#include "AnimationData.h"

//!@brief	�R���X�g���N�^
AnimationData::AnimationData()
	: animationNumber(0)
	, animationName("")
{

}
//!@brief	�R���X�g���N�^
//!@param[in]	animationNumber	�A�j���[�V�����ԍ�
//!@param[in]	animationName	�A�j���[�V������
AnimationData::AnimationData(const int& animationNumber, const char* animationName)
	: animationNumber(animationNumber)
	, animationName(animationName)
{

}
//!@brief	�f�X�g���N�^
AnimationData::~AnimationData()
{

}

/////////////////////////////////////////////////
//�擾����
/////////////////////////////////////////////////
//!@brief	�A�j���[�V�����ԍ��̎擾
const int&	AnimationData::GetAnimationNumber() const
{
	return animationNumber;
}
//!@brief	�A�j���[�V�������̎擾
const std::string&	AnimationData::GetAnimationName() const
{
	return animationName;
}

/////////////////////////////////////////////////
//�ݒ菈��
/////////////////////////////////////////////////
//!@brief	�A�j���[�V�����ԍ��ݒ�
//!@param[in]	animationNumber	�A�j���[�V�����ԍ�
void	AnimationData::SetAnimationNumber(const int& animationNumber)
{
	this->animationNumber = animationNumber;
}
//!@brief	�A�j���[�V�������̐ݒ�
//!@param[in]	animationName	�A�j���[�V������
void	AnimationData::SetAnimationName(const char* animationName)
{
	this->animationName = animationName;
}

//!@brief	�ԍ��Ɩ��O�̏o��
void	AnimationData::Output()
{
	std::cout << "�A�j���[�V�����ԍ�[ " << animationNumber << " ]" << " : "
		<< "�A�j���[�V������:" << animationName << std::endl;
}