#pragma once
#include <string>
#include <iostream>

//-------------------------------------------------------------
//!@class		AnimationData
//!@brief	�A�j���[�V�����̃f�[�^��ێ����܂�
//-------------------------------------------------------------
class AnimationData
{
public:
	//!@brief	�R���X�g���N�^
	AnimationData();
	//!@brief	�R���X�g���N�^
	//!@param[in]	animationNumber	�A�j���[�V�����ԍ�
	//!@param[in]	animationName	�A�j���[�V������
	AnimationData(const int& animationNumber, const char* animationName);
	//!@brief	�f�X�g���N�^
	~AnimationData();

public:
	/////////////////////////////////////////////////
	//�擾����
	/////////////////////////////////////////////////
	//!@brief	�A�j���[�V�����ԍ��̎擾
	const int&	GetAnimationNumber() const;
	//!@brief	�A�j���[�V�������̎擾
	const std::string&	GetAnimationName() const;

public:
	/////////////////////////////////////////////////
	//�ݒ菈��
	/////////////////////////////////////////////////
	//!@brief	�A�j���[�V�����ԍ��ݒ�
	//!@param[in]	animationNumber	�A�j���[�V�����ԍ�
	void	SetAnimationNumber(const int& animationNumber);
	//!@brief	�A�j���[�V�������̐ݒ�
	//!@param[in]	animationName	�A�j���[�V������
	void	SetAnimationName(const char* animationName);

public:
	//!@brief	�ԍ��Ɩ��O�̏o��
	void	Output();

private:
	int			animationNumber;	//�A�j���[�V�����ԍ�
	std::string	animationName;		//�A�j���[�V������
};

