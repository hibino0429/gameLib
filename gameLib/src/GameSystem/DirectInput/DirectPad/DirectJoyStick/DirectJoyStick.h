#pragma once
#include "../../src/GameSystem/DirectInput/DirectInput.h"
#include <array>



//------------------------------------------------------------------------------
//!@class		DirectJoyStick
//!@brief	DirectInput�𗘗p����JoyStick�ł̑��������
//!@brief	�����̂̓W���C�X�e�B�b�N1��
//------------------------------------------------------------------------------
class DirectJoyStick : private DirectInputDevice
{
public:
	//!@brief	�R���X�g���N�^
	DirectJoyStick();
	//!@brief	�f�X�g���N�^
	~DirectJoyStick();
public:
	//!@brief	�W���C�X�e�B�b�N�f�o�C�X�̎擾
	//!@return	joystickDevice
	const LPDIRECTINPUTDEVICE8&	GetJoystick() const;
	//!@brief	���݂̃W���C�X�e�B�b�N�̏�Ԃ̎擾
	//!@return	nowJoyState
	const DIJOYSTATE&	GetNowJoyState() const;
	//!@brief	1�O�̃W���C�X�e�B�b�N�̏�Ԃ̎擾
	//!@return	preJoyState
	const DIJOYSTATE&	GetPreJoyState() const;
private:
	//!@brief	�f�o�C�X�̍쐬
	bool	CreateDevice() override;
	//!@brief	���̓f�[�^�`���̐ݒ�
	bool	SetDataFormat() override;
	//!@brief	�r������
	bool	SetCooperativeLevel(const HWND& hWnd) override;
	//!@brief	����
	void	Run() override;
	//!@brief	�I������
	void	Finalize() override;
	//!@brief	�W���C�X�e�B�b�N�̃f�o�C�X�̊m��
	bool	SetEnumDevice();
	//!@brief	�W���C�X�e�B�b�N�̓��͂��m�F
	bool	CheckEnumObjects(const HWND& hWnd);

	//!@brief �ڑ�����Ă���pad�����m����
	//!@param[in]	instance	���̓f�o�C�X�̃C���X�^���X
	//!@param[in]	context	�R���e�L�X�g�̃|�C���^
	static BOOL CALLBACK EnumPadCallback(
		const DIDEVICEINSTANCE* instance,
		void* pContext
	);
	//!@brief	�p�b�h�̐ݒ�
	//!@param[in]	objInstance �I�u�W�F�N�g�C���X�^���X
	//!@param[in]	context	�R���e�L�X�g�̃|�C���^
	static BOOL CALLBACK EnumAxisCallback(
		const DIDEVICEOBJECTINSTANCE* objInstance,
		void* pContext);

private:
	LPDIRECTINPUTDEVICE8	joystickDevice;
	DIDEVCAPS				deviceCaps;		//�W���C�X�e�B�b�N�̔\��
	DIJOYSTATE				nowJoyState;	//���݂̃W���C�X�e�B�b�N�̏��
	DIJOYSTATE				preJoyState;	//�P�O�̃W���C�X�e�B�b�N�̏��
};


