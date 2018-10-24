#pragma once
#pragma comment(lib,"winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
#include <vector>
#include <string>



namespace AudioSystem
{
	//---------------------------------------------------------------
	//!@class		WaveDecoder
	//---------------------------------------------------------------
	class WaveDecoder
	{
	public:
		//!@brief	�R���X�g���N�^
		WaveDecoder();
		//!@brief	�f�X�g���N�^
		~WaveDecoder();
	public:
		//!@brief	���[�h����
		//!@param[in]	filePath	�t�@�C���p�X
		bool	Load(const std::string& filePath);
		//!@brief	WAVE�t�H�[�}�b�g���擾
		const WAVEFORMATEX&	GetWaveFmtEx() const;
		//!@brief	�t�@�C�����̎擾
		const std::string&	GetFileName() const;
		//!@brief	Wave�f�[�^���擾
		const BYTE*	GetWaveData() const;
		//!@brief	Wave�f�[�^�̃T�C�Y�̎擾
		const size_t	GetWaveByteSize() const;
	private:
		//!@brief	Wave�t�@�C���I�[�v��
		bool	Open(const std::string& filePath);
		//!@brief	Wave�t�@�C���N���[�Y
		bool	Close();
		//!@brief	WAVEFORMATEX�Ƀf�[�^��ǂݍ���
		bool	ReadToWaveFmtEx();
		//!@brief	WaveData��WAVE�f�[�^��ǂݍ���
		bool	ReadToWaveData();
		//!@brief	WAVE�w�b�_�����邩�`�F�b�N
		bool	IsWaveHeader();
		//!@brief	FMT�`�����N�����邩�`�F�b�N
		bool	IsFMTChunk();
		//!@brief	DATA�`�����N�����邩�`�F�b�N
		bool	IsDATAChunk();
	private:
		HMMIO				mmio;		//MMIO�n���h��
		MMCKINFO			riff;		//RIFF�`�����N
		MMCKINFO			fmt;		//FMT�`�����N
		MMCKINFO			data;		//DATA�`�����N
		WAVEFORMATEX		wave;		//WAVE�t�H�[�}�b�g�\����
		std::vector<BYTE>	waveData;	//���y�f�[�^
		std::string			fileName;	//�t�@�C����
	};
}