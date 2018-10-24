#include "AudioSource.h"



namespace AudioSystem
{
	AudioSource::AudioSource()
		: data(new AudioData())
		, pcm(nullptr)
	{
		
	}
	AudioSource::~AudioSource()
	{
		Destroy();
	}
	bool	AudioSource::Load(const std::string& filePath, bool is3DSoundFlag)
	{
		std::string  oggName = ".ogg";
		std::string	 wavName = ".wav";

		if (std::equal(filePath.begin() + filePath.find("."), filePath.end(), oggName.begin()))
		{
			pcm = new Ogg(filePath);
		}
		else if (std::equal(filePath.begin() + filePath.find("."), filePath.end(), wavName.begin()))
		{
			pcm = new Wave(filePath);
		}
		XAUDIO2_SEND_DESCRIPTOR sendDescription = { 0 };
		XAUDIO2_VOICE_SENDS sendList = { 0 };

		data->is3DAudio = is3DSoundFlag;

		auto hr = audioEngine.GetXAudio2()->CreateSubmixVoice(
			&data->subMixVoice,
			pcm->GetWaveFmtEx().nChannels,
			pcm->GetWaveFmtEx().nSamplesPerSec,
			XAUDIO2_VOICE_USEFILTER
		);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "SubMixVoiceの作成に失敗しました", "AudioSource::Load()", MB_OK);
			return false;
		}
		sendDescription.Flags = 0;
		sendDescription.pOutputVoice = data->subMixVoice;
		sendList.pSends = &sendDescription;
		sendList.SendCount = 1;

		//ソースボイスの作成
		hr = audioEngine.GetXAudio2()->CreateSourceVoice(
			&data->source,
			&pcm->GetWaveFmtEx(),
			0,
			XAUDIO2_DEFAULT_FREQ_RATIO,
			&data->voiceCallback,
			&sendList,
			0
		);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "ソースボイスの作成に失敗しました", "AudioSource::Load()", MB_OK);
			return false;
		}
		data->buf = { 0 };
		return true;
	}
	void	AudioSource::PlayBGM(int loopNum, float gain, float pitch)
	{
		data->buf.AudioBytes = (UINT32)pcm->GEtWaveByteSize();
		data->buf.pAudioData = pcm->GetWaveData();
		data->buf.pContext = this;
		data->buf.Flags = XAUDIO2_END_OF_STREAM;
		data->buf.PlayBegin = 0;
		data->buf.PlayLength = 0;
		data->buf.LoopCount = loopNum;
		data->source->SetFrequencyRatio(pitch);
		data->source->SetVolume(gain);
		data->source->FlushSourceBuffers();
		auto hr = data->source->SubmitSourceBuffer(&data->buf, nullptr);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Sourceに音源の情報を送る", "AudioSource::PlayBGM()", MB_OK);
			return;
		}
		if (data->source)
		{
			data->source->Start();
		}
		while (data->xState.BuffersQueued > 0)
		{
			//イベントがトリガーされるのを待つ
			WaitForSingleObject(data->voiceCallback.handle, INFINITE);
		}
	}
	void	AudioSource::PlaySE(int loopNum, float gain, float pitch)
	{
		data->buf.AudioBytes = (UINT)pcm->GEtWaveByteSize();
		data->buf.pAudioData = pcm->GetWaveData();
		data->buf.pContext = this;
		data->buf.Flags = XAUDIO2_END_OF_STREAM;
		data->buf.PlayBegin = 0;
		data->buf.PlayLength = 0;
		data->buf.LoopCount = 0;
		data->source->SetFrequencyRatio(pitch);
		data->source->SetVolume(gain);
		data->source->FlushSourceBuffers();
		auto hr = data->source->SubmitSourceBuffer(&data->buf, nullptr);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "Sourceに音源の情報を送る", "AudioSource::PlaySE()", MB_OK);
			return;
		}
		if (data->source)
		{
			data->source->Start();

		}
	}
	void	AudioSource::Stop() const
	{
		if (data->source)
		{
			data->source->Stop(0);	//一旦停止
			data->source->FlushSourceBuffers();						//ボイスキューを削除(再生位置を戻す)
			data->source->SubmitSourceBuffer(&data->buf, nullptr);	//Sourceに音源の情報を送る
		}
	}
	void	AudioSource::Pause()
	{
		GetState();
		UINT isPlay = data->xState.BuffersQueued;	//再生中なら0以外
		if (data->source && isPlay != 0)
		{
			data->source->Stop(0);
		}
	}
	void	AudioSource::SetVolume(const float volume)
	{
		data->source->SetVolume(volume);
		data->source->SubmitSourceBuffer(&data->buf, nullptr);	//Sourceに音源の情報を送る
	}
	void	AudioSource::SetListener(const Math::Vector3& listenerPos)
	{
		if (!data->is3DAudio) { return; }
		XAUDIO2_VOICE_DETAILS voiceDetails;
		XAUDIO2_VOICE_DETAILS& deviceDetails = audioEngine.GetVoiceDetails();
		data->subMixVoice->GetVoiceDetails(&voiceDetails);

		float emitterAzimuths[1] = { 0.0f };
		data->emitter.pCone = NULL;
		data->emitter.Position = { listenerPos.x, listenerPos.y, listenerPos.z };	//ここ改造
		data->emitter.OrientFront = { 0, 0, 1 };
		data->emitter.OrientTop = { 0 , 1, 0 };
		data->emitter.ChannelCount = voiceDetails.InputChannels;	//ソースのチャンネル数
		data->emitter.ChannelRadius = 1.0f;							//エミッタでの行列の計算のみに使用。この値は0.0f以上であることが必要
		data->emitter.pChannelAzimuths = emitterAzimuths;			//方位角。チャンネル半径と共に使用される。行列の計算のみに使用
		data->emitter.InnerRadius = 1.0f;							//内部半径の計算に使用される値。0.0f ～ MAX_FLTの値を指定
		data->emitter.InnerRadiusAngle = 1.0f;						//内部角度の計算に使用される値。0.0f ～ X3DAUDIO_PI/4.0 の値を指定
		data->emitter.pVolumeCurve = NULL;							//ボリュームレベル距離カーブ。行列の計算にのみ使用
		data->emitter.pLFECurve = NULL;								//LFE ロールオフ距離カーブ
		data->emitter.pLPFDirectCurve = NULL;						//ローパスフィルター(LPF)ダイレクト パス係数距離カーブNULLで規定値
		data->emitter.pLPFReverbCurve = NULL;						//LPFリバーブパス係数距離カーブ
		data->emitter.pReverbCurve = NULL;							//リバーブセンドレベル距離カーブ。
		data->emitter.CurveDistanceScaler = 7.0f;					//減衰
		//ほかの計算に影響しない。この値はFLT_MIN～FLT_MAXの範囲にする必要がある
		data->emitter.DopplerScaler = 1.0f;							//ドップラー偏移効果を強調するために使用するドップラー偏移スケーラー。0.0f ～ FLT_MAX の範囲内にする必要がある

		data->listener.OrientFront = X3DAUDIO_VECTOR(0, 0, 1);		//前方方向の定義
		data->listener.OrientTop = X3DAUDIO_VECTOR(0, 1, 0);		//上方向の定義
		data->listener.pCone = NULL;								//NULLは全方向性と同じ
		data->listener.Position = X3DAUDIO_VECTOR(listenerPos.x, listenerPos.y, listenerPos.z);
		data->listener.Velocity = X3DAUDIO_VECTOR(1.0f, 0.0f, 1.0f);//ドップラー効果に用いるPositionには影響しない
		data->dsp.SrcChannelCount = data->emitter.ChannelCount;
		data->dsp.DstChannelCount = deviceDetails.InputChannels;

		if (!data->dsp.pMatrixCoefficients)
		{
			data->dsp.pMatrixCoefficients = new FLOAT32[data->dsp.SrcChannelCount * data->dsp.DstChannelCount];
			memset(data->dsp.pMatrixCoefficients, 0, sizeof(FLOAT32) * (data->dsp.SrcChannelCount * data->dsp.DstChannelCount));
		}

		/*emitter構造体にNULLを指定した変数によって動作が変わるので注意!!*/
		DWORD calculateFlags =
			X3DAUDIO_CALCULATE_MATRIX |					//行列係数テーブルの計算を有効にします。 
			//X3DAUDIO_CALCULATE_DELAY |				//遅延時間配列の計算を有効にします (ステレオのみ)。 
			X3DAUDIO_CALCULATE_LPF_DIRECT |				//ローパスフィルター (LPF) ダイレクトパス係数の計算を有効にします。
			//X3DAUDIO_CALCULATE_LPF_REVERB |			//LPF リバーブパス係数の計算を有効にします。 
			//	X3DAUDIO_CALCULATE_REVERB |				//リバーブセンドレベルの計算を有効にします。 
			X3DAUDIO_CALCULATE_DOPPLER |				//ドップラー偏移係数の計算を有効にします。 
			X3DAUDIO_CALCULATE_EMITTER_ANGLE;			//エミッタ/リスナーの内角の計算を有効にします。 
			//X3DAUDIO_CALCULATE_ZEROCENTER |			//中央チャンネルに無音の値を設定します。 
			//X3DAUDIO_CALCULATE_REDIRECT_TO_LFE;		//すべてのソースチャンネルの均等ミックスを低周波効果 (LFE) デスティネーションチャンネルに適用します。

		X3DAudioCalculate(
			audioEngine.Get3DInstance(),
			&data->listener,
			&data->emitter,
			calculateFlags,
			&data->dsp);

		data->subMixVoice->SetOutputMatrix(NULL, data->dsp.SrcChannelCount, data->dsp.DstChannelCount, data->dsp.pMatrixCoefficients);
		data->source->SetFrequencyRatio(data->dsp.DopplerFactor);

		XAUDIO2_FILTER_PARAMETERS filterParameters = { LowPassFilter, 2.0f * sinf(X3DAUDIO_PI / 4.0f *data->dsp.LPFDirectCoefficient),  1.0f };

		data->subMixVoice->SetFilterParameters(&filterParameters);
	}
	void	AudioSource::ExitLoop() const
	{
		data->source->ExitLoop();
	}
	void	AudioSource::SetLoopPoint(const UINT32 begin, const UINT32 end)
	{
		data->buf.AudioBytes = (UINT32)pcm->GEtWaveByteSize();
		data->buf.pAudioData = pcm->GetWaveData();
		data->buf.pContext = this;
		data->buf.Flags = XAUDIO2_END_OF_STREAM;	//データがないことをソースボイスに伝える
		data->buf.PlayBegin = begin;				//最初のサンプル
		data->buf.LoopLength = end;
		data->buf.LoopCount = XAUDIO2_LOOP_INFINITE;
		data->source->FlushSourceBuffers();			//ボイスキューを削除
		data->source->SubmitSourceBuffer(&data->buf, nullptr);	//Sourceに音源の情報を送る
	}
	void	AudioSource::SetLoopNum(int loopNum)
	{
		data->buf.LoopCount = loopNum;
		data->source->SubmitSourceBuffer(&data->buf, nullptr);
	}
	void	AudioSource::Destroy()
	{
		//ソースの再生を止めてから削除
		data->source->Stop(0);
		if (data->dsp.pMatrixCoefficients != nullptr)
		{
			delete data->dsp.pMatrixCoefficients;
			data->dsp.pMatrixCoefficients = nullptr;
		}
		if (data != nullptr)
		{
			delete data;
			data = nullptr;
		}
		if (pcm != nullptr)
		{
			delete pcm;
			pcm = nullptr;
		}
	}
	UINT64	AudioSource::GetCurrentSampleTime() const
	{
		return data->xState.SamplesPlayed;
	}
	IXAudio2SourceVoice*	AudioSource::GetSource() const
	{
		return data->source;
	}
	WORD		AudioSource::GetChannels() const
	{
		return pcm->GetWaveFmtEx().nChannels;
	}

	void	AudioSource::GetState()
	{
		#if(_WIN32_WINNT >= _WIN32_WINNT_WIN8)
			data->source->GetState(&data->xState, 0);
		#else 
			data->source->GetState(&data->xState);
		#endif
	}
}