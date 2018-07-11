#include "KeyBoard.h"


//!@brief	コンストラクタ
KeyBoard::KeyBoard()
{
	
}

//!@brief	更新
void	KeyBoard::Run()
{
	input.Run();
}

//!@brief	押しているか判定
//!@param[in]	key	キー
bool	KeyBoard::On(const Key& key)
{
	return input.Push((int)key);
}

//!@brief	押したか判定
//!@param[in]	key	キー
bool	KeyBoard::Down(const Key& key)
{
	return input.Press((int)key);
}

//!@brief	入力がないか判定
//!@param[in]	key	キー
bool	KeyBoard::Free(const Key& key)
{
	return input.Free((int)key);
}

//!@brief	離されたか判定
//!@param[in]	key	キー
bool	KeyBoard::Pull(const Key& key)
{
	return input.Pull((int)key);
}