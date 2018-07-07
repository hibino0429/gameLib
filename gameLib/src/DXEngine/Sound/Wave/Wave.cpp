#include "Wave.h"


//!@brief	�R���X�g���N�^
Wave::Wave()
{
	mmio = nullptr;
	SecureZeroMemory(&fmt, sizeof(fmt));
	waveData.clear();
}

//!@brief	�R���X�g���N�^
Wave::~Wave()
{
	Close();
}

//!@brief	Wave�̃��[�h
//!@param[in]	filePath	�t�@�C���p�X
//!@return �����Ȃ� true ���s�Ȃ� false
bool	Wave::Load(const std::string& filePath)
{
	if (!Open(filePath.c_str()))
	{
		return false;
	}
	if (!IsWaveHeader())
	{
		return false;
	}
	if (!IsFMTChunk())
	{
		return false;
	}
	if (!ReadToWaveFormat())
	{
		return false;
	}

	//�ǂݍ��݈ʒu��擪�֖߂�
	mmioAscend(mmio, &fmt, SEEK_SET);

	if (!IsDataChunk())
	{
		return false;
	}
	if (!ReadToWaveData())
	{
		return false;
	}
	Close();
	return true;
}
//!@brief	Wave�t�H�[�}�b�g�̎擾
//!@return	WaveFormat	Wave�t�H�[�}�b�g
const WAVEFORMATEX&	Wave::GetWaveFormatEx() const
{
	return waveFormat;
}

//!@brief	�t�@�C�����̎擾
//!@return	fileName	�t�@�C����
const std::string&	Wave::GetFileName() const
{
	return fileName;
}

//!@brief	Wave�f�[�^�̎擾
//!@return Wave�f�[�^
const BYTE*	Wave::GetWaveData() const
{
	return &waveData[0];
}

//!@brief	Wave�f�[�^�̃T�C�Y�̎擾
//!@return Wave�f�[�^�̃T�C�Y
const size_t	Wave::GetWaveSize() const
{
	return waveData.size();
}


//!@brief	Wave�t�@�C�����J��
//!@param[in]	filePath	�t�@�C���p�X
//!@return	�����Ȃ� true ���s�Ȃ� false
bool	Wave::Open(const std::string& filePath)
{
	fileName = filePath;
	mmio = mmioOpenA(&fileName[0], nullptr, MMIO_READ);
	if (!mmio)
	{
		return false;
	}
	return true;
}

//!@brief	Wave�t�@�C�������
//!@return	�����Ȃ� true ���s�Ȃ� false
bool	Wave::Close()
{
	if (mmioClose(mmio, MMIO_FHOPEN) == MMIOERR_CANNOTWRITE)
	{
		return false;
	}
	return true;
}

//!@brief	WaveFormat��ǂݍ���
//!@return	�����Ȃ� true ���s�Ȃ� false
bool	Wave::ReadToWaveFormat()
{
	LONG	readSize = mmioRead(mmio, reinterpret_cast<HPSTR>(&waveFormat), fmt.cksize);
	switch (readSize)
	{
	case 0:		break;
	case -1:	break;
	default:
		if (readSize != fmt.cksize)
		{
			return false;
		}
		break;
	}
	return true;
}

//!@brief	WaveData��Wave�f�[�^��ǂݍ���
//!@return	�����Ȃ� true ���s�Ȃ� false
bool	Wave::ReadToWaveData()
{
	waveData.resize(data.cksize);
	if (mmioRead(mmio, reinterpret_cast<HPSTR>(&waveData[0]), data.cksize) != data.cksize)
	{
		return false;
	}
	return true;
}

//!@brief	Wave�w�b�_�����邩�`�F�b�N
//!@return	�����Ȃ� true ���s�Ȃ� false
bool	Wave::IsWaveHeader()
{
	riff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(mmio, &riff, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR)
	{
		return false;
	}
	return true;
}

//!@brief	FMT�`�����N�����邩�`�F�b�N
//!@return	�����Ȃ� true ���s�Ȃ� false
bool	Wave::IsFMTChunk()
{
	fmt.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(mmio, &fmt, &riff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		return false;
	}
	return true;
}

//!@brief	DATA�`�����N�����邩�`�F�b�N
//!@return	�����Ȃ� true ���s�Ȃ� false
bool	Wave::IsDataChunk()
{
	data.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmio, &data, &riff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		return false;
	}
	return true;
}