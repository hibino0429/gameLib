#include "Collision.h"

//�R���X�g���N�^
Collision::Collision()
{
	
}
//!@brief	�R���X�g���N�^
//!@param[in]	dynamicShape	�`��
Collision::Collision(DynamicShape* dynamicShape)
{
	this->dynamicShape = dynamicShape;
}

//�f�X�g���N�^
Collision::~Collision()
{
	//�`��̉���ӔC������
	delete dynamicShape;
}


//!@brief	�`��̎擾
//!@return	�ێ����Ă���`��
const DynamicShape&	Collision::GetDynamicShape() const
{
	return *dynamicShape;
}

//!@brief	�Փ˂������𔻒�
//!@brief	�R���W�������m���G�ꂽ�u��
//!@param[in]	collision	����̃R���W����
//!@return	true: �Փ˂��� false: �Փ˂��Ă��Ȃ�
bool	Collision::OnCollisionEnter(Collision* collision)
{
	return true;
}
//!@brief	�Փ˂��Ă��邩�𔻒�
//!@brief	�R���W�������m���G��Ă����
//!@return	true: �Փ˂��Ă��� false: �Փ˂��Ă��Ȃ�
bool	Collision::OnCollisionStay(Collision* collision)
{
	return true;
}
//!@brief	�Փ˂���߂����𔻒�
//!@brief	�R���W�������m�����ꂽ�Ƃ�
//!@return	true: �Փ˂��Ȃ��Ȃ��� false: �Փ˂��Ă���
bool	Collision::OnCollisionExit(Collision* collision)
{
	return true;
}