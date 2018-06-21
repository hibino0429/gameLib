#pragma once


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
	virtual void	Run() = 0;
	virtual	bool	CleanUp() = 0;
	virtual bool	Remove() = 0;
};
