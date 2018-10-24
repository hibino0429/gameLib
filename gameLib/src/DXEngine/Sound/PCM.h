#pragma once
#include "../../DXEngine/Sound/WaveDecoder.h"
#include "OggDecoder.h"


namespace AudioSystem
{
	class PCM
	{
	public:
		PCM() = default;
		virtual ~PCM() = default;
		virtual bool	Load(const std::string& filePath) = 0;
		virtual const WAVEFORMATEX&	GetWaveFmtEx() const = 0;
		virtual const BYTE*	GetWaveData() const = 0;
		virtual const size_t GEtWaveByteSize() const = 0;
		virtual const UINT64 GetSample() const = 0;
	};

	//------------------------------------------------
	//!@class		Wave
	//------------------------------------------------
	class Wave : public PCM
	{
	public:
		Wave(const std::string& filePath);
		virtual bool Load(const std::string & filePath) override;
		virtual const WAVEFORMATEX & GetWaveFmtEx() const override;
		virtual const BYTE * GetWaveData() const override;
		virtual const size_t GEtWaveByteSize() const override;
		virtual const UINT64 GetSample() const override;
	private:
		WaveDecoder		data;
	};

	//------------------------------------------------
	//!@class		Ogg
	//------------------------------------------------
	class Ogg : public PCM
	{
	public:
		Ogg(const std::string& filePath);
		virtual bool Load(const std::string & filePath) override;
		virtual const WAVEFORMATEX & GetWaveFmtEx() const override;
		virtual const BYTE * GetWaveData() const override;
		virtual const size_t GEtWaveByteSize() const override;
		virtual const UINT64 GetSample() const override;
	private:
		OggDecoder		data;
	};
}
