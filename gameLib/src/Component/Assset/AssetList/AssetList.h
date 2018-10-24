#pragma once
#include <unordered_map>


template<typename Type>
class AssetList
{
public:
	//!@brief	デストラクタ
	~AssetList()
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			Utility::SafeDelete(it->second);
		}
		list.clear();
	}
public:
	//!@brief	指定した[番号]に指定した[asset]を登録する
	//!@note	元々データがあった場合、登録は失敗
	//!@param[in]	number	キー番号
	//!@param[in]	asset	アセットデータ
	//!@return	true:成功  false:失敗
	bool	Regist(const unsigned int number, Type asset)
	{
		//指定したキーにAssetがセットされているかチェック
		//すでにAssetがあれば、登録しない
		if (list.find(number) != list.end())
		{
			return false;
		}
		list[number] = asset;
		return true;
	}
	//!@brief	指定した[番号]の[asset]の取得
	//!@param[in]	number	キー番号
	//!@return	指定したキー番号のasset
	Type	GetAsset(const unsigned int number)
	{
		//指定したキーがAssetにあるかチェック
		//Assetがなければ、nullptrを返す
		if (list.find(number) == list.end())
		{
			return nullptr;
		}
		return list[number];
	}
	//!@brief	自身のリストを取得する
	const std::unordered_map<unsigned int, Type>&	GetList() const
	{
		return list;
	}
private:
	std::unordered_map<unsigned int, Type>		list;
};