#pragma once

#include <string>
#include "../../src/GameSystem/Fbx/Fbx.h"
#include "../../src/DXEngine/PrimitiveData/PrimitiveData.h"
#include "../../src/DXEngine/Math/Math.h"
#include "../../src/Component/AnimationData/AnimationData.h"

//----------------------------------------------------------------------------------------
//!@class		Model
//!@brief	���f���������܂�
//----------------------------------------------------------------------------------------
class Model
{
public:
	Model();
	//!@brief	�R���X�g���N�^
	//!@param[in]	filePath	�t�@�C���p�X
	Model(const std::string& filePath);
	~Model();

	void	UpDate();
	void	Render();
	//!@brief	�ʒu�̐ݒ�
	void	SetPos(const Math::Vector3& pos);

	//!@brief	�X�P�[���̐ݒ�
	void	SetScale(const Math::Vector3& scale);
private:
	//!@brief	�C���v�b�g���C�A�E�g�̍쐬
	void	CreateInputLayout();
	//!@brief	�萔�o�b�t�@�̍쐬
	void	CreateConstantBuffer();
public:
	//!@brief	�A�j���[�V�����̍X�V
	//!@brief	�A�j���[�V������؂�ւ���Ƃ��ɌĂ�
	//!@brief	�p�ɂɌĂԂƂ��܂������Ȃ�
	//!@param[in]	animationNumber	�X�V����A�j���[�V�����ԍ�
	void	UpDateAnimation(const int& upDateAnimationNumber);
public:
	//!@brief	�}�g���b�N�X�̐ݒ�
	//void	SetMatrix(Camera* camera);
private:
	//�萔�o�b�t�@
	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4	world;
		DirectX::XMFLOAT4X4	view;
		DirectX::XMFLOAT4X4	projection;
	};
private:
	VertexShader*	vertexShader;
	PixelShader*	pixelShader;
	ID3D11Buffer*	constantBuf;
	Primitive*		primitive;
	FbxModel*		fbxModel;
	Math::Vector3	pos;
	Math::Vector3	angle;
	Math::Vector3	scale;
	AnimationData*	animationData;	
};