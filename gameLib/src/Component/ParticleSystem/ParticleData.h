#pragma once
//#include "Effekseer.h"
//#include "EffekseerRendererDX11.h"
//#include "EffekseerSoundXAudio2.h"

#include "../Effekseer/include/Effekseer.h"
#include "../Effekseer/include/EffekseerRendererDX11.h"
#include "../Effekseer/include/EffekseerSoundXAudio2.h"



#if defined(_DEBUG)
#pragma comment(lib, "Effekseer.Debug.lib" )
#pragma comment(lib, "EffekseerRendererDX11.Debug.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Debug.lib" )
#else
#pragma comment(lib, "Effekseer.Release.lib" )
#pragma comment(lib, "EffekseerRendererDX11.Release.lib" )
#pragma comment(lib, "EffekseerSoundXAudio2.Release.lib" )
#endif


//--------------------------------------------
//!@class		ParticleÇÃÉfÅ[É^
//--------------------------------------------
struct ParticleData
{
	EffekseerRenderer::Renderer* renderer;
	Effekseer::Manager* manager;
	Effekseer::Effect*	effect;
	Effekseer::Handle	handle;
	unsigned int		maxSprits;
	bool				playFlag;
};