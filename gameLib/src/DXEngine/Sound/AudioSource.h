#pragma once
#include <string>
#include "Audio.h"
#include "PCM.h"
#include "../../DXEngine/Math/Math.h"


namespace AudioSystem
{
	class AudioSource
	{
	private:
		struct AudioData
		{
			IXAudio2SubmixVoice*	subMixVoice;
			XAudio2Callback			voiceCallback;	//コールバック
			X3DAUDIO_DSP_SETTINGS	dsp;			//X3DAudioCalculateの呼び出し結果を受け取る
			XAUDIO2_BUFFER			buf;			//音源格納用のバッファ
			IXAudio2SourceVoice*	source;			//ソースヴォイス(音源が格納される)
			XAUDIO2_VOICE_STATE		xState;			//ソースの情報格納用
			X3DAUDIO_EMITTER		emitter;		//3Dオーディオソースの定義
			X3DAUDIO_LISTENER		listener;		//リスナー位置
			bool					is3DAudio;		//3D音源フラグ
		};
	public:
		//!@brief	コンストラクタ
		AudioSource();
		//!@brief	デストラクタ
		~AudioSource();
	public:
		//!@brief	ソースのロード
		//!@param[in]	filePath	ファイルパス
		//!@param[in]	is3DSoundFlag	3Dサウンドのフラグ
		bool	Load(const std::string& filePath, bool is3DSoundFlag);
		//!@brief	BGMの再生
		void	PlayBGM(int loopNum = XAUDIO2_LOOP_INFINITE, float gain = 1.0f, float pitch = 1.0f);
		//!@brief	SEの再生
		void	PlaySE(int loopNum = 0, float gain = 1.0f, float pitch = 1.0f);
		//!@brief	再生の停止
		void	Stop() const;
		//!@brief	再生の一時停止
		void	Pause();
		//!@brief	ボリューム(0～1)の間
		void	SetVolume(const float volume);
		//!@brief	3Dリスナーの位置を設定
		//!@note	3Dサウンドを使用するときのみ
		void	SetListener(const Math::Vector3& listenerPos);
		//!@brief	曲の終端に来たらループを停止させる
		void	ExitLoop() const;
		//!@brief	ループ区間を設定
		void	SetLoopPoint(const UINT32 begin, const UINT32 end);
		//!@brief	ループの方法を設定
		void	SetLoopNum(int loopNum);
		//!@brief	破棄
		void	Destroy();
		//!@brief	現在のサンプラー時間を取得
		UINT64	GetCurrentSampleTime() const;
		//!@brief	音源の取得
		IXAudio2SourceVoice*	GetSource() const;
		//!@brief	チャンネルの取得
		WORD		GetChannels() const;
	private:
		//!@brief	ソースの情報の取得
		void		GetState();
	private:
		AudioData*		data;
		PCM*			pcm;
		Audio			audioEngine;
	};


	class AudioListener
	{
	public:
		AudioListener();
		AudioListener(const Math::Vector3& position);
	private:
		X3DAUDIO_LISTENER		listener;		//リスナー位置
	};
}