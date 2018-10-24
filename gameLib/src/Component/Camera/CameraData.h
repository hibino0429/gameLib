#pragma once
#include "../../src/DXEngine/Math/Math.h"


//------------------------------------------------
//!@class		CameraData
//------------------------------------------------
struct CameraData
{
	Math::Vector3	eyePos;			//���_
	Math::Vector3	targetPos;		//�����_
	Math::Vector3	upVec;			//������x�N�g��
	float			fovAngle;		//����p(�x��)
	float			aspect;			//�A�X�y�N�g��
	float			nearZ;			//�O�����e�ʂ܂ł̋���
	float			farZ;			//������e�ʂ܂ł̋���
	Math::Vector4	backGround;		//�w�i�F
	bool			projectionFlag;	//�i�F�̃J�����@�\�̐؂�ւ�
};