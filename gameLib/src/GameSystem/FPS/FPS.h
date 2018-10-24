#pragma once
#include <atlbase.h>

//---------------------------------------------------------------------------------
//!@class		FPS
//!@brief	Frame/Per/Secondを計測するクラス
//!@brief	FPSを固定させる
//---------------------------------------------------------------------------------
class FPS
{
public:
	//!@brief	コンストラクタ
	FPS();
	//!@brief	デストラクタ
	~FPS();

	//!@brief	FPSの同期をさせる
	void	Run();
	//!@brief	アプリケーション起動時からの時間を返す
	//!@return	時間
	float	GetTime() const;
	//!@brief	前のフレームと今のフレームの時間差を返す
	//!@return 時間差
	float	GetDeltaTime() const;
	//!@brief	現在のフレームレートを返す
	//!@return フレームレート
	int		GetFrameRate() const;

private:
	LARGE_INTEGER GetCounter() const;
	LARGE_INTEGER GetCountFrequency() const;
private:
	float	time;
	float	deltaTime;
	int		frameRate;
	float	second;
	int		frameCount;
	LARGE_INTEGER preCount;
	LARGE_INTEGER frequency;

};