#pragma once
#include <string>
#include "../../src/Component/Assset/AssetList/AssetList.h"
#include <assert.h>
#include <fstream>
#include <stdio.h>
#include <memory>



//------------------------------------------------------------------------
//!@class		LoadAsset
//!@brief	Asset�̃f�[�^���t�@�C������ǂݍ���
//------------------------------------------------------------------------
template<typename Type>
class LoadAsset
{
public:
	//!@brief	Asset�̏����t�@�C�����烍�[�h
	//!@param[in]	filePath	�t�@�C���p�X
	//!@return	AssetList�̃|�C���^
	AssetList<Type*>*	LoadAssetList(const std::string& filePath)
	{
		std::ifstream	stream(filePath);
		std::string	str;
		std::string name;
		std::string path;
		//�Ԃ��͎̂Q�Ƃł͂Ȃ��|�C���^
		AssetList<Type*>*	assetList = new AssetList<Type*>();
		if (stream.fail())
		{
			assert(stream.fail());
		}
		int cnt = 0;
		//1�s�̓ǂݍ���
		while (std::getline(stream, str))
		{
			//�R�����g�A�E�g(/)�������玟�̍s��
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