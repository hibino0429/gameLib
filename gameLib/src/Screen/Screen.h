#pragma once

#include <string>
#include <Windows.h>

//----------------------------------------------------------------------------------------
//概要: スクリーンの情報を保持します
//概要: 画面の情報を持つ
//----------------------------------------------------------------------------------------
class Screen
{
public:

	Screen(const int& width, const int& height);
	~Screen();

public:
	//概要: スクリーンの幅を取得
	int		GetWidth() const;
	//概要: スクリーンの高さを取得
	int		GetHeight() const;
	//概要: ハンドルを取得
	HWND&	GetHWND();

	//概要: スクリーンの幅と高さの設定
	void	SetSize(const int& width, const int& height);
	//概要: スクリーンのハンドルの設定
	//void	Sethandle(const HWND& hWnd);


private:
	int		width;
	int		height;
	HWND	hWnd;
};