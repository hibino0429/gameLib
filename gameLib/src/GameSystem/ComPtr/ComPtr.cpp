#include "Comptr.h"

//�Q�ƃJ�E���^�̑���
//template<typename Type>
//void	ComPtr<Type>::AddRef(Type* pInterface)
//{
//	#if _DEBUG
//	//�f�o�b�O���A�Q�ƃJ�E���^���o��
//	ULONG c = pInterface->AddRef();
//	ofstream	ofs;
//	ofs.open("DEBUG.txt", ios::app);
//	ofs << pInterface << "\t[" << c << "]" << endl;
//	ofs.close();
//	#else
//	pInterface->AddRef();
//	#endif
//}

//�Q�ƃJ�E���^�̌���
template<typename Type>
void	ComPtr<Type>::Release(Type* pInterface)
{
	#if _DEBUG
	ULONG c = m_pInterface->Release();
	ofstream ofs;
	ofs.open("DEBUG.txt", ios::app);
	ofs << m_pInterface << "\t[" << c << "]" << endl;
	ofs.close();
	#else
	m_pInterface->Release();
	#endif
}


//�f�t�H���g�R���X�g���N�^
template<typename Type>
ComPtr<Type>::ComPtr(Type* pInterface = nullptr, bool add = false)
{
	if (pInterface && add)
	{
		AddRef(pInterface);
	}
	this->pInterface = pInterface;
}

//�R�s�[�R���X�g���N�^
template<typename Type>
ComPtr<Type>::ComPtr(const ComPtr& src)
{
	//�R�s�[���̎Q�ƃJ�E���^��1���₷
	if (src.pInterface)
	{
		AddRef(src.pInterface);
	}
	//�R�s�[
	pInterface = src.pInterface;
}

//�f�X�g���N�^
template<typename Type>
ComPtr<Type>::~ComPtr()
{
	if (this->pInterface)
	{
		Release(this->pInterface);
	}
}

//=������Z�q(�����I�ȃR�s�[)
template<typename Type>
ComPtr<Type>&	ComPtr<Type>::operator=(const ComPtr<Type>& src)
{
	//���g�̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^���P���炷
	if (pInterface)
	{
		Release(pInterface);
	}
	//�R�s�[���̎Q�ƃJ�E���^��1���₷
	if (src.pInterface)
	{
		AddRef(src.pInterface);
	}
	//�R�s�[
	this->pInterface = src.pInterface;
	return *this;
}

//=������Z�q(�C���^�[�t�F�C�X�̓o�^)
template<typename Type>
void	ComPtr<Type>::operator=(Type* pInterface)
{
	//���g�̃C���^�[�t�F�C�X�̎Q�ƃJ�E���^��1���炷
	if (pInterface)
	{
		Release(pInterface);
	}
	//�R�s�[
	this->pInterface = pInterface;
}

//!= ��r���Z�q
template<typename Type>
bool	ComPtr<Type>::operator!=(int value)
{
	if (value != (int)pInterface)
	{
		return true;
	}
	return false;
}

//== ��r���Z�q
template<typename Type>
bool	ComPtr<Type>::operator==(int value)
{
	if (value == (int)pInterface)
	{
		return true;
	}
	return false;
}

//�|�C���^�̎擾
template<typename Type>
Type*	ComPtr<Type>::GetPtr()
{
	return this->pInterface;
}

template<typename Type>
Type**	ComPtr<Type>::GetPtrPtr()
{
	return &this->pInterface;
}

//�C���^�[�t�F�C�X�����֐��֓n����p�֐�
template<typename Type>
Type**	ComPtr<Type>::ToCreator()
{
	if (this->pInterface)
	{
		pInterface->Release();
	}
	return &pInterface;
}