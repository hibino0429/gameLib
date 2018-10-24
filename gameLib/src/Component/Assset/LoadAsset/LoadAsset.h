#pragma once
#include <string>
#include "../../src/Component/Assset/AssetList/AssetList.h"
#include <assert.h>
#include <fstream>
#include <stdio.h>
#include <memory>



//------------------------------------------------------------------------
//!@class		LoadAsset
//!@brief	Assetのデータをファイルから読み込む
//------------------------------------------------------------------------
template<typename Type>
class LoadAsset
{
public:
	//!@brief	Assetの情報をファイルからロード
	//!@param[in]	filePath	ファイルパス
	//!@return	AssetListのポインタ
	AssetList<Type*>*	LoadAssetList(const std::string& filePath)
	{
		std::ifstream	stream(filePath);
		std::string	str;
		std::string name;
		std::string path;
		//返すのは参照ではなくポインタ
		AssetList<Type*>*	assetList = new AssetList<Type*>();
		if (stream.fail())
		{
			assert(stream.fail());
		}
		int cnt = 0;
		//1行の読み込み
		while (std::getline(stream, str))
		{
			//コメントアウト(/)が来たら次の行へ
			if (str.at(0) == '/')
			{
				continue;
			}
			size_t num = str.find(",");
			name = str.substr(0, num);
			path = str.substr(num + 1);
			//list.Regist(stoi(name), new Type(path));
			assetList->Regist(stoi(name), new Type(path));
			++cnt;
		}
		stream.close();
		return assetList;
	}
};