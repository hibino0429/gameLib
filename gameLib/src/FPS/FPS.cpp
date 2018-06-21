#include "FPS.h"


//!@brief	コンストラクタ
FPS::FPS()
	: frameCount(0)
	,frameRate(0)
	,deltaTime(0)
	,second(0)
{
	preCount = GetCounter();
	frequency = GetCountFrequency();
}

//!@brief	デストラクタ
FPS::~FPS()
{

}

//!@brief	FPSの同期をさせる
void	FPS::Run()
{
	LARGE_INTEGER count = GetCounter();
	deltaTime = static_cast<float>(count.QuadPart - preCount.QuadPart) / frequency.QuadPart;
	preCount = GetCounter();

	time += deltaTime;
	frameCount++;
	if (second >= 1.0f)
	{
		frameRate = frameCount;
		frameCount = 0;
		second -= 1.0f;
	}
}

//!@brief	アプリケーション起動時からの時間を返す
//!@return	時間
float	FPS::GetTime() const
{
	return time;
}

//!@brief	前のフレームと今のフレームの時間差を返す
//!@return 時間差
float	FPS::GetDeltaTime() const
{
	return deltaTime;
}

//!@brief	現在のフレームレートを返す
//!@return フレームレート
int		FPS::GetFrameRate() const
{
	return frameRate;
}



LARGE_INTEGER FPS::GetCounter() const
{
	LARGE_INTEGER	counter;
	QueryPerformanceCounter(&counter);
	return counter;
}

LARGE_INTEGER FPS::GetCountFrequency() const
{
	LARGE_INTEGER	frequency;
	QueryPerformanceFrequency(&frequency);
	return frequency;
}