#include "Screen.h"


//コンストラクタ
Screen::Screen(const int& width, const int&height)
	: width(width),height(height)
{

}

//デストラクタ
Screen::~Screen()
{

}



//概要: スクリーンの幅を取得
int		Screen::GetWidth() const
{
	return width;
}
//概要: スクリーンの高さを取得
int		Screen::GetHeight() const
{
	return height;
}

//概要: ハンドルを取得
HWND&	Screen::GetHWND()
{
	return hWnd;
}

//概要: スクリーンの幅と高さの設定
void	Screen::SetSize(const int& width, const int& height)
{
	this->width = width;
	this->height = height;
}