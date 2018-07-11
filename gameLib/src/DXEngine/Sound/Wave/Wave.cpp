#include "Wave.h"


//!@brief	コンストラクタ
Wave::Wave()
{
	mmio = nullptr;
	SecureZeroMemory(&fmt, sizeof(fmt));
	waveData.clear();
}

//!@brief	コンストラクタ
Wave::~Wave()
{
	Close();
}

//!@brief	Waveのロード
//!@param[in]	filePath	ファイルパス
//!@return 成功なら true 失敗なら false
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

	//読み込み位置を先頭へ戻す
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
//!@brief	Waveフォーマットの取得
//!@return	WaveFormat	Waveフォーマット
const WAVEFORMATEX&	Wave::GetWaveFormatEx() const
{
	return waveFormat;
}

//!@brief	ファイル名の取得
//!@return	fileName	ファイル名
const std::string&	Wave::GetFileName() const
{
	return fileName;
}

//!@brief	Waveデータの取得
//!@return Waveデータ
const BYTE*	Wave::GetWaveData() const
{
	return &waveData[0];
}

//!@brief	Waveデータのサイズの取得
//!@return Waveデータのサイズ
const size_t	Wave::GetWaveSize() const
{
	return waveData.size();
}


//!@brief	Waveファイルを開く
//!@param[in]	filePath	ファイルパス
//!@return	成功なら true 失敗なら false
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

//!@brief	Waveファイルを閉じる
//!@return	成功なら true 失敗なら false
bool	Wave::Close()
{
	if (mmioClose(mmio, MMIO_FHOPEN) == MMIOERR_CANNOTWRITE)
	{
		return false;
	}
	return true;
}

//!@brief	WaveFormatを読み込む
//!@return	成功なら true 失敗なら false
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

//!@brief	WaveDataにWaveデータを読み込む
//!@return	成功なら true 失敗なら false
bool	Wave::ReadToWaveData()
{
	waveData.resize(data.cksize);
	if (mmioRead(mmio, reinterpret_cast<HPSTR>(&waveData[0]), data.cksize) != data.cksize)
	{
		return false;
	}
	return true;
}

//!@brief	Waveヘッダがあるかチェック
//!@return	成功なら true 失敗なら false
bool	Wave::IsWaveHeader()
{
	riff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(mmio, &riff, nullptr, MMIO_FINDRIFF) != MMSYSERR_NOERROR)
	{
		return false;
	}
	return true;
}

//!@brief	FMTチャンクがあるかチェック
//!@return	成功なら true 失敗なら false
bool	Wave::IsFMTChunk()
{
	fmt.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(mmio, &fmt, &riff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		return false;
	}
	return true;
}

//!@brief	DATAチャンクがあるかチェック
//!@return	成功なら true 失敗なら false
bool	Wave::IsDataChunk()
{
	data.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(mmio, &data, &riff, MMIO_FINDCHUNK) != MMSYSERR_NOERROR)
	{
		return false;
	}
	return true;
}