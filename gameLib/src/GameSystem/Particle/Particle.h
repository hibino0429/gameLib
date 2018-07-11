#pragma once
#include "../../src/DXEngine/Math/Math.h"
//#include "Effekseer.h"
//#include "EffekseerRendererDX11.h"
//#include "EffekseerSoundXAudio2.h"
#include "../../src/DXEngine/Camera/Camera.h"

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

class Particle
{
private:
	static constexpr int MAX_SPRITS = 2000;
	EffekseerRenderer::Renderer* renderer;
	Effekseer::Manager* manager;
	Effekseer::Effect* effect;
	Effekseer::Handle handle;
	void Create();
	void Update();
	void EffectDraw(Camera& camera);
	void Init();
public:
	
	Math::Vector3 pos;
	Math::Vector3 scale;
	Math::Vector3 angle;
	Particle(const char* path);
	Particle();
	~Particle();
	void Load(const char* path);
	void Play();
	void Stop();
	void Draw(Camera &camera);

};

