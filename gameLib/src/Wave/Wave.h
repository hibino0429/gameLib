#pragma once
#pragma comment(lib,"winmm.lib")
#include <Windows.h>
#include <mmsystem.h>
#include <vector>
#include <string>


//--------------------------------------------------------------------------------
//!@class		Wave
//!@brief	Waveを扱うクラス
//--------------------------------------------------------------------------------
class Wave
{
public:
	//!@brief	コンストラクタ
	Wave();
	//!@brief	コンストラクタ
	~Wave();

	//!@brief	Waveのロード
	//!@param[in]	filePath	ファイルパス
	//!@return 成功なら true 失敗なら false
	bool	Load(const std::string& filePath);
	//!@brief	Waveフォーマットの取得
	//!@return	WaveFormat	Waveフォーマット
	const WAVEFORMATEX&	GetWaveFormatEx() const;
	//!@brief	ファイル名の取得
	//!@return	fileName	ファイル名
	const std::string&	GetFileName() const;
	//!@brief	Waveデータの取得
	//!@return Waveデータ
	const BYTE*	GetWaveData() const;
	//!@brief	Waveデータのサイズの取得
	//!@return Waveデータのサイズ
	const size_t	GetWaveSize() const;

private:

	//!@brief	Waveファイルを開く
	//!@param[in]	filePath	ファイルパス
	//!@return	成功なら true 失敗なら false
	bool	Open(const std::string& filePath);
	//!@brief	Waveファイルを閉じる
	//!@return	成功なら true 失敗なら false
	bool	Close();
	//!@brief	WaveFormatを読み込む
	//!@return	成功なら true 失敗なら false
	bool	ReadToWaveFormat();
	//!@brief	WaveDataにWaveデータを読み込む
	//!@return	成功なら true 失敗なら false
	bool	ReadToWaveData();
	//!@brief	Waveヘッダがあるかチェック
	//!@return	成功なら true 失敗なら false
	bool	IsWaveHeader();
	//!@brief	FMTチャンクがあるかチェック
	//!@return	成功なら true 失敗なら false
	bool	IsFMTChunk();
	//!@brief	DATAチャンクがあるかチェック
	//!@return	成功なら true 失敗なら false
	bool	IsDataChunk();


private:
	HMMIO		mmio;	//MMIOハンドル
	MMCKINFO	riff;	//RIFFチャンク
	MMCKINFO	fmt;	//FMTチャンク
	MMCKINFO	data;	//DATAチャンク
	WAVEFORMATEX		waveFormat;		//フォーマット構造体
	std::vector<BYTE>	waveData;		//音楽データ
	std::string			fileName;		//ファイル名
};