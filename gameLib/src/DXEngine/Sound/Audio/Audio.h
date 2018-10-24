#pragma once
#include <atlbase.h>
#include <XAudio2.h>
#include <string>
#include "../../src/DXEngine/Sound/Wave/Wave.h"

#pragma comment(lib,"XAudio2.lib")


//-----------------------------------------------------------------------------------
//!@class		Audio
//!@brief	Soundを扱うクラス
//!@brief	Soundの再生・停止・音源の破棄などを行う
//-----------------------------------------------------------------------------------
class SoundSource
{
public:
	//!@brief	コンストラクタ
	SoundSource();
	//!@brief	コンストラクタ
	//!@param[in]	sound	サウンドソース
	SoundSource(SoundSource& sound);
	//!@brief	デストラクタ
	~SoundSource();

	//!@brief	サウンドのロード
	//!@param[in]	filePath	ファイルのパス
	bool	Load(const std::string& filePath);
	//!@brief	BGMの再生
	//!@param[in]	loopNum	ループ
	//!@param[in]	gain	音量
	//!@param[in]	pitch	ピッチ
	void	PlayBGM(int loopNum = XAUDIO2_LOOP_INFINITE, float gain = 1.0f, float pitch = 1.0f);
	//!@brief	SEの再生
	//!@param[in]	gain	音量
	//!@param[in]	pitch	ピッチ
	void	PlaySE(float gain = 1.0f, float pitch = 1.0f);

	//!@brief	一時停止
	void	Pause();
	//!@brief	停止
	void	Stop();
	//!@brief	ソースの破棄
	void	Destory();

private:
	XAUDIO2_BUFFER			audiobuf;	//音源格納バッファ

public:
	IXAudio2SourceVoice*	source;		//サウンドソース
	Wave					wave;
};



//---------------------------------------------------------------------------------
//!@class		SoundSystem
//!@brief	サウンドのシステムを扱うクラス
//!@brief	サウンドを管理する
//---------------------------------------------------------------------------------
class SoundSystem
{
public:
	//!@brief	コンストラクタ
	SoundSystem();
	//!@brief	デストラクタ
	~SoundSystem();

	//!@brief	ソースボイスの登録
	//!@param[in]	source サウンドソース
	bool	AddSource(SoundSource& source);

	//!@brief	サウンド全体の音量調整
	//!@brief	gain	音量
	void	SetMasterGain(float gain);
	//!@brief	サウンドの破棄
	//!@param[in]	source	ソース
	void	DestorySystem(SoundSource& source);

private:
	//!@brief	サウンドシステムの生成
	bool	Create();

private:
	IXAudio2*				xAudio2;
	IXAudio2MasteringVoice*	master;
};