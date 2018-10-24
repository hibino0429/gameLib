#pragma once
#include "../../src/Component/Material/MaterialData.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Material/Shader.h"


//-------------------------------------------------------
//!@class	Material
//!@brief	�}�e���A���̏�������
//!@brief	�e�N�X�`���̃A�^�b�`�₻�̂��̎��̂̐F
//-------------------------------------------------------
class Material : public Component
{
public:
	Material() = delete;
	//!@brief	�R���X�g���N�^
	//!@param[in]	color	�F
	Material(const Math::Vector4& color);
	//!@brief	�R���X�g���N�^
	//!@param[in]	texture	�e�N�X�`��
	Material(Texture* texture);
	//!@brief	�f�X�g���N�^
	virtual ~Material();
public:
	//!@brief	�e�N�X�`����ύX����
	//!@brief	�O�̃e�N�X�`���͔j�������
	//!@param[in]	texture	�e�N�X�`��
	void	ChangeTexture(Texture* texture);
	//!@brief	�F�̎擾
	//!@return	x: red, y: green, z: blue, w: alpha
	const Math::Vector4&	GetColor() const;
	//!@brief	�g�p����V�F�[�_�̂̃Z�b�g
	//!@param[in]	shader	�g�p����V�F�[�_
	bool	SetShader(Shader* shader);
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	MaterialData	data;
	Shader*			shader;
};