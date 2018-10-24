#pragma once
#include <iostream>
#include <Windows.h>
#include <string>

#include "../../src/GameSystem/GameMain/GameMain.h"


//------------------------------------------------------------------------
//!@class		Window
//!@brief	�E�B���h�E�N���X
//------------------------------------------------------------------------
class Window
{
public:
	//�T�v: �X�N���[���̏������ƂɃE�B���h�E�𐶐�
	//����: screen �X�N���[�����̃|�C���^
	Window(Screen* screen);
	~Window();

	//�T�v: wParam�̎擾
	//�߂�l: wParam��int�l
	int		GetWParam() const;

	//�T�v: �E�B���h�E�N���X�̏�����
	//����: hInstance �C���X�^���X�n���h��
	void	InitWindowClass(const HINSTANCE& hInstance);
	//�T�v: �t���X�N���[���ɂ���
	//����: cmdLine �R�}���h���C��
	//����: cmdShow �R�}���h�p�����[�^
	void	FullScreen(const LPWSTR& cmdLine,const int& cmdShow);
	//�T�v: �E�B���h�E�N���X�̓o�^
	//�߂�l: �o�^�����Ȃ�true
	bool	RegistWindowClass();
	//�T�v: �E�B���h�E�̍쐬
	//����: �C���X�^���X�n���h��
	void	CreateWindows(const HINSTANCE& hInstance);
	//�T�v: �E�B���h�E�̕\��
	//����: �R�}���h�p�����[�^
	void	Show(const int& cmdShow);
	//�T�v: ���b�Z�[�W�������`�惋�[�v
	//�߂�l: �X�V����Ȃ�true
	bool	Run();
	

private:
	//�T�v: WM_PAINT���Ă΂Ȃ��悤�ɂ���
	void	ValidateMessage();

	//�T�v: ���b�Z�[�W�����p�R�[���o�b�N�֐�
	//����:	hWnd		�n���h��
	//����:	msg			���b�Z�[�W
	//����:	wParam		�p�����[�^
	//����:	lParam		�p�����[�^
	//�߂�l: LRESULT	�o�͌���
	static LRESULT	CALLBACK WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

private:
	MSG				msg;				//���b�Z�[�W
	WNDCLASSEX		windowClass;		//�E�B���h�E�N���X
	const wchar_t*	className;			//�N���X��
	const wchar_t*	windowName;			//�E�B���h�E��
	bool			isFullScreen;		//�t���X�N���[���t���O
	Screen*				screen;			//�X�N���[��
};