#pragma once
#include <unordered_map>


template<typename Type>
class AssetList
{
public:
	//!@brief	�f�X�g���N�^
	~AssetList()
	{
		for (auto it = list.begin(); it != list.end(); ++it)
		{
			Utility::SafeDelete(it->second);
		}
		list.clear();
	}
public:
	//!@brief	�w�肵��[�ԍ�]�Ɏw�肵��[asset]��o�^����
	//!@note	���X�f�[�^���������ꍇ�A�o�^�͎��s
	//!@param[in]	number	�L�[�ԍ�
	//!@param[in]	asset	�A�Z�b�g�f�[�^
	//!@return	true:����  false:���s
	bool	Regist(const unsigned int number, Type asset)
	{
		//�w�肵���L�[��Asset���Z�b�g����Ă��邩�`�F�b�N
		//���ł�Asset������΁A�o�^���Ȃ�
		if (list.find(number) != list.end())
		{
			return false;
		}
		list[number] = asset;
		return true;
	}
	//!@brief	�w�肵��[�ԍ�]��[asset]�̎擾
	//!@param[in]	number	�L�[�ԍ�
	//!@return	�w�肵���L�[�ԍ���asset
	Type	GetAsset(const unsigned int number)
	{
		//�w�肵���L�[��Asset�ɂ��邩�`�F�b�N
		//Asset���Ȃ���΁Anullptr��Ԃ�
		if (list.find(number) == list.end())
		{
			return nullptr;
		}
		return list[number];
	}
	//!@brief	���g�̃��X�g���擾����
	const std::unordered_map<unsigned int, Type>&	GetList() const
	{
		return list;
	}
private:
	std::unordered_map<unsigned int, Type>		list;
};