#pragma once
#include "../../src/Component/Assset/AssetList/AssetList.h"
#include <memory>


class List
{
protected:
	//template<typename Type>
	//static std::unordered_map<std::string, AssetList<Type*>> list;
	template<typename Type>
	static std::unordered_map<std::string, AssetList<Type*>*> list;
};

//template<typename Type>
//std::unordered_map<std::string, AssetList<Type*>> List::list = 0;

template<typename Type>
std::unordered_map<std::string, AssetList<Type*>*> List::list = 0;

//------------------------------------------------------------------
//!@class		AssetManager
//!@brief	AssetList�������o�^����K�v������܂�
//!@brief	AssetList�������Ō�̍폜����K�v������܂�
//!@brief	�o�^: RegistAssetList<Type>("ListName");
//!@brief	�폜: Delete<Type>();
//------------------------------------------------------------------
class AssetManager : private List
{
public:
	//!@brief	�R���X�g���N�^
	AssetManager();
	//!@brief	�f�X�g���N�^
	~AssetManager();
public:
	//!@brief	AssetList�̓o�^
	//!@param[in]	listName	���X�g�ɃL�[�̖��O���w��
	template<typename Type>
	bool	RegistAssetList(const std::string& listName,AssetList<Type*>* assetList)
	{
		if (list<Type>.find(listName) != list<Type>.end())
		{
			return false;
		}
		list<Type>[listName] = assetList;
		return true;
	}
	//!@brief	�w�肵���L�[�̖��O��AssetList�����݂��邩
	//!@param[in]	listName	�L�[�̖��O���w��
	//!@return	true:����	false:�Ȃ�
	template<typename Type>
	bool	HasAssetList(const std::string& listName)
	{
		if (list<Type>.find(listName) == list<Type>.end())
		{
			return false;
		}
		return true;
	}
	//!@brief	�w�肵���L�[�̖��O��AssetList���������
	//!@param[in]	listName	�L�[�̖��O���w��
	template<typename Type>
	bool	ReleaseAssetList(const std::string& listName)
	{
		auto itr = list<Type>.find(listName);
		if (itr == list<Type>.end())
		{
			return false;
		}
		list<Type>.erase(itr);
		return true;
	}
	//!@brief	�w�肵���L�[�̖��O��AssetList���擾����
	//!@param[in]	listName	�L�[�̖��O���w��
	//!@return	AssetList<Type>& ��Ԃ�
	template<typename Type>
	AssetList<Type*>&	GetAssetList(const std::string& listName)
	{
		if (!HasAssetList<Type>(listName))
		{
			std::cout << "�L�[�̖��O��AssetList�����݂��܂���" << std::endl;
			assert(false);
		}
		return *list<Type>[listName];
	}
public:
	//!@brief	�o�^�����^��AssetList���폜
	//!@note	�o�^�������X�g���폜����K�v������
	template<typename Type>
	void	Delete()
	{
		/*if (list<Type>.empty())
		{
			return;
		}
		for (auto it = list<Type>.begin(); it != list<Type>.end(); ++it)
		{
			it->second->~AssetList();
		}*/
		list<Type>.clear();
	}
};



