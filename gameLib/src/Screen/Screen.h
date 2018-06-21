#pragma once

#include <string>
#include <Windows.h>

//----------------------------------------------------------------------------------------
//�T�v: �X�N���[���̏���ێ����܂�
//�T�v: ��ʂ̏�������
//----------------------------------------------------------------------------------------
class Screen
{
public:

	Screen(const int& width, const int& height);
	~Screen();

public:
	//�T�v: �X�N���[���̕����擾
	int		GetWidth() const;
	//�T�v: �X�N���[���̍������擾
	int		GetHeight() const;
	//�T�v: �n���h�����擾
	HWND&	GetHWND();

	//�T�v: �X�N���[���̕��ƍ����̐ݒ�
	void	SetSize(const int& width, const int& height);
	//�T�v: �X�N���[���̃n���h���̐ݒ�
	//void	Sethandle(const HWND& hWnd);


private:
	int		width;
	int		height;
	HWND	hWnd;
};