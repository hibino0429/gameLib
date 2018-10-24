#include "PCM.h"
#include <iostream>


namespace AudioSystem
{
	Wave::Wave(const std::string & filePath)
	{
		try {
			if (!Load(filePath))
			{
				throw "Wave Failed to load";
			}
		}
		catch (const char* e)
		{
			std::cerr << e << std::endl;
		}
	}
	bool Wave::Load(const std::string & filePath)
	{
		return data.Load(filePath);
	}

	const WAVEFORMATEX & Wave::GetWaveFmtEx() const
	{
		return data.GetWaveFmtEx();
	}

	const BYTE * Wave::GetWaveData() const
	{
		return data.GetWaveData();
	}

	const size_t Wave::GEtWaveByteSize() const
	{
		return data.GetWaveByteSize();
	}

	const UINT64 Wave::GetSample() const
	{
		return data.GetWaveFmtEx().nSamplesPerSec;
	}


	Ogg::Ogg(const std::string & filePath)
	{
		try {
			if (!Load(filePath))
			{
				throw "Ogg Failed to load";
			}
		}
		catch (const char* e)
		{
			std::cerr << e << std::endl;
		}
	}

	bool Ogg::Load(const std::string & filePath)
	{
		return data.Load(filePath);
	}

	const WAVEFORMATEX & Ogg::GetWaveFmtEx() const
	{
		return data.GetWaveFmtEx();
	}

	const BYTE * Ogg::GetWaveData() const
	{
		return data.GetWaveData();
	}

	const size_t Ogg::GEtWaveByteSize() const
	{
		return data.GetWaveByteSize();
	}

	const UINT64 Ogg::GetSample() const
	{
		return data.GetWaveFmtEx().nSamplesPerSec;
	}
}