#pragma once
#include "../../src/DXEngine/DXDevice/DXDevice.h"


//----------------------------------------------------------------------------------
//�T�v: �V�F�[�_������
//----------------------------------------------------------------------------------
class PixelShader
{
public:
	//!@brief	�R���X�g���N�^
	PixelShader();
	//!@brief	�f�X�g���N�^
	~PixelShader();

	//!@brief		�쐬
	//!@param[in]	fileName	�t�@�C����
	//!@return		���� true ���s false
	bool	Create(const std::string& fileName);

	//!@brief		�ݒ�
	void	Set();

private:
	ID3D11PixelShader*		pixelShader;
};