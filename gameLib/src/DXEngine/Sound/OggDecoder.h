#pragma once
#include <vorbis/vorbisfile.h>
#include <Windows.h>
#include <string>
#pragma comment (lib, "libogg_static.lib")
#pragma comment (lib, "libvorbis_static.lib")
#pragma comment (lib, "libvorbisfile_static.lib")


namespace AudioSystem
{
	//-----------------------------------------------------
	//!@class		OggDecoder
	//-----------------------------------------------------
	class OggDecoder
	{
	public:
		//!@brief	�R���X�g���N�^
		OggDecoder();
		//!@brief	�f�X�g���N�^
		~OggDecoder();
	public:
		//!@brief	���[�h����
		bool	Load(const std::string& filePath);
		//!@brief	WAVE�t�H�[�}�b�g�̎擾
		const WAVEFORMATEX&	GetWaveFmtEx() const;
		//!@brief	WAVE�f�[�^�̎擾
		const BYTE*	GetWaveData() const;
		//!@brief	WAVE�f�[�^�̃T�C�Y���擾
		const size_t	GetWaveByteSize() const;
	private:
		//!@brief	ogg�����ׂ�
		bool	IsOgg(const std::string& filePath);
	private:
		OggVorbis_File	oggBinFile;
		WAVEFORMATEX	fmt;
		UINT			size;
		char*			data;
	};
}