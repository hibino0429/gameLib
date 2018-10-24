#pragma once


//DirectXのインターフェイスの参照カウンタやコピーの問題を防ぐ
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
	//参照カウンタ増加
	inline void	AddRef(Type* pInterface)
	{
		{
#if _DEBUG
			//デバッグ時、参照カウンタを出力
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

	//参照カウンタ減少
	inline void	Release(Type* pInterface);

public:
	//デフォルトコンストラクタ
	explicit ComPtr(Type* pInterface = nullptr, bool add = false);
	//コピーコンストラクタ
	ComPtr(const ComPtr& src);

	//デストラクタ
	virtual ~ComPtr();

	//演算子
	inline ComPtr&	operator=(const ComPtr& src);
	inline void	operator=(Type* pInterface);
	inline bool	operator!=(int value);
	inline bool	operator==(int value);

	//ポインタの取得
	inline Type*	GetPtr();
	inline Type**	GetPtrPtr();

	//インターフェイス生成関数へ渡す専用関数
	inline Type** ToCreator();

private:
	Type*	pInterface;	//インターフェイスのポインタ

};