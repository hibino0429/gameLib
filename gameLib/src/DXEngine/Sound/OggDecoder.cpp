#include "OggDecoder.h"


namespace AudioSystem
{
	OggDecoder::OggDecoder()
		:data(nullptr)
		,size(0)
	{
		SecureZeroMemory(&fmt, sizeof(WAVEFORMATEX));
	}

	OggDecoder::~OggDecoder()
	{
		if (data != nullptr)
		{
			delete data;
			data = nullptr;
		}
		ov_clear(&oggBinFile);
	}

	bool OggDecoder::Load(const std::string & filePath)
	{
		if (!IsOgg(filePath)) { return false; }
		ov_fopen(filePath.c_str(), &oggBinFile);
		vorbis_info*	info = ov_info(&oggBinFile, -1);

		fmt.wFormatTag = WAVE_FORMAT_PCM;
		fmt.nChannels = static_cast<WORD>(info->channels);
		fmt.nSamplesPerSec = info->rate;
		fmt.wBitsPerSample = 16;
		fmt.nBlockAlign = fmt.wBitsPerSample / 8 * fmt.nChannels;
		fmt.nAvgBytesPerSec = fmt.nSamplesPerSec * fmt.nBlockAlign;
		fmt.cbSize = 0;

		size = static_cast<UINT>(info->channels * info->rate * info->channels * ov_time_total(&oggBinFile, -1));
		data = new char[size];

		UINT loadSize = 4096;
		UINT readSize = 0;
		UINT pos = 0;

		while (1)
		{
			readSize = ov_read(&oggBinFile, &data[pos], loadSize, 0, 2, 1, nullptr);
			if (readSize == 0 || pos + readSize >= size) { break; }
			pos += readSize;
			if (pos + loadSize >= size)
			{
				loadSize = size - pos;
			}
		}
		return true;
	}

	const WAVEFORMATEX & OggDecoder::GetWaveFmtEx() const
	{
		return fmt;
	}

	const BYTE * OggDecoder::GetWaveData() const
	{
		return (BYTE*)data;
	}

	const size_t AudioSystem::OggDecoder::GetWaveByteSize() const
	{
		return size;
	}

	bool	OggDecoder::IsOgg(const std::string & filePath)
	{
		FILE*	fp = nullptr;
		char c[3];

		fopen_s(&fp, filePath.c_str(), "rb");
		if (fp == nullptr) { return false; }
		fread_s(c, sizeof(c), 3, 1, fp);
		fclose(fp);

		bool isogg = (c[0] == 'O') && (c[1] == 'g') && (c[2] == 'g');
		return isogg;
	}
}