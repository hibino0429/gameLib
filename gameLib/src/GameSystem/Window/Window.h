#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

#include "../../src/GameSystem/GameMain/GameMain.h"


//------------------------------------------------------------------------
//!@class		Window
//!@brief	ウィンドウクラス
//------------------------------------------------------------------------
class Window
{
public:
	//概要: スクリーンの情報をもとにウィンドウを生成
	//引数: screen スクリーン情報のポインタ
	Window(Screen* screen);
	~Window();

	//概要: wParamの取得
	//戻り値: wParamのint値
	int		GetWParam() const;

	//概要: ウィンドウクラスの初期化
	//引数: hInstance インスタンスハンドル
	void	InitWindowClass(const HINSTANCE& hInstance);
	//概要: フルスクリーンにする
	//引数: cmdLine コマンドライン
	//引数: cmdShow コマンドパラメータ
	void	FullScreen(const LPWSTR& cmdLine,const int& cmdShow);
	//概要: ウィンドウクラスの登録
	//戻り値: 登録完了ならtrue
	bool	RegistWindowClass();
	//概要: ウィンドウの作成
	//引数: インスタンスハンドル
	void	CreateWindows(const HINSTANCE& hInstance);
	//概要: ウィンドウの表示
	//引数: コマンドパラメータ
	void	Show(const int& cmdShow);
	//概要: メッセージ処理＆描画ループ
	//戻り値: 更新するならtrue
	bool	Run();
	

private:
	//概要: WM_PAINTを呼ばないようにする
	void	ValidateMessage();

	//概要: メッセージ処理用コールバック関数
	//引数:	hWnd		ハンドル
	//引数:	msg			メッセージ
	//引数:	wParam		パラメータ
	//引数:	lParam		パラメータ
	//戻り値: LRESULT	出力結果
	static LRESULT	CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	MSG				msg;				//メッセージ
	WNDCLASSEX		windowClass;		//ウィンドウクラス
	const wchar_t*	className;			//クラス名
	const wchar_t*	windowName;			//ウィンドウ名
	bool			isFullScreen;		//フルスクリーンフラグ
	Screen*				screen;			//スクリーン
};