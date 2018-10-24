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
		//!@brief	コンストラクタ
		OggDecoder();
		//!@brief	デストラクタ
		~OggDecoder();
	public:
		//!@brief	ロード処理
		bool	Load(const std::string& filePath);
		//!@brief	WAVEフォーマットの取得
		const WAVEFORMATEX&	GetWaveFmtEx() const;
		//!@brief	WAVEデータの取得
		const BYTE*	GetWaveData() const;
		//!@brief	WAVEデータのサイズを取得
		const size_t	GetWaveByteSize() const;
	private:
		//!@brief	oggか調べる
		bool	IsOgg(const std::string& filePath);
	private:
		OggVorbis_File	oggBinFile;
		WAVEFORMATEX	fmt;
		UINT			size;
		char*			data;
	};
}