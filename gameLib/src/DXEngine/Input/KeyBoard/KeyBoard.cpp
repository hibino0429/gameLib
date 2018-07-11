#include "KeyBoard.h"


//!@brief	�R���X�g���N�^
KeyBoard::KeyBoard()
{
	
}

//!@brief	�X�V
void	KeyBoard::Run()
{
	input.Run();
}

//!@brief	�����Ă��邩����
//!@param[in]	key	�L�[
bool	KeyBoard::On(const Key& key)
{
	return input.Push((int)key);
}

//!@brief	������������
//!@param[in]	key	�L�[
bool	KeyBoard::Down(const Key& key)
{
	return input.Press((int)key);
}

//!@brief	���͂��Ȃ�������
//!@param[in]	key	�L�[
bool	KeyBoard::Free(const Key& key)
{
	return input.Free((int)key);
}

//!@brief	�����ꂽ������
//!@param[in]	key	�L�[
bool	KeyBoard::Pull(const Key& key)
{
	return input.Pull((int)key);
}