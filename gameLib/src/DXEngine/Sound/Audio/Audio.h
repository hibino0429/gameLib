#pragma once
#include <atlbase.h>
#include <XAudio2.h>
#include <string>
#include "../../src/DXEngine/Sound/Wave/Wave.h"

#pragma comment(lib,"XAudio2.lib")


//-----------------------------------------------------------------------------------
//!@class		Audio
//!@brief	Sound�������N���X
//!@brief	Sound�̍Đ��E��~�E�����̔j���Ȃǂ��s��
//-----------------------------------------------------------------------------------
class SoundSource
{
public:
	//!@brief	�R���X�g���N�^
	SoundSource();
	//!@brief	�R���X�g���N�^
	//!@param[in]	sound	�T�E���h�\�[�X
	SoundSource(SoundSource& sound);
	//!@brief	�f�X�g���N�^
	~SoundSource();

	//!@brief	�T�E���h�̃��[�h
	//!@param[in]	filePath	�t�@�C���̃p�X
	bool	Load(const std::string& filePath);
	//!@brief	BGM�̍Đ�
	//!@param[in]	loopNum	���[�v
	//!@param[in]	gain	����
	//!@param[in]	pitch	�s�b�`
	void	PlayBGM(int loopNum = XAUDIO2_LOOP_INFINITE, float gain = 1.0f, float pitch = 1.0f);
	//!@brief	SE�̍Đ�
	//!@param[in]	gain	����
	//!@param[in]	pitch	�s�b�`
	void	PlaySE(float gain = 1.0f, float pitch = 1.0f);

	//!@brief	�ꎞ��~
	void	Pause();
	//!@brief	��~
	void	Stop();
	//!@brief	�\�[�X�̔j��
	void	Destory();

private:
	XAUDIO2_BUFFER			audiobuf;	//�����i�[�o�b�t�@

public:
	IXAudio2SourceVoice*	source;		//�T�E���h�\�[�X
	Wave					wave;
};



//---------------------------------------------------------------------------------
//!@class		SoundSystem
//!@brief	�T�E���h�̃V�X�e���������N���X
//!@brief	�T�E���h���Ǘ�����
//---------------------------------------------------------------------------------
class SoundSystem
{
public:
	//!@brief	�R���X�g���N�^
	SoundSystem();
	//!@brief	�f�X�g���N�^
	~SoundSystem();

	//!@brief	�\�[�X�{�C�X�̓o�^
	//!@param[in]	source �T�E���h�\�[�X
	bool	AddSource(SoundSource& source);

	//!@brief	�T�E���h�S�̂̉��ʒ���
	//!@brief	gain	����
	void	SetMasterGain(float gain);
	//!@brief	�T�E���h�̔j��
	//!@param[in]	source	�\�[�X
	void	DestorySystem(SoundSource& source);

private:
	//!@brief	�T�E���h�V�X�e���̐���
	bool	Create();

private:
	IXAudio2*				xAudio2;
	IXAudio2MasteringVoice*	master;
};