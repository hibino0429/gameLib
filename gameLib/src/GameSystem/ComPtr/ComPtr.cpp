#include "Comptr.h"

//参照カウンタの増加
//template<typename Type>
//void	ComPtr<Type>::AddRef(Type* pInterface)
//{
//	#if _DEBUG
//	//デバッグ時、参照カウンタを出力
//	ULONG c = pInterface->AddRef();
//	ofstream	ofs;
//	ofs.open("DEBUG.txt", ios::app);
//	ofs << pInterface << "\t[" << c << "]" << endl;
//	ofs.close();
//	#else
//	pInterface->AddRef();
//	#endif
//}

//参照カウンタの減少
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


//デフォルトコンストラクタ
template<typename Type>
ComPtr<Type>::ComPtr(Type* pInterface = nullptr, bool add = false)
{
	if (pInterface && add)
	{
		AddRef(pInterface);
	}
	this->pInterface = pInterface;
}

//コピーコンストラクタ
template<typename Type>
ComPtr<Type>::ComPtr(const ComPtr& src)
{
	//コピー元の参照カウンタを1つ増やす
	if (src.pInterface)
	{
		AddRef(src.pInterface);
	}
	//コピー
	pInterface = src.pInterface;
}

//デストラクタ
template<typename Type>
ComPtr<Type>::~ComPtr()
{
	if (this->pInterface)
	{
		Release(this->pInterface);
	}
}

//=代入演算子(明示的なコピー)
template<typename Type>
ComPtr<Type>&	ComPtr<Type>::operator=(const ComPtr<Type>& src)
{
	//自身のインターフェイスの参照カウンタを１つ減らす
	if (pInterface)
	{
		Release(pInterface);
	}
	//コピー元の参照カウンタを1つ増やす
	if (src.pInterface)
	{
		AddRef(src.pInterface);
	}
	//コピー
	this->pInterface = src.pInterface;
	return *this;
}

//=代入演算子(インターフェイスの登録)
template<typename Type>
void	ComPtr<Type>::operator=(Type* pInterface)
{
	//自身のインターフェイスの参照カウンタを1つ減らす
	if (pInterface)
	{
		Release(pInterface);
	}
	//コピー
	this->pInterface = pInterface;
}

//!= 比較演算子
template<typename Type>
bool	ComPtr<Type>::operator!=(int value)
{
	if (value != (int)pInterface)
	{
		return true;
	}
	return false;
}

//== 比較演算子
template<typename Type>
bool	ComPtr<Type>::operator==(int value)
{
	if (value == (int)pInterface)
	{
		return true;
	}
	return false;
}

//ポインタの取得
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

//インターフェイス生成関数へ渡す専用関数
template<typename Type>
Type**	ComPtr<Type>::ToCreator()
{
	if (this->pInterface)
	{
		pInterface->Release();
	}
	return &pInterface;
}