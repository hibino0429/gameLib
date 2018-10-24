#pragma once

//---------------------------------------------------------------------
//!@file	Utility.hpp
//!@brief	ユーティリティ関数
//!@data	2018/06/02
//---------------------------------------------------------------------
namespace Utility
{
	//------------------------------------------------------------------------------
	//!@brief		削除処理
	//!@param[in]	pointer ポインタ
	//!
	//!@brief		SafeDelete(pointer);
	//------------------------------------------------------------------------------
	template<typename Type>
	void	SafeDelete(Type*& pointer)
	{
		delete pointer;
		pointer = nullptr;
	}

	//------------------------------------------------------------------------------
	//!@brief		配列削除処理
	//!@param[in]	pointer ポインタ
	//!
	//!@brief		SafeDeleteArray(pointer)
	//------------------------------------------------------------------------------
	template<typename Type>
	void	SafeDeleteArray(Type*& pointer)
	{
		delete[] pointer;
		pointer = nullptr;
	}

	//------------------------------------------------------------------------------
	//!@brief		解放処理
	//!@param[in]	pointer ポインタ
	//!
	//!@brief		SafeRelease(pointer)
	//------------------------------------------------------------------------------
	template<typename Type>
	void	SafeRelease(Type*& pointer)
	{
		if (pointer != nullptr)
		{
			pointer->Release();
			pointer = nullptr;
		}
	}

	//------------------------------------------------------------------------------
	//!@brief		nullptrチェック
	//!@param[in]	pointer ポインタ
	//!@return	true: nullptrである  false: nullptrでない
	//!
	//!@brief		CheckNull(pointer)
	//------------------------------------------------------------------------------
	template<typename Type>
	bool	CheckNull(Type*& pointer)
	{
		if (pointer == nullptr)
		{
			return true;
		}
		return false;
	}
}