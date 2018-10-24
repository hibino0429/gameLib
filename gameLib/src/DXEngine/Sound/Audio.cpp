#include "Audio.h"
#include <memory>
#include <iostream>



namespace AudioSystem
{
	XAUDIO2_VOICE_DETAILS	Audio::SingleAudio::voiceDetails;	
	ATL::CComPtr<IXAudio2>	Audio::SingleAudio::xAudio2 = 0;		
	X3DAUDIO_HANDLE			Audio::SingleAudio::x3DInstance;
	IXAudio2MasteringVoice*	Audio::SingleAudio::master = 0;
	Audio::EngineCallBack	Audio::SingleAudio::engineCallBack;

	Audio::Audio()
		: singleAudio()
	{
	
	}

	Audio::~Audio()
	{
		
	}

	IXAudio2 * Audio::GetXAudio2() const
	{
		return singleAudio.GetXAudio2();
	}

	IXAudio2MasteringVoice * Audio::GetMaster() const
	{
		return singleAudio.GetMaster();
	}

	X3DAUDIO_HANDLE & Audio::Get3DInstance()
	{
		return singleAudio.Get3DInstance();
	}

	XAUDIO2_VOICE_DETAILS & Audio::GetVoiceDetails()
	{
		return singleAudio.GetVoiceDetails();
	}

	void Audio::SetMasterGain(float gain)
	{
		singleAudio.SetMasterGain(gain);
	}

	void Audio::Create()
	{
		singleAudio.Create();
	}




	Audio::SingleAudio::SingleAudio()
	{
		CoInitializeEx(nullptr, COINIT_MULTITHREADED);
		SecureZeroMemory(&x3DInstance, sizeof(x3DInstance));
		SecureZeroMemory(&voiceDetails, sizeof(voiceDetails));
		Create();
	}

	Audio::SingleAudio::~SingleAudio()
	{
		xAudio2->UnregisterForCallbacks(&engineCallBack);
		if (master != nullptr)
		{
			master->DestroyVoice();
			master = nullptr;
		}
		CoUninitialize();
	}

	void Audio::SingleAudio::Create()
	{
		try {
			xAudio2.Release();
			//XAudio2の初期化
			auto hr = XAudio2Create(&xAudio2, 0, XAUDIO2_DEFAULT_PROCESSOR);
			if (FAILED(hr))
			{
				throw "XAudio2 Initialize failed";
			}
			//マスターボイスの生成
			hr = xAudio2->CreateMasteringVoice(
				&master,
				XAUDIO2_DEFAULT_CHANNELS,
				XAUDIO2_DEFAULT_SAMPLERATE,
				0, 0, nullptr);
			if (FAILED(hr))
			{
				throw "MasteringVoice Initialize failed";
			}
			//detailの初期化
			master->GetVoiceDetails(&voiceDetails);
			//3Dインターフェイスの初期化
			DWORD	speakerMask;

			master->GetChannelMask(&speakerMask);
			hr = X3DAudioInitialize(speakerMask, X3DAUDIO_SPEED_OF_SOUND, x3DInstance);
			if (FAILED(hr))
			{
				throw "X3DAudio Initialize failed";
			}
		}
		catch (const char* e)
		{
			std::cerr << e << std::endl;
		}
		//コールバックリストに追加
		xAudio2->RegisterForCallbacks(&engineCallBack);
	}

	IXAudio2 * Audio::SingleAudio::GetXAudio2() 
	{
		return xAudio2.p;
	}

	IXAudio2MasteringVoice * Audio::SingleAudio::GetMaster() 
	{
		return master;
	}

	X3DAUDIO_HANDLE & Audio::SingleAudio::Get3DInstance()
	{
		return x3DInstance;
	}

	XAUDIO2_VOICE_DETAILS & Audio::SingleAudio::GetVoiceDetails()
	{
		return voiceDetails;
	}

	void Audio::SingleAudio::SetMasterGain(float gain)
	{
		master->SetVolume(gain);
	}

}