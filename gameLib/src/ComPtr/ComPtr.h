#pragma once


//DirectX�̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^��R�s�[�̖���h��
#define OUTPUT_INTERFACEUSAGE

#ifdef OUTPUT_INTERFACEUSAGE

#if _DEBUG
#include <fstream>
using namespace std;
#endif

#endif

//-------------------------------------------------------------
//ComPtr
//-------------------------------------------------------------
template<typename Type>
class ComPtr
{
protected:
	//�Q�ƃJ�E���^����
	inline void	AddRef(Type* pInterface)
	{
		{
#if _DEBUG
			//�f�o�b�O���A�Q�ƃJ�E���^���o��
			ULONG c = pInterface->AddRef();
			ofstream	ofs;
			ofs.open("DEBUG.txt", ios::app);
			ofs << pInterface << "\t[" << c << "]" << endl;
			ofs.close();
#else
			pInterface->AddRef();
#endif
		}
	}

	//�Q�ƃJ�E���^����
	inline void	Release(Type* pInterface);

public:
	//�f�t�H���g�R���X�g���N�^
	explicit ComPtr(Type* pInterface = nullptr, bool add = false);
	//�R�s�[�R���X�g���N�^
	ComPtr(const ComPtr& src);

	//�f�X�g���N�^
	virtual ~ComPtr();

	//���Z�q
	inline ComPtr&	operator=(const ComPtr& src);
	inline void	operator=(Type* pInterface);
	inline bool	operator!=(int value);
	inline bool	operator==(int value);

	//�|�C���^�̎擾
	inline Type*	GetPtr();
	inline Type**	GetPtrPtr();

	//�C���^�[�t�F�C�X�����֐��֓n����p�֐�
	inline Type** ToCreator();

private:
	Type*	pInterface;	//�C���^�[�t�F�C�X�̃|�C���^

};