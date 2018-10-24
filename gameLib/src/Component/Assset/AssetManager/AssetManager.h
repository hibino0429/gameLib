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
//!@brief	AssetList分だけ登録する必要があります
//!@brief	AssetList分だけ最後の削除する必要があります
//!@brief	登録: RegistAssetList<Type>("ListName");
//!@brief	削除: Delete<Type>();
//------------------------------------------------------------------
class AssetManager : private List
{
public:
	//!@brief	コンストラクタ
	AssetManager();
	//!@brief	デストラクタ
	~AssetManager();
public:
	//!@brief	AssetListの登録
	//!@param[in]	listName	リストにキーの名前を指定
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
	//!@brief	指定したキーの名前にAssetListが存在するか
	//!@param[in]	listName	キーの名前を指定
	//!@return	true:ある	false:ない
	template<typename Type>
	bool	HasAssetList(const std::string& listName)
	{
		if (list<Type>.find(listName) == list<Type>.end())
		{
			return false;
		}
		return true;
	}
	//!@brief	指定したキーの名前のAssetListを解放する
	//!@param[in]	listName	キーの名前を指定
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
	//!@brief	指定したキーの名前のAssetListを取得する
	//!@param[in]	listName	キーの名前を指定
	//!@return	AssetList<Type>& を返す
	template<typename Type>
	AssetList<Type*>&	GetAssetList(const std::string& listName)
	{
		if (!HasAssetList<Type>(listName))
		{
			std::cout << "キーの名前のAssetListが存在しません" << std::endl;
			assert(false);
		}
		return *list<Type>[listName];
	}
public:
	//!@brief	登録した型のAssetListを削除
	//!@note	登録したリスト分削除する必要がある
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



