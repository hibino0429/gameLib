#pragma once
#include "../../src/Device/Device.h"

//-------------------------------------------------------------
//!@class		GLDevice
//!@brief	OpenGLのデバイスを提供します
//!@brief	デバイスの作成や、機能の提供などを行います
//-------------------------------------------------------------
class GLDevice : public Device
{
public:
	//!@brief コンストラクタ
	GLDevice();
	//!@brief デストラクタ
	virtual ~GLDevice();

public:
	//!@brief 生成
	bool	Create();
	//!@brief 更新
	void	Run();
	//!@brief 終了
	bool	CleanUp();
	//!@brief 消失
	bool	Remove();

};

