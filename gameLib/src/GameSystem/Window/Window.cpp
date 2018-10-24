#include "Window.h"
#include "../../src/GUISystem/GUISystem.h"


//!@brief �X�N���[�����ƃX�N���[���������w�肵�ăE�B���h�E�𐶐�
//!@param[in] screenWidth �X�N���[����
//!@param[in] screenHeight �X�N���[������
Window::Window(Screen* screen)
	: isFullScreen(false)
	, screen(screen)
{
	className = L"DirectX11Program";
	windowName = L"DirectX11";
}

//!@brief �f�X�g���N�^
Window::~Window()
{
	
}

//!@brief wParam�̎擾
//!@return wParam�̒l
int		Window::GetWParam() const
{
	return (int)msg.wParam;
}

//!@brief �t���X�N���[���ɂ���
//!@param[in] cmdLine �R�}���h���C��
//!@param[in] cmdShow �R�}���h�p�����[�^
void	Window::FullScreen(const LPWSTR& cmdLine,const int& cmdShow)
{
	for (int i = 0; i < cmdShow; ++i)
	{
		if (_stricmp((char*)&cmdLine[i], "/f") == 0)
		{
			isFullScreen = true;
			break;
		}
	}
}

//!@brief �E�B���h�E�N���X�̏�����
//!@param[in] hInstance �C���X�^���X�n���h��
void	Window::InitWindowClass(const HINSTANCE& hInstance)
{
	windowClass = {
		sizeof(WNDCLASSEX),				// ���̍\���̂̃T�C�Y
		CS_CLASSDC,						// �E�C���h�E�̃X�^�C��(default)
		WindowProc,						// ���b�Z�[�W�����֐��̓o�^
		0,								// �ʏ�͎g��Ȃ��̂ŏ��0
		0,								// �ʏ�͎g��Ȃ��̂ŏ��0
		GetModuleHandle(nullptr),						// �C���X�^���X�ւ̃n���h��
		nullptr,						// �A�C�R���i�Ȃ��j
		LoadCursor(NULL, IDC_ARROW),	// �J�[�\���̌`
		nullptr, nullptr,				// �w�i�Ȃ��A���j���[�Ȃ�
		className,						// �N���X���̎w��
		nullptr							// ���A�C�R���i�Ȃ��j
	};
}

//!@brief �E�B���h�E�N���X�̓o�^
//!@return �o�^�����Ȃ�true
bool	Window::RegistWindowClass()
{
	if (RegisterClassEx(&windowClass) == 0)
	{
		return false;
	}
	return true;
}

//!@brief �E�B���h�E�̍쐬
void	Window::CreateWindows(const HINSTANCE& hInstance)
{
	if (isFullScreen)
	{
		int sw;
		int sh;
		// ��ʑS�̂̕��ƍ������擾
		sw = GetSystemMetrics(SM_CXSCREEN);
		sh = GetSystemMetrics(SM_CYSCREEN);

		screen->GetHWND() = CreateWindow(
			className, 			// �o�^����Ă���N���X��
			windowName, 		// �E�C���h�E��
			WS_POPUP,			// �E�C���h�E�X�^�C���i�|�b�v�A�b�v�E�C���h�E���쐬�j
			0, 					// �E�C���h�E�̉������̈ʒu
			0, 					// �E�C���h�E�̏c�����̈ʒu
			screen->GetWidth(), 		// �E�C���h�E�̕�
			screen->GetHeight(),		// �E�C���h�E�̍���
			nullptr,			// �e�E�C���h�E�̃n���h���i�ȗ��j
			nullptr,			// ���j���[��q�E�C���h�E�̃n���h��
			hInstance, 			// �A�v���P�[�V�����C���X�^���X�̃n���h��
			nullptr				// �E�C���h�E�̍쐬�f�[�^
		);
	}
	else
	{
		screen->GetHWND() = CreateWindow(
			className,
			windowName,
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT, CW_USEDEFAULT,
			CW_USEDEFAULT, CW_USEDEFAULT,
			nullptr, nullptr, hInstance, nullptr
		);

		// �E�B���h�E�T�C�Y���Đݒ肷��
		RECT rect;
		int ww = 0, wh = 0;
		int cw = 0, ch = 0;

		// �N���C�A���g�̈�̊O�̕����v�Z
		GetClientRect(screen->GetHWND(), &rect);		// �N���C�A���g�����̃T�C�Y�̎擾
		cw = rect.right - rect.left;					// �N���C�A���g�̈�O�̉������v�Z
		ch = rect.bottom - rect.top;					// �N���C�A���g�̈�O�̏c�����v�Z

														// �E�C���h�E�S�̂̉����̕����v�Z
		GetWindowRect(screen->GetHWND(), &rect);		// �E�C���h�E�S�̂̃T�C�Y�擾
		ww = rect.right - rect.left;					// �E�C���h�E�S�̂̕��̉������v�Z
		wh = rect.bottom - rect.top;					// �E�C���h�E�S�̂̕��̏c�����v�Z
		ww = ww - cw;									// �N���C�A���g�̈�ȊO�ɕK�v�ȕ�
		wh = wh - ch;									// �N���C�A���g�̈�ȊO�ɕK�v�ȍ���

		// �E�B���h�E�T�C�Y�̍Čv�Z
		ww = screen->GetWidth() + ww;					// �K�v�ȃE�C���h�E�̕�
		wh = screen->GetHeight() + wh;					// �K�v�ȃE�C���h�E�̍���

		// �E�C���h�E�T�C�Y�̍Đݒ�
		SetWindowPos(screen->GetHWND(), HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);
	}
}

//!@brief �E�B���h�E�̕\��
void	Window::Show(const int& cmdShow)
{
	ShowWindow(screen->GetHWND(), cmdShow);
	UpdateWindow(screen->GetHWND());
	ValidateMessage();
}



//!@brief ���b�Z�[�W�������`�惋�[�v
//!@return �X�V����Ȃ�true
bool	Window::Run()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;	//���[�v�̏I��
		}
		else
		{
			//���b�Z�[�W�̖|��ƃf�B�X�p�b�`
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			return true;
		}
	}
	else
	{
		//�������郁�b�Z�[�W���Ȃ��ꍇ�A�`����s��
		//�E�B���h�E�������Ă���Ƃ������`�悷��
		WINDOWPLACEMENT	windowPlacement;
		GetWindowPlacement(screen->GetHWND(), &windowPlacement);
		
		if ((windowPlacement.showCmd != SW_HIDE) &&
			(windowPlacement.showCmd != SW_MINIMIZE) &&
			(windowPlacement.showCmd != SW_SHOWMINIMIZED) &&
			(windowPlacement.showCmd != SW_SHOWMINNOACTIVE))
		{
				return true;
		}
	}
	return true;
}




//!@brief WM_PAINT���Ă΂Ȃ��悤�ɂ���
void	Window::ValidateMessage()
{
	ValidateRect(screen->GetHWND(), 0);
}




extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//!@brief ���b�Z�[�W�����p�R�[���o�b�N�֐�
//!@param[in] hWnd �n���h��
//!@param[in] msg ���b�Z�[�W
//!@param[in] wParam �p�����[�^
//!@param[in] lParam �p�����[�^
//!@return �o�͌���
LRESULT	CALLBACK Window::WindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam))
	{
		return true;
	}


	switch (msg) {
	case WM_SIZE:
		if (wParam != SIZE_MINIMIZED)
		{
			ImGui_ImplDX11_InvalidateDeviceObjects();
			ImGui_ImplDX11_CreateDeviceObjects();
		}
		break;
	case WM_CLOSE:				// �E�C���h�E������ꂽ
		PostQuitMessage(0);		// �A�v���P�[�V�������I������
		break;
	case WM_KEYDOWN:				// �L�[�������ꂽ
		if (wParam == VK_ESCAPE) {	// �����ꂽ�̂�ESC�L�[��
			PostQuitMessage(0);		// �A�v���P�[�V�������I������
		}
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}