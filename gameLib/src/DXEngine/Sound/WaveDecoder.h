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
		//!@brief	コンストラクタ
		WaveDecoder();
		//!@brief	デストラクタ
		~WaveDecoder();
	public:
		//!@brief	ロード処理
		//!@param[in]	filePath	ファイルパス
		bool	Load(const std::string& filePath);
		//!@brief	WAVEフォーマットを取得
		const WAVEFORMATEX&	GetWaveFmtEx() const;
		//!@brief	ファイル名の取得
		const std::string&	GetFileName() const;
		//!@brief	Waveデータを取得
		const BYTE*	GetWaveData() const;
		//!@brief	Waveデータのサイズの取得
		const size_t	GetWaveByteSize() const;
	private:
		//!@brief	Waveファイルオープン
		bool	Open(const std::string& filePath);
		//!@brief	Waveファイルクローズ
		bool	Close();
		//!@brief	WAVEFORMATEXにデータを読み込む
		bool	ReadToWaveFmtEx();
		//!@brief	WaveDataにWAVEデータを読み込む
		bool	ReadToWaveData();
		//!@brief	WAVEヘッダがあるかチェック
		bool	IsWaveHeader();
		//!@brief	FMTチャンクがあるかチェック
		bool	IsFMTChunk();
		//!@brief	DATAチャンクがあるかチェック
		bool	IsDATAChunk();
	private:
		HMMIO				mmio;		//MMIOハンドル
		MMCKINFO			riff;		//RIFFチャンク
		MMCKINFO			fmt;		//FMTチャンク
		MMCKINFO			data;		//DATAチャンク
		WAVEFORMATEX		wave;		//WAVEフォーマット構造体
		std::vector<BYTE>	waveData;	//音楽データ
		std::string			fileName;	//ファイル名
	};
}