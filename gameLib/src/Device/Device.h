#pragma once

//-------------------------------------------------------------
//追加するデバイスクラス



//-------------------------------------------------------------
//!@class		Device
//!@brief デバイスのインターフェイス
//-------------------------------------------------------------
class Device
{
public:
	//!@brief デストラクタ
	virtual ~Device() {};

	virtual bool	Create() = 0;
	virtual bool	Run() = 0;
	virtual	bool	CleanUp() = 0;
	virtual bool	Remove() = 0;
	virtual Device*	GetDevice() = 0;
};
