#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Light/LightData.h"
#include "../../src/Component/ConstantBuffer/ConstantBuffer.h"
#include "../../src/Component/Material/Material.h"


//----------------------------------------------------
//!@class		���C�g�R���|�[�l���g
//----------------------------------------------------
class Light : Component
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	lightType	���C�g�̎��
	//!@param[in]	lightColor	���C�g�̐F
	Light(const LightType& lightType, const Math::Vector3& lightColor);
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	const LightData&		GetLightData() const;
	const TransMatrix&		GetTransMat() const;
	void	SetMatrix(const TransMatrix& transMatrix);
	void*	operator new(size_t ptr)
	{
		return _mm_malloc(ptr, 16);
	}
	void	operator delete(void* ptr)
	{
		_mm_free(ptr);
	}
private:
	LightData		data;
	TransMatrix		transMat;
};


//----------------------------------------------------
//!@class		���s����
//----------------------------------------------------
class	DirectionalLight : public Component
{
public:
	//!@brief	�R���X�g���N�^
	DirectionalLight();
	//!@brief	�R���X�g���N�^
	//!@param[in]	lightDir	���̌���
	DirectionalLight(const Math::Vector3& lightDir);
	//!@brief	�R���X�g���N�^
	//!@param[in]	lightDir	���̌���
	//!@param[in]	lightColor	���̐F
	DirectionalLight(const Math::Vector3& lightDir, const Math::Vector3& lightColor);
	//!@brief	�f�X�g���N�^
	~DirectionalLight();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	���̕����̎擾
	const Math::Vector3&	GetLightDir() const;
	//!@brief	���̐F�̎擾
	const Math::Vector3&	GetLightColor() const;
	//!@brief	���̕����̐ݒ�
	//!@param[in]	lightDir	���̌���
	void	SetLightDir(const Math::Vector3& lightDir);
	//!@brief	�}�g���b�N�X�̐ݒ�
	void	SetMatrix(const TransMatrix& transMatrix);
private:
	Light*					light;
	DirectinalLightData		data;
};



//-----------------------------------------------------
//!@class		�_����
//-----------------------------------------------------
class PointLight : public Component
{
public:
	//!@brief	�R���X�g���N�^
	PointLight();
	//!@brief	�R���X�g���N�^
	//!@param[in]	pos	�����ʒu
	//!@param[in]	attenuation	������
	PointLight(const Math::Vector3& pos, const Math::Vector3& attenuation);
	//!@brief	�f�X�g���N�^
	~PointLight();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	�}�g���b�N�X�̃Z�b�g
	//void	SetMatrix(const TransMatrix& transMatrix);
private:
	Light*				light;
	PointLightData		data;
};