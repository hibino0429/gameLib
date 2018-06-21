#pragma once
#include <vector>
#include "../../src/Device/DXDevice/DXDevice.h"
#include "../../src/Math/Math.h"
#include "../../src/Material/Material.h"

//-------------------------------------------------------------------
//!@class		Mesh
//!@brief	�|���S���̏W���N���X
//-------------------------------------------------------------------
class Mesh
{
private:
	//!@brief	�萔�o�b�t�@�̒�`
	struct Constant
	{
		DirectX::XMMATRIX	worldMat;
	};

public:
	//!@brief	�R���X�g���N�^
	Mesh();
	//!@brief	�f�X�g���N�^
	~Mesh();

	//!@brief	���ʂ̍쐬
	//!@param[in]	�|���S���̑傫��
	//!@param[in]	�|���S���̃I�t�Z�b�g�ʒu
	//!@param[in]	���_�E�C���f�b�N�X�̏������t���O
	//!@param[in]	�������̌���
	//!@param[in]	������̌���
	//!@param[in]	�@���̌���
	void	CreatePlane(
		Math::Vector2 size,
		Math::Vector3 offset = Math::Vector3(0.0f, 0.0f, 0.0f),
		bool		 shoudClear = true,
		Math::Vector3 leftDir = Math::Vector3(1.0f, 0.0f, 0.0f),
		Math::Vector3 upDir = Math::Vector3(0.0f, 1.0f, 0.0f),
		Math::Vector3 forwardDir = Math::Vector3(0.0f, 0.0f, 1.0f)
	);

	//!@brief	�l�ʑ̂̍쐬
	//!@param[in]	���_�E�C���f�b�N�X�̏������t���O
	void	CreateCube(bool	shoudClear = true);

	//!@brief	�|�C���g�̍쐬
	//!@param[in]	pos	�|�C���g�ʒu
	//!@param[in]	offset	�I�t�Z�b�g
	//!@param[in]	forwardDir	����
	//!@param[in]	shoudClear	���_�E�C���f�b�N�X�̏������t���O
	void	CreatePoint(
		const Math::Vector3& pos,
		const Math::Vector3& offset,
		const Math::Vector3& forwardDir,
		bool	shoudClear);

	//!@brief	�}�e���A���̎擾
	//!@return �}�e���A��
	Material&	GetMaterial();

	//!@brief	�ʒu�̐ݒ�
	//!@param[in]	pos	�ʒu
	void	SetPos(const Math::Vector3& pos);
	//!@brief	�p�x�̐ݒ�
	//!@param[in]	angle	�p�x
	void	SetAngle(const Math::Vector3& angle);
	//!@brief	�X�P�[���̐ݒ�
	//!@param[in]	scale	�X�P�[��
	void	SetScale(const Math::Vector3& scale);
	
	//!@brief	�J�����O���[�h�̐ݒ�
	//!@param[in]	�J�����O�̐ݒ�
	void	SetCullingMode(D3D11_CULL_MODE cullingMode);

	//!@brief	�ύX�_��K��������
	void	Apply();

	//!@brief	�ʒu�E��]�E�X�P�[���̐ݒ�
	//!@param[in]	pos_		�ʒu
	//!@param[in]	rotation_	��]
	//!@param[in]	scale_		�X�P�[��
	void	SetParams(const Math::Vector3& pos_, const Math::Vector3& rotation_, const Math::Vector3& scale_);

	//!@brief	�`�悷��
	void	Draw();
	//!@brief	�|�C���g��`�悷��
	void	DrawPoint();

	void*	operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}
	void	operator delete(void* p)
	{
		_mm_free(p);
	}

private:
	Constant				constantBuf;		//�萔�o�b�t�@
	ID3D11Buffer*			vertexBuf;			//���_�o�b�t�@
	ID3D11Buffer*			indexBuf;			//�C���f�b�N�X�o�b�t�@
	ID3D11RasterizerState*	rasterizerState;	//���X�^���C�U�X�e�[�g

	std::vector<Math::VertexData>	vertices;		//���_�f�[�^
	std::vector<UINT>				indices;		//�C���f�b�N�X�f�[�^

	Material			material;
	Math::Vector3		position;
	Math::Vector3		angle;
	Math::Vector3		scale;
};