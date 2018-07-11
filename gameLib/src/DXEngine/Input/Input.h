#pragma once
#define DIRECTINPUT_VERSION 0x0800
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")
#include <dinput.h>


//------------------------------------------------------------------------------
//!@class		DirectInput
//!@brief	DirectInput���g�p���ē��͏������s��
//------------------------------------------------------------------------------
class Input
{
public:
	Input();
	~Input();

	//!@brief	���͂̐���
	//!@param[in]	hWnd	�E�B���h�E�n���h��
	bool	CreateInput(const HWND& hWnd);
	//!@brief	�X�V
	void	Run();
	//!@brief	������������
	//!@return �������Ȃ� true �����Ă��Ȃ��Ȃ� false
	bool	Press(const int key);
	//!@brief	�����Ă��邩����
	//!@return �����Ă���Ȃ� true �����Ă��Ȃ��Ȃ� false
	bool	Push(const int key);
	//!@brief	������Ă��Ȃ�������
	//!@return ������Ă��Ȃ��Ȃ� true �����Ă���Ȃ� false
	bool	Free(const int key);
	//!@brief	�����ꂽ������
	//!@return �����ꂽ�Ȃ� true ������Ă��Ȃ��Ȃ� false
	bool	Pull(const int key);

	//!@brief	DirectInput��Ԃ�
	//!@return DirectInput�̃|�C���^
	LPDIRECTINPUT8	GetDirectInput() const;
	
private:
	LPDIRECTINPUT8			directInput;
	LPDIRECTINPUTDEVICE8	key;
	unsigned char buf[256];
	unsigned char preBuf[256];
	static const int MaxKey = 61;
	int	DIKeyCode[MaxKey];
};


//�p�b�h�̕����L�[
#define PAD_UP	0x1
#define PAD_RIGHT 0x2
#define PAD_DOWN 0x4
#define PAD_LEFT 0x8


//------------------------------------------------------------------------------
//!@class		�p�b�h
//!@brief	�p�b�h���g�p�������͂��s��
//------------------------------------------------------------------------------
class PadInput
{
private:
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
	
public:
	PadInput();
	~PadInput();

	//!@brief	���̓p�b�h�̍쐬
	//!@param[in]	hWnd	�E�B���h�E�n���h��
	void	CreatePadInput(const HWND& hWnd);
	//!@brief	�X�V
	void	Run();
	//!@brief	������������
	//!@param[in]	no	�p�b�h�ԍ�
	//!@param[in]	key	���̓L�[
	bool	Press(const int no, const int key);
	//!@brief	�c����Ă��邩����
	//!@param[in]	no	�p�b�h�ԍ�
	//!@param[in]	key	���̓L�[
	bool	Push(const int no, const int key);
	//!@brief	������Ă��邩����
	//!@param[in]	no	�p�b�h�ԍ�
	//!@param[in]	key	���̓L�[
	bool	Free(const int no, const int key);
	//!@brief	�����ꂽ������
	//!@param[in]	no	�p�b�h�ԍ�
	//!@param[in]	key	���̓L�[
	bool	Pull(const int no, const int key);

	//!@brief	�\���L�[�̈ʒu���擾
	//!@param[in]	no	�p�b�h�ԍ�
	//!@return	�o�C�g�^�̈ʒu
	BYTE	GetPovPosition(const int no);

private:
	static int			padNo;
	static const int	padNum = 1;
	static LPDIRECTINPUTDEVICE8	pad[padNum];
	DIDEVCAPS			DIDeviceCaps[padNum];
	DIJOYSTATE			joyBuf[padNum];
	DIJOYSTATE			preJoyBuf[padNum];
};


//------------------------------------------------------------------------------
//!@class		DirectMouse
//!@brief	DirectX�̃}�E�X�f�o�C�X���g�p���A�}�E�X������s��
//------------------------------------------------------------------------------
class DXMouse
{
public:
	DXMouse();
	~DXMouse();

	//!@brief	���̓}�E�X�f�o�C�X�̍쐬
	//!@param[in]	hWnd	�n���h��
	bool	CreateMouseInput(const HWND& hWnd);
	//!@brief	�X�V
	void	Run();
	//!@brief	������Ă��邩����
	bool	LButtonPush();
	//!@brief	������Ă��邩����
	bool	RButtonPush();

	//!@brief	�}�E�X�J�[�\���̈ʒu�̎擾
	//!@return	�}�E�X�J�[�\���̈ʒu
	POINT	GetMousePos();

private:
	LPDIRECTINPUTDEVICE8	DIMouse;
	DIMOUSESTATE			mouseState;
	HWND					hWnd;
	POINT					position;
};


extern Input input;
extern PadInput pad;
extern DXMouse mouse;