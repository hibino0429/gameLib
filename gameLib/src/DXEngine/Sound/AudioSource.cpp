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
			MessageBoxA(nullptr, "SubMixVoice�̍쐬�Ɏ��s���܂���", "AudioSource::Load()", MB_OK);
			return false;
		}
		sendDescription.Flags = 0;
		sendDescription.pOutputVoice = data->subMixVoice;
		sendList.pSends = &sendDescription;
		sendList.SendCount = 1;

		//�\�[�X�{�C�X�̍쐬
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
			MessageBoxA(nullptr, "�\�[�X�{�C�X�̍쐬�Ɏ��s���܂���", "AudioSource::Load()", MB_OK);
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
			MessageBoxA(nullptr, "Source�ɉ����̏��𑗂�", "AudioSource::PlayBGM()", MB_OK);
			return;
		}
		if (data->source)
		{
			data->source->Start();
		}
		while (data->xState.BuffersQueued > 0)
		{
			//�C�x���g���g���K�[�����̂�҂�
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
			MessageBoxA(nullptr, "Source�ɉ����̏��𑗂�", "AudioSource::PlaySE()", MB_OK);
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
			data->source->Stop(0);	//��U��~
			data->source->FlushSourceBuffers();						//�{�C�X�L���[���폜(�Đ��ʒu��߂�)
			data->source->SubmitSourceBuffer(&data->buf, nullptr);	//Source�ɉ����̏��𑗂�
		}
	}
	void	AudioSource::Pause()
	{
		GetState();
		UINT isPlay = data->xState.BuffersQueued;	//�Đ����Ȃ�0�ȊO
		if (data->source && isPlay != 0)
		{
			data->source->Stop(0);
		}
	}
	void	AudioSource::SetVolume(const float volume)
	{
		data->source->SetVolume(volume);
		data->source->SubmitSourceBuffer(&data->buf, nullptr);	//Source�ɉ����̏��𑗂�
	}
	void	AudioSource::SetListener(const Math::Vector3& listenerPos)
	{
		if (!data->is3DAudio) { return; }
		XAUDIO2_VOICE_DETAILS voiceDetails;
		XAUDIO2_VOICE_DETAILS& deviceDetails = audioEngine.GetVoiceDetails();
		data->subMixVoice->GetVoiceDetails(&voiceDetails);

		float emitterAzimuths[1] = { 0.0f };
		data->emitter.pCone = NULL;
		data->emitter.Position = { listenerPos.x, listenerPos.y, listenerPos.z };	//��������
		data->emitter.OrientFront = { 0, 0, 1 };
		data->emitter.OrientTop = { 0 , 1, 0 };
		data->emitter.ChannelCount = voiceDetails.InputChannels;	//�\�[�X�̃`�����l����
		data->emitter.ChannelRadius = 1.0f;							//�G�~�b�^�ł̍s��̌v�Z�݂̂Ɏg�p�B���̒l��0.0f�ȏ�ł��邱�Ƃ��K�v
		data->emitter.pChannelAzimuths = emitterAzimuths;			//���ʊp�B�`�����l�����a�Ƌ��Ɏg�p�����B�s��̌v�Z�݂̂Ɏg�p
		data->emitter.InnerRadius = 1.0f;							//�������a�̌v�Z�Ɏg�p�����l�B0.0f �` MAX_FLT�̒l���w��
		data->emitter.InnerRadiusAngle = 1.0f;						//�����p�x�̌v�Z�Ɏg�p�����l�B0.0f �` X3DAUDIO_PI/4.0 �̒l���w��
		data->emitter.pVolumeCurve = NULL;							//�{�����[�����x�������J�[�u�B�s��̌v�Z�ɂ̂ݎg�p
		data->emitter.pLFECurve = NULL;								//LFE ���[���I�t�����J�[�u
		data->emitter.pLPFDirectCurve = NULL;						//���[�p�X�t�B���^�[(LPF)�_�C���N�g �p�X�W�������J�[�uNULL�ŋK��l
		data->emitter.pLPFReverbCurve = NULL;						//LPF���o�[�u�p�X�W�������J�[�u
		data->emitter.pReverbCurve = NULL;							//���o�[�u�Z���h���x�������J�[�u�B
		data->emitter.CurveDistanceScaler = 7.0f;					//����
		//�ق��̌v�Z�ɉe�����Ȃ��B���̒l��FLT_MIN�`FLT_MAX�͈̔͂ɂ���K�v������
		data->emitter.DopplerScaler = 1.0f;							//�h�b�v���[�Έڌ��ʂ��������邽�߂Ɏg�p����h�b�v���[�ΈڃX�P�[���[�B0.0f �` FLT_MAX �͈͓̔��ɂ���K�v������

		data->listener.OrientFront = X3DAUDIO_VECTOR(0, 0, 1);		//�O�������̒�`
		data->listener.OrientTop = X3DAUDIO_VECTOR(0, 1, 0);		//������̒�`
		data->listener.pCone = NULL;								//NULL�͑S�������Ɠ���
		data->listener.Position = X3DAUDIO_VECTOR(listenerPos.x, listenerPos.y, listenerPos.z);
		data->listener.Velocity = X3DAUDIO_VECTOR(1.0f, 0.0f, 1.0f);//�h�b�v���[���ʂɗp����Position�ɂ͉e�����Ȃ�
		data->dsp.SrcChannelCount = data->emitter.ChannelCount;
		data->dsp.DstChannelCount = deviceDetails.InputChannels;

		if (!data->dsp.pMatrixCoefficients)
		{
			data->dsp.pMatrixCoefficients = new FLOAT32[data->dsp.SrcChannelCount * data->dsp.DstChannelCount];
			memset(data->dsp.pMatrixCoefficients, 0, sizeof(FLOAT32) * (data->dsp.SrcChannelCount * data->dsp.DstChannelCount));
		}

		/*emitter�\���̂�NULL���w�肵���ϐ��ɂ���ē��삪�ς��̂Œ���!!*/
		DWORD calculateFlags =
			X3DAUDIO_CALCULATE_MATRIX |					//�s��W���e�[�u���̌v�Z��L���ɂ��܂��B 
			//X3DAUDIO_CALCULATE_DELAY |				//�x�����Ԕz��̌v�Z��L���ɂ��܂� (�X�e���I�̂�)�B 
			X3DAUDIO_CALCULATE_LPF_DIRECT |				//���[�p�X�t�B���^�[ (LPF) �_�C���N�g�p�X�W���̌v�Z��L���ɂ��܂��B
			//X3DAUDIO_CALCULATE_LPF_REVERB |			//LPF ���o�[�u�p�X�W���̌v�Z��L���ɂ��܂��B 
			//	X3DAUDIO_CALCULATE_REVERB |				//���o�[�u�Z���h���x���̌v�Z��L���ɂ��܂��B 
			X3DAUDIO_CALCULATE_DOPPLER |				//�h�b�v���[�ΈڌW���̌v�Z��L���ɂ��܂��B 
			X3DAUDIO_CALCULATE_EMITTER_ANGLE;			//�G�~�b�^/���X�i�[�̓��p�̌v�Z��L���ɂ��܂��B 
			//X3DAUDIO_CALCULATE_ZEROCENTER |			//�����`�����l���ɖ����̒l��ݒ肵�܂��B 
			//X3DAUDIO_CALCULATE_REDIRECT_TO_LFE;		//���ׂẴ\�[�X�`�����l���̋ϓ��~�b�N�X�����g���� (LFE) �f�X�e�B�l�[�V�����`�����l���ɓK�p���܂��B

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
		data->buf.Flags = XAUDIO2_END_OF_STREAM;	//�f�[�^���Ȃ����Ƃ��\�[�X�{�C�X�ɓ`����
		data->buf.PlayBegin = begin;				//�ŏ��̃T���v��
		data->buf.LoopLength = end;
		data->buf.LoopCount = XAUDIO2_LOOP_INFINITE;
		data->source->FlushSourceBuffers();			//�{�C�X�L���[���폜
		data->source->SubmitSourceBuffer(&data->buf, nullptr);	//Source�ɉ����̏��𑗂�
	}
	void	AudioSource::SetLoopNum(int loopNum)
	{
		data->buf.LoopCount = loopNum;
		data->source->SubmitSourceBuffer(&data->buf, nullptr);
	}
	void	AudioSource::Destroy()
	{
		//�\�[�X�̍Đ����~�߂Ă���폜
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