#include "WaveDecoder.h"
#include <cstring>
#include <iostream>


namespace AudioSystem
{
	WaveDecoder::WaveDecoder()
		: mmio(nullptr)
	{
		SecureZeroMemory(&fmt, sizeof(fmt));
		waveData.clear();
	}
	WaveDecoder::~WaveDecoder()
	{
		Close();
	}
	bool	WaveDecoder::Load(const std::string& filePath)
	{
		if (!Open(filePath)) { return false; }
		if (!IsWaveHeader()) { return false; }
		if (!IsFMTChunk()) { return false; }
		if (!ReadToWaveFmtEx()) { return false; }
		//�ǂݍ��ވʒu��擪��
		mmioAscend(mmio, &fmt, SEEK_SET);
		if (!IsDATAChunk()) { return false; }
		if (!ReadToWaveData()) { return false; }
		//�t�@�C�������
		Close();
		return true;
	}
	const std::string&	WaveDecoder::GetFileName() const
	{
		return fileName;
	}
	const WAVEFORMATEX&	WaveDecoder::GetWaveFmtEx() const
	{
		return wave;
	}
	const BYTE*	WaveDecoder::GetWaveData() const
	{
		return &waveData[0];
	}
	const size_t WaveDecoder::GetWaveByteSize() const
	{
		return waveData.size();
	}

	bool	WaveDecoder::Open(const std::string& filePath)
	{
		fileName = filePath;
		//�t�@�C�����̃R�s�[
		mmio = mmioOpenA(&fileName[0], nullptr, MMIO_READ);
		if (!mmio)
		{
			MessageBoxA(nullptr, "Wave���J���܂���ł���", "WaveDecoder::Open()", MB_OK);
			return false;
		}
		return true;
	}
	bool	WaveDecoder::Close()
	{
		if (mmioClose(mmio, MMIO_FHOPEN) == MMIOERR_CANNOTWRITE)
		{
			return false;
		}
		return true;
	}
	bool	WaveDecoder::IsFMTChunk()
	{
		fmt.ckid = mmioFOURCC('f', 'm', 't', ' ');
		if (mmioDescend(mmio, &fmt, &riff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
		{
			MessageBoxA(nullptr, "FMT�`�����N������܂���", "WaveDecoder::IsFMTChunk()", MB_OK);
			return false;
		}
		return true;
	}
	bool	WaveDecoder::IsDATAChunk()
	{
		data.ckid = mmioFOURCC('d', 'a','t', 'a');
		if (mmioDescend(mmio, &data, &riff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
		{
			MessageBoxA(nullptr, "DATA�`�����N������܂���", "WaveDecoder::IsDATAChunk()", MB_OK);
			return false;
		}
		return true;
	}
	bool	WaveDecoder::ReadToWaveFmtEx()
	{
		//mmioRead����������Ɠǂݍ��񂾃T�C�Y��Ԃ�
		//wave�ɏ����i�[
		LONG readSize = mmioRead(mmio, reinterpret_cast<HPSTR>(&wave), fmt.cksize);
		switch (readSize)
		{
		case 0:		//����ȏ�ǂݍ��߂Ȃ�
			MessageBoxA(nullptr, "wave�f�[�^������ȏ�ǂݍ��߂܂���", "WaveDecoder::ReadToWaveFmtEx()", MB_OK);
			break;
		case -1:	//�t�@�C���̓ǂݎ��Ɏ��s
			MessageBoxA(nullptr, "wave�f�[�^��ǂݍ��߂܂���ł���", "WaveDecoder::ReadToWaveFmtEx()", MB_OK);
			break;
		default:
			if ((unsigned)readSize != fmt.cksize)
			{
				MessageBoxA(nullptr, "�ǂݍ���wave�f�[�^�̃T�C�Y���قȂ�܂�", "WaveDecoder::ReadToWaveFmtEx()", MB_OK);
				return false;
			}
		}
		return true;
	}
	bool	WaveDecoder::ReadToWaveData()
	{
		//Wave�f�[�^�p�Ƀ��T�C�Y
		waveData.resize(data.cksize);
		if (mmioRead(mmio, reinterpret_cast<HPSTR>(&waveData[0]), data.cksize) != (signed)data.cksize)
		{
			MessageBoxA(nullptr, "�ǂݍ���wave�f�[�^�̃T�C�Y���قȂ�܂�", "WaveDecoder::ReadToWaveData()", MB_OK);
			return false;
		}
		return true;
	}
	bool	WaveDecoder::IsWaveHeader()
	{
		riff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		if (mmioDescend(mmio, &riff, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR)
		{
			MessageBoxA(nullptr, "�ǂݍ���wave�Ƀw�b�_������܂���", "WaveDecoder::IsWaveHeader()", MB_OK);
			return false;
		}
		return true;
	}
}