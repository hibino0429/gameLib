#pragma once
#include <string>
#include "Audio.h"
#include "PCM.h"
#include "../../DXEngine/Math/Math.h"


namespace AudioSystem
{
	class AudioSource
	{
	private:
		struct AudioData
		{
			IXAudio2SubmixVoice*	subMixVoice;
			XAudio2Callback			voiceCallback;	//�R�[���o�b�N
			X3DAUDIO_DSP_SETTINGS	dsp;			//X3DAudioCalculate�̌Ăяo�����ʂ��󂯎��
			XAUDIO2_BUFFER			buf;			//�����i�[�p�̃o�b�t�@
			IXAudio2SourceVoice*	source;			//�\�[�X���H�C�X(�������i�[�����)
			XAUDIO2_VOICE_STATE		xState;			//�\�[�X�̏��i�[�p
			X3DAUDIO_EMITTER		emitter;		//3D�I�[�f�B�I�\�[�X�̒�`
			X3DAUDIO_LISTENER		listener;		//���X�i�[�ʒu
			bool					is3DAudio;		//3D�����t���O
		};
	public:
		//!@brief	�R���X�g���N�^
		AudioSource();
		//!@brief	�f�X�g���N�^
		~AudioSource();
	public:
		//!@brief	�\�[�X�̃��[�h
		//!@param[in]	filePath	�t�@�C���p�X
		//!@param[in]	is3DSoundFlag	3D�T�E���h�̃t���O
		bool	Load(const std::string& filePath, bool is3DSoundFlag);
		//!@brief	BGM�̍Đ�
		void	PlayBGM(int loopNum = XAUDIO2_LOOP_INFINITE, float gain = 1.0f, float pitch = 1.0f);
		//!@brief	SE�̍Đ�
		void	PlaySE(int loopNum = 0, float gain = 1.0f, float pitch = 1.0f);
		//!@brief	�Đ��̒�~
		void	Stop() const;
		//!@brief	�Đ��̈ꎞ��~
		void	Pause();
		//!@brief	�{�����[��(0�`1)�̊�
		void	SetVolume(const float volume);
		//!@brief	3D���X�i�[�̈ʒu��ݒ�
		//!@note	3D�T�E���h���g�p����Ƃ��̂�
		void	SetListener(const Math::Vector3& listenerPos);
		//!@brief	�Ȃ̏I�[�ɗ����烋�[�v���~������
		void	ExitLoop() const;
		//!@brief	���[�v��Ԃ�ݒ�
		void	SetLoopPoint(const UINT32 begin, const UINT32 end);
		//!@brief	���[�v�̕��@��ݒ�
		void	SetLoopNum(int loopNum);
		//!@brief	�j��
		void	Destroy();
		//!@brief	���݂̃T���v���[���Ԃ��擾
		UINT64	GetCurrentSampleTime() const;
		//!@brief	�����̎擾
		IXAudio2SourceVoice*	GetSource() const;
		//!@brief	�`�����l���̎擾
		WORD		GetChannels() const;
	private:
		//!@brief	�\�[�X�̏��̎擾
		void		GetState();
	private:
		AudioData*		data;
		PCM*			pcm;
		Audio			audioEngine;
	};


	class AudioListener
	{
	public:
		AudioListener();
		AudioListener(const Math::Vector3& position);
	private:
		X3DAUDIO_LISTENER		listener;		//���X�i�[�ʒu
	};
}