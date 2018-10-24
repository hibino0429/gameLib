#pragma once

//---------------------------------------------------------------------
//!@file	Utility.hpp
//!@brief	���[�e�B���e�B�֐�
//!@data	2018/06/02
//---------------------------------------------------------------------
namespace Utility
{
	//------------------------------------------------------------------------------
	//!@brief		�폜����
	//!@param[in]	pointer �|�C���^
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
	//!@brief		�z��폜����
	//!@param[in]	pointer �|�C���^
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
	//!@brief		�������
	//!@param[in]	pointer �|�C���^
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
	//!@brief		nullptr�`�F�b�N
	//!@param[in]	pointer �|�C���^
	//!@return	true: nullptr�ł���  false: nullptr�łȂ�
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