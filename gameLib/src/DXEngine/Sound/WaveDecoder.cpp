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
		//読み込む位置を先頭へ
		mmioAscend(mmio, &fmt, SEEK_SET);
		if (!IsDATAChunk()) { return false; }
		if (!ReadToWaveData()) { return false; }
		//ファイルを閉じる
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
		//ファイル名のコピー
		mmio = mmioOpenA(&fileName[0], nullptr, MMIO_READ);
		if (!mmio)
		{
			MessageBoxA(nullptr, "Waveを開けませんでした", "WaveDecoder::Open()", MB_OK);
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
			MessageBoxA(nullptr, "FMTチャンクがありません", "WaveDecoder::IsFMTChunk()", MB_OK);
			return false;
		}
		return true;
	}
	bool	WaveDecoder::IsDATAChunk()
	{
		data.ckid = mmioFOURCC('d', 'a','t', 'a');
		if (mmioDescend(mmio, &data, &riff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
		{
			MessageBoxA(nullptr, "DATAチャンクがありません", "WaveDecoder::IsDATAChunk()", MB_OK);
			return false;
		}
		return true;
	}
	bool	WaveDecoder::ReadToWaveFmtEx()
	{
		//mmioReadが成功すると読み込んだサイズを返す
		//waveに情報を格納
		LONG readSize = mmioRead(mmio, reinterpret_cast<HPSTR>(&wave), fmt.cksize);
		switch (readSize)
		{
		case 0:		//それ以上読み込めない
			MessageBoxA(nullptr, "waveデータをこれ以上読み込めません", "WaveDecoder::ReadToWaveFmtEx()", MB_OK);
			break;
		case -1:	//ファイルの読み取りに失敗
			MessageBoxA(nullptr, "waveデータを読み込めませんでした", "WaveDecoder::ReadToWaveFmtEx()", MB_OK);
			break;
		default:
			if ((unsigned)readSize != fmt.cksize)
			{
				MessageBoxA(nullptr, "読み込んだwaveデータのサイズが異なります", "WaveDecoder::ReadToWaveFmtEx()", MB_OK);
				return false;
			}
		}
		return true;
	}
	bool	WaveDecoder::ReadToWaveData()
	{
		//Waveデータ用にリサイズ
		waveData.resize(data.cksize);
		if (mmioRead(mmio, reinterpret_cast<HPSTR>(&waveData[0]), data.cksize) != (signed)data.cksize)
		{
			MessageBoxA(nullptr, "読み込んだwaveデータのサイズが異なります", "WaveDecoder::ReadToWaveData()", MB_OK);
			return false;
		}
		return true;
	}
	bool	WaveDecoder::IsWaveHeader()
	{
		riff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
		if (mmioDescend(mmio, &riff, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR)
		{
			MessageBoxA(nullptr, "読み込んだwaveにヘッダがありません", "WaveDecoder::IsWaveHeader()", MB_OK);
			return false;
		}
		return true;
	}
}