#include "Audio.h"

//!@brief	コンストラクタ
SoundSource::SoundSource()
	: source(nullptr)
{
	
}

//!@brief	コンストラクタ
//!@param[in]	sound	サウンドソース
SoundSource::SoundSource(SoundSource& sound)
{
	source = sound.source;
	wave = sound.wave;
}

//!@brief	デストラクタ
SoundSource::~SoundSource()
{
	Destory();
}

//!@brief	サウンドのロード
//!@param[in]	filePath	ファイルのパス
bool	SoundSource::Load(const std::string& filePath)
{
	if (!wave.Load(filePath))
	{
		return false;
	}
	return true;
}

//!@brief	BGMの再生
//!@param[in]	loopNum	ループ
//!@param[in]	gain	音量
//!@param[in]	pitch	ピッチ
void	SoundSource::PlayBGM(int loopNum, float gain, float pitch)
{
	audiobuf = { 0 };
	audiobuf.AudioBytes = wave.GetWaveSize();
	audiobuf.pAudioData = wave.GetWaveData();
	audiobuf.Flags = XAUDIO2_END_OF_STREAM;	//データがないことをソースボイスに伝える
	audiobuf.LoopCount = loopNum;			//ループ回数の指定
	audiobuf.LoopBegin = 0;
	source->SetFrequencyRatio(pitch);
	source->SetVolume(gain);
	auto result = source->SubmitSourceBuffer(&audiobuf, nullptr);	//Sourceに音源情報を送る
	if (FAILED(result))
	{
		//エラーメッセージ
	}
	if (source)
	{
		source->Start();
	}
}

//!@brief	SEの再生
//!@param[in]	gain	音量
//!@param[in]	pitch	ピッチ
void	SoundSource::PlaySE(float gain, float pitch)
{
	audiobuf = { 0 };
	audiobuf.AudioBytes = wave.GetWaveSize();
	audiobuf.pAudioData = wave.GetWaveData();
	audiobuf.LoopCount = 0;						//ループ回数の指定
	audiobuf.LoopBegin = 0;

	source->SetFrequencyRatio(pitch);
	source->SetVolume(gain);
	source->Stop(0);						//一旦停止
	source->FlushSourceBuffers();			//ボイスキューを削除
	source->SubmitSourceBuffer(&audiobuf, nullptr);	//sourceに音源情報を送る
	if (source)
	{
		source->Start();
	}
}

//!@brief	一時停止
void	SoundSource::Pause()
{
	XAUDIO2_VOICE_STATE xa2state;
	source->GetState(&xa2state);
	auto isPlay = xa2state.BuffersQueued;	//再生中なら0以外が返る
	if (source && isPlay != 0)
	{
		source->Stop(0);
	}
}

//!@brief	停止
void	SoundSource::Stop()
{
	if (source)
	{
		source->Stop(0);
		source->FlushSourceBuffers();
		source->SubmitSourceBuffer(&audiobuf, nullptr);
	}
}

//!@brief	ソースの破棄
void	SoundSource::Destory()
{
	if (source != nullptr)
	{
		source->Stop(0);
		source->DestroyVoice();
		source = nullptr;
	}
}




//***************************************************************************


//!@brief	コンストラクタ
SoundSystem::SoundSystem()
	: xAudio2(nullptr)
	, master(nullptr)
{
	Create();
}

//!@brief	デストラクタ
SoundSystem::~SoundSystem()
{
	if (master != nullptr)
	{
		master->DestroyVoice();
		master = nullptr;
	}
}

//!@brief	ソースボイスの登録
//!@param[in]	source サウンドソース
bool	SoundSystem::AddSource(SoundSource& source)
{
	auto result = xAudio2->CreateSourceVoice(
		&source.source,
		&source.wave.GetWaveFormatEx()
	);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

//!@brief	サウンド全体の音量調整
//!@brief	gain	音量
void	SoundSystem::SetMasterGain(float gain)
{
	master->SetVolume(gain);
}

//!@brief	サウンドの破棄
//!@param[in]	source	ソース
void	SoundSystem::DestorySystem(SoundSource& source)
{
	if (source.source != nullptr)
	{
		source.source->Stop(0);
		source.source->DestroyVoice();
		source.source = nullptr;
	}
	if (master != nullptr)
	{
		master->DestroyVoice();
		master = nullptr;
	}
}


//!@brief	サウンドシステムの生成
bool	SoundSystem::Create()
{
	auto result = XAudio2Create(&xAudio2, 0);
	if (FAILED(result))
	{
		return false;
	}
	result = xAudio2->CreateMasteringVoice(
		&master,
		XAUDIO2_DEFAULT_CHANNELS,
		XAUDIO2_DEFAULT_SAMPLERATE,
		0,
		0,
		nullptr
	);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}