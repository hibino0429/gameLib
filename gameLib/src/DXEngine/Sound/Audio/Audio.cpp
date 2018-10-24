#include "Audio.h"

//!@brief	�R���X�g���N�^
SoundSource::SoundSource()
	: source(nullptr)
{
	
}

//!@brief	�R���X�g���N�^
//!@param[in]	sound	�T�E���h�\�[�X
SoundSource::SoundSource(SoundSource& sound)
{
	source = sound.source;
	wave = sound.wave;
}

//!@brief	�f�X�g���N�^
SoundSource::~SoundSource()
{
	Destory();
}

//!@brief	�T�E���h�̃��[�h
//!@param[in]	filePath	�t�@�C���̃p�X
bool	SoundSource::Load(const std::string& filePath)
{
	if (!wave.Load(filePath))
	{
		return false;
	}
	return true;
}

//!@brief	BGM�̍Đ�
//!@param[in]	loopNum	���[�v
//!@param[in]	gain	����
//!@param[in]	pitch	�s�b�`
void	SoundSource::PlayBGM(int loopNum, float gain, float pitch)
{
	audiobuf = { 0 };
	audiobuf.AudioBytes = wave.GetWaveSize();
	audiobuf.pAudioData = wave.GetWaveData();
	audiobuf.Flags = XAUDIO2_END_OF_STREAM;	//�f�[�^���Ȃ����Ƃ��\�[�X�{�C�X�ɓ`����
	audiobuf.LoopCount = loopNum;			//���[�v�񐔂̎w��
	audiobuf.LoopBegin = 0;
	source->SetFrequencyRatio(pitch);
	source->SetVolume(gain);
	auto result = source->SubmitSourceBuffer(&audiobuf, nullptr);	//Source�ɉ������𑗂�
	if (FAILED(result))
	{
		//�G���[���b�Z�[�W
	}
	if (source)
	{
		source->Start();
	}
}

//!@brief	SE�̍Đ�
//!@param[in]	gain	����
//!@param[in]	pitch	�s�b�`
void	SoundSource::PlaySE(float gain, float pitch)
{
	audiobuf = { 0 };
	audiobuf.AudioBytes = wave.GetWaveSize();
	audiobuf.pAudioData = wave.GetWaveData();
	audiobuf.LoopCount = 0;						//���[�v�񐔂̎w��
	audiobuf.LoopBegin = 0;

	source->SetFrequencyRatio(pitch);
	source->SetVolume(gain);
	source->Stop(0);						//��U��~
	source->FlushSourceBuffers();			//�{�C�X�L���[���폜
	source->SubmitSourceBuffer(&audiobuf, nullptr);	//source�ɉ������𑗂�
	if (source)
	{
		source->Start();
	}
}

//!@brief	�ꎞ��~
void	SoundSource::Pause()
{
	XAUDIO2_VOICE_STATE xa2state;
	source->GetState(&xa2state);
	auto isPlay = xa2state.BuffersQueued;	//�Đ����Ȃ�0�ȊO���Ԃ�
	if (source && isPlay != 0)
	{
		source->Stop(0);
	}
}

//!@brief	��~
void	SoundSource::Stop()
{
	if (source)
	{
		source->Stop(0);
		source->FlushSourceBuffers();
		source->SubmitSourceBuffer(&audiobuf, nullptr);
	}
}

//!@brief	�\�[�X�̔j��
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


//!@brief	�R���X�g���N�^
SoundSystem::SoundSystem()
	: xAudio2(nullptr)
	, master(nullptr)
{
	Create();
}

//!@brief	�f�X�g���N�^
SoundSystem::~SoundSystem()
{
	if (master != nullptr)
	{
		master->DestroyVoice();
		master = nullptr;
	}
}

//!@brief	�\�[�X�{�C�X�̓o�^
//!@param[in]	source �T�E���h�\�[�X
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

//!@brief	�T�E���h�S�̂̉��ʒ���
//!@brief	gain	����
void	SoundSystem::SetMasterGain(float gain)
{
	master->SetVolume(gain);
}

//!@brief	�T�E���h�̔j��
//!@param[in]	source	�\�[�X
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


//!@brief	�T�E���h�V�X�e���̐���
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