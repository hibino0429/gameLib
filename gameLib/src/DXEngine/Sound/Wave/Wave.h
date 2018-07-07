#pragma once
#pragma comment(lib,"winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
#include <vector>
#include <string>


//--------------------------------------------------------------------------------
//!@class		Wave
//!@brief	Wave�������N���X
//--------------------------------------------------------------------------------
class Wave
{
public:
	//!@brief	�R���X�g���N�^
	Wave();
	//!@brief	�R���X�g���N�^
	~Wave();

	//!@brief	Wave�̃��[�h
	//!@param[in]	filePath	�t�@�C���p�X
	//!@return �����Ȃ� true ���s�Ȃ� false
	bool	Load(const std::string& filePath);
	//!@brief	Wave�t�H�[�}�b�g�̎擾
	//!@return	WaveFormat	Wave�t�H�[�}�b�g
	const WAVEFORMATEX&	GetWaveFormatEx() const;
	//!@brief	�t�@�C�����̎擾
	//!@return	fileName	�t�@�C����
	const std::string&	GetFileName() const;
	//!@brief	Wave�f�[�^�̎擾
	//!@return Wave�f�[�^
	const BYTE*	GetWaveData() const;
	//!@brief	Wave�f�[�^�̃T�C�Y�̎擾
	//!@return Wave�f�[�^�̃T�C�Y
	const size_t	GetWaveSize() const;

private:

	//!@brief	Wave�t�@�C�����J��
	//!@param[in]	filePath	�t�@�C���p�X
	//!@return	�����Ȃ� true ���s�Ȃ� false
	bool	Open(const std::string& filePath);
	//!@brief	Wave�t�@�C�������
	//!@return	�����Ȃ� true ���s�Ȃ� false
	bool	Close();
	//!@brief	WaveFormat��ǂݍ���
	//!@return	�����Ȃ� true ���s�Ȃ� false
	bool	ReadToWaveFormat();
	//!@brief	WaveData��Wave�f�[�^��ǂݍ���
	//!@return	�����Ȃ� true ���s�Ȃ� false
	bool	ReadToWaveData();
	//!@brief	Wave�w�b�_�����邩�`�F�b�N
	//!@return	�����Ȃ� true ���s�Ȃ� false
	bool	IsWaveHeader();
	//!@brief	FMT�`�����N�����邩�`�F�b�N
	//!@return	�����Ȃ� true ���s�Ȃ� false
	bool	IsFMTChunk();
	//!@brief	DATA�`�����N�����邩�`�F�b�N
	//!@return	�����Ȃ� true ���s�Ȃ� false
	bool	IsDataChunk();


private:
	HMMIO		mmio;	//MMIO�n���h��
	MMCKINFO	riff;	//RIFF�`�����N
	MMCKINFO	fmt;	//FMT�`�����N
	MMCKINFO	data;	//DATA�`�����N
	WAVEFORMATEX		waveFormat;		//�t�H�[�}�b�g�\����
	std::vector<BYTE>	waveData;		//���y�f�[�^
	std::string			fileName;		//�t�@�C����
};