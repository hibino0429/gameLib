#pragma once



//------------------------------------------------------------------------------
//!@class		InputDevice
//!@brief	���̓f�o�C�X�𗘗p���āA���͂��s��
//!@brief	�C���^�[�t�F�C�X�Ƃ��Ĉ���
//------------------------------------------------------------------------------
class InputDevice
{
public:
	//!@brief	�f�X�g���N�^
	virtual ~InputDevice() {}
public:
	//!@brief	���͂̐���
	virtual bool	CreateInput() = 0;
	//!@brief	�X�V
	virtual void	Run() = 0;
	//!@brief	�����Ă��邩����
	//!@return �����Ă���Ȃ� true �����Ă��Ȃ��Ȃ� false
	virtual bool	Press(const int key) = 0;
	//!@brief	������������
	//!@return �������Ȃ� true �����ĂȂ��Ȃ� false
	virtual bool	Push(const int key) = 0;
	//!@brief	������Ă��Ȃ�������
	//!@return ������Ă��Ȃ��Ȃ� true �����Ă���Ȃ� false
	virtual bool	Free(const int key) = 0;
	//!@brief	�����ꂽ������
	//!@return �����ꂽ�Ȃ� true ������Ă��Ȃ��Ȃ� false
	virtual bool	Release(const int key) = 0;
};


//------------------------------------------
//!@class		InputEngine
//!@brief	���͏����̒񋟃N���X
//------------------------------------------
class InputEngine
{
public:
	//!@brief	���̓f�o�C�X�̓o�^
	//!@param[in]	inputDevice	���̓f�o�C�X
	static void Regist(InputDevice* inputDevice);
	//!@brief	���̓f�o�C�X�̉���
	static void Release();

	//!@brief	���̓f�o�C�X�̎擾
	static InputDevice&	GetDevice();
private:
	static InputDevice*	device;
};


//------------------------------------------------------------------------------
//!@class		Input
//!@brief	���͂�����
//------------------------------------------------------------------------------
class InputI
{
public:
	//!@brief	�R���X�g���N�^
	//!@param[in]	���̓f�o�C�X�̃|�C���^
	//!@detail
	//	Input* input = new Input(new XInput());
	//
	InputI(InputDevice* inputDevice);
	//!@brief	�f�X�g���N�^
	~InputI();
public:
	//!@brief	���̓G���W���̎擾
	//!@return	�ێ����Ă�����̓G���W��
	const InputEngine&	GetInputEngine() const;
private:
	InputEngine*		inputEngine;
};


