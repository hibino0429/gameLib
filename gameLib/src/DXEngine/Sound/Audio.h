#pragma once
#pragma warning (disable : 4100)	//�R�[���o�b�N�֐�
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
			//!@brief	�T�E���h�V�X�e���̍쐬
			static void	Create();
			//!@brief	XAudio2�̃C���^�[�t�F�C�X�̎擾
			static IXAudio2*	GetXAudio2();
			//!@brief	�}�X�^�����O�{�C�X�̎擾
			static IXAudio2MasteringVoice*	GetMaster();
			//!@brief	3D�C���X�^���X�̎擾
			static X3DAUDIO_HANDLE&	Get3DInstance();
			//!@brief	�{�C�X�̏ڍׂ��擾
			static XAUDIO2_VOICE_DETAILS&	GetVoiceDetails();
			//!@brief	�}�X�^�[�̉��ʂ̒���
			static void	SetMasterGain(float gain);
		private:
			static XAUDIO2_VOICE_DETAILS	voiceDetails;	//�쐬�t���O�A���̓`�����l���A�{�C�X�̃T���v�����[�g�̏��
			static ATL::CComPtr<IXAudio2>	xAudio2;		//�C���^�[�t�F�C�X
			static X3DAUDIO_HANDLE			x3DInstance;	//3D�C���X�^���X
			static IXAudio2MasteringVoice*	master;			//�}�X�^�����O�{�C�X
			static EngineCallBack			engineCallBack;	//�R�[���o�b�N
		};
	public:
		//!@brief	�R���X�g���N�^
		Audio();
		//!@brief	�f�X�g���N�^
		~Audio();
	public:
		//!@brief	XAudio2�̃C���^�[�t�F�C�X�̎擾
		IXAudio2*	GetXAudio2() const;
		//!@brief	�}�X�^�����O�{�C�X�̎擾
		IXAudio2MasteringVoice*	GetMaster() const;
		//!@brief	3D�C���X�^���X�̎擾
		X3DAUDIO_HANDLE&	Get3DInstance();
		//!@brief	�{�C�X�̏ڍׂ��擾
		XAUDIO2_VOICE_DETAILS&	GetVoiceDetails();
		//!@brief	�}�X�^�[�̉��ʂ̒���
		void	SetMasterGain(float gain);
	private:
		//!@brief	�T�E���h�V�X�e���̍쐬
		void	Create();
	private:
		SingleAudio		singleAudio;
	};
}