#pragma once
#pragma warning (disable : 4100)	//コールバック関数
#include <atlbase.h>
#include <Windows.h>
#include <xaudio2.h>
#include <x3daudio.h>

#pragma comment(lib,"xaudio2")


namespace AudioSystem
{
	class XAudio2Callback : public IXAudio2VoiceCallback
	{
	public:
		XAudio2Callback() 
			: handle(CreateEventEx(nullptr,nullptr,0,EVENT_MODIFY_STATE | SYNCHRONIZE))
		{}
		virtual ~XAudio2Callback()
		{
			CloseHandle(handle);
		}
		void	__stdcall OnStreamEnd() override
		{
			SetEvent(handle);
		}
		void	__stdcall OnBufferStart(void* bufferContext) override
		{
			SetEvent(handle);
		}
		void	__stdcall OnVoiceProcessingPassStart(UINT32 byteRequired) override
		{}
		void	__stdcall OnVoiceProcessingPassEnd() override
		{}
		void	__stdcall OnBufferEnd(void* bufferContext) override
		{}
		void	__stdcall OnLoopEnd(void* bufferContext) override
		{}
		void	__stdcall OnVoiceError(void* bufferContext, HRESULT error) override
		{}
	public:
		HANDLE		handle;
	};

	//--------------------------------------------------------------
	//!@class		Audio
	//--------------------------------------------------------------
	class Audio
	{
	public:
		class EngineCallBack : public IXAudio2EngineCallback
		{
		public:
			void __stdcall OnProcessingPassEnd() override {}
			void __stdcall OnProcessingPassStart() override {}
			void __stdcall OnCriticalError(HRESULT error) override {}
		};
	private:
		class SingleAudio
		{
		public: 
			SingleAudio();
			~SingleAudio();
		public:
			//!@brief	サウンドシステムの作成
			static void	Create();
			//!@brief	XAudio2のインターフェイスの取得
			static IXAudio2*	GetXAudio2();
			//!@brief	マスタリングボイスの取得
			static IXAudio2MasteringVoice*	GetMaster();
			//!@brief	3Dインスタンスの取得
			static X3DAUDIO_HANDLE&	Get3DInstance();
			//!@brief	ボイスの詳細を取得
			static XAUDIO2_VOICE_DETAILS&	GetVoiceDetails();
			//!@brief	マスターの音量の調整
			static void	SetMasterGain(float gain);
		private:
			static XAUDIO2_VOICE_DETAILS	voiceDetails;	//作成フラグ、入力チャンネル、ボイスのサンプルレートの情報
			static ATL::CComPtr<IXAudio2>	xAudio2;		//インターフェイス
			static X3DAUDIO_HANDLE			x3DInstance;	//3Dインスタンス
			static IXAudio2MasteringVoice*	master;			//マスタリングボイス
			static EngineCallBack			engineCallBack;	//コールバック
		};
	public:
		//!@brief	コンストラクタ
		Audio();
		//!@brief	デストラクタ
		~Audio();
	public:
		//!@brief	XAudio2のインターフェイスの取得
		IXAudio2*	GetXAudio2() const;
		//!@brief	マスタリングボイスの取得
		IXAudio2MasteringVoice*	GetMaster() const;
		//!@brief	3Dインスタンスの取得
		X3DAUDIO_HANDLE&	Get3DInstance();
		//!@brief	ボイスの詳細を取得
		XAUDIO2_VOICE_DETAILS&	GetVoiceDetails();
		//!@brief	マスターの音量の調整
		void	SetMasterGain(float gain);
	private:
		//!@brief	サウンドシステムの作成
		void	Create();
	private:
		SingleAudio		singleAudio;
	};
}