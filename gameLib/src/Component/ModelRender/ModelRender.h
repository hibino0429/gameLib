#pragma once
#include "../../src/Component/ModelRender/ModelData.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/ConstantBuffer/ConstantBuffer.h"
#include "../../src/Component/Camera/Camera.h"
#include "../../src/Component/Light/Light.h"




//---------------------------------------------------------------
//!@class		ModelRender
//!@brief	���f��������
//---------------------------------------------------------------
class ModelRender : public Component
{
public:
	ModelRender() = delete;
	//!@brief	�R���X�g���N�^
	//!@param[in]	model	fbxModel�𐶐������|�C���^
	ModelRender(FbxModel* model);
	//!@brief	�f�X�g���N�^
	~ModelRender();
public:
	//!@brief	�A�j���[�V�����̍X�V
	//!@brief	�A�j���[�V������؂�ւ���Ƃ��ɌĂ�
	//!@brief	�p�ɂɌĂԂƂ��܂������Ȃ�
	//!@param[in]	animationNumber	�X�V����A�j���[�V�����ԍ�
	void	UpDateAnimation(const int& upDateAnimationNumber);
	//!@brief	�}�g���b�N�X�̍X�V
	void	UpDateMatrix(const Camera& camera,const DirectionalLight& light);
	//!@brief	�`�惂�[�h�̃Z�b�g
	void	SetDrawMode(const D3D11_FILL_MODE& fillMode = D3D11_FILL_SOLID,const D3D11_CULL_MODE& cullMode = D3D11_CULL_BACK);
	//!@brief	�F�̐ݒ�
	void	SetColor(const Math::Vector4& color);
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	void*	operator new(size_t ptr)
	{
		return _mm_malloc(ptr, 16);
	}
	void	operator delete(void* ptr)
	{
		_mm_free(ptr);
	}
private:
	ModelData		modelData;
	ConstantBuffer*	constantBuf;
	CBuffer			cBuf;
	TransMatrix		transMat;
};