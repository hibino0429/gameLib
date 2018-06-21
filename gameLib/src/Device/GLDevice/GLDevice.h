#pragma once


//-------------------------------------------------------------
//!@class		GLDevice
//!@brief	OpenGLのデバイスを提供します
//!@brief	デバイスの作成や、機能の提供などを行います
//-------------------------------------------------------------
class GLDevice
{
public:
	//!@brief コンストラクタ
	GLDevice();
	//!@brief デストラクタ
	virtual ~GLDevice();

public:
	//!@brief	生成処理
	bool	Create();
	//!@brief	解放処理
	bool	Release();

};

