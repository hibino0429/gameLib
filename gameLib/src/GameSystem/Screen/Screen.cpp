#include "Screen.h"


//�R���X�g���N�^
Screen::Screen(const int& width, const int&height)
	: width(width),height(height)
{

}

//�f�X�g���N�^
Screen::~Screen()
{

}



//�T�v: �X�N���[���̕����擾
int		Screen::GetWidth() const
{
	return width;
}
//�T�v: �X�N���[���̍������擾
int		Screen::GetHeight() const
{
	return height;
}

//�T�v: �n���h�����擾
HWND&	Screen::GetHWND()
{
	return hWnd;
}

//�T�v: �X�N���[���̕��ƍ����̐ݒ�
void	Screen::SetSize(const int& width, const int& height)
{
	this->width = width;
	this->height = height;
}