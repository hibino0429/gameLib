#pragma once
#include "../../src/DXEngine/DXDevice/DXDevice.h"


//----------------------------------------------------------------------------------
//概要: シェーダを扱う
//----------------------------------------------------------------------------------
class PixelShader
{
public:
	//!@brief	コンストラクタ
	PixelShader();
	//!@brief	デストラクタ
	~PixelShader();

	//!@brief		作成
	//!@param[in]	fileName	ファイル名
	//!@return		成功 true 失敗 false
	bool	Create(const std::string& fileName);

	//!@brief		設定
	void	Set();

private:
	ID3D11PixelShader*		pixelShader;
};