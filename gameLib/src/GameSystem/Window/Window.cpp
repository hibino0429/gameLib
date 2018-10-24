#include "Window.h"
#include "../../src/GUISystem/GUISystem.h"


//!@brief スクリーン幅とスクリーン高さを指定してウィンドウを生成
//!@param[in] screenWidth スクリーン幅
//!@param[in] screenHeight スクリーン高さ
Window::Window(Screen* screen)
	: isFullScreen(false)
	, screen(screen)
{
	className = L"DirectX11Program";
	windowName = L"DirectX11";
}

//!@brief デストラクタ
Window::~Window()
{
	
}

//!@brief wParamの取得
//!@return wParamの値
int		Window::GetWParam() const
{
	return (int)msg.wParam;
}

//!@brief フルスクリーンにする
//!@param[in] cmdLine コマンドライン
//!@param[in] cmdShow コマンドパラメータ
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

//!@brief ウィンドウクラスの初期化
//!@param[in] hInstance インスタンスハンドル
void	Window::InitWindowClass(const HINSTANCE& hInstance)
{
	windowClass = {
		sizeof(WNDCLASSEX),				// この構造体のサイズ
		CS_CLASSDC,						// ウインドウのスタイル(default)
		WindowProc,						// メッセージ処理関数の登録
		0,								// 通常は使わないので常に0
		0,								// 通常は使わないので常に0
		GetModuleHandle(nullptr),						// インスタンスへのハンドル
		nullptr,						// アイコン（なし）
		LoadCursor(NULL, IDC_ARROW),	// カーソルの形
		nullptr, nullptr,				// 背景なし、メニューなし
		className,						// クラス名の指定
		nullptr							// 小アイコン（なし）
	};
}

//!@brief ウィンドウクラスの登録
//!@return 登録完了ならtrue
bool	Window::RegistWindowClass()
{
	if (RegisterClassEx(&windowClass) == 0)
	{
		return false;
	}
	return true;
}

//!@brief ウィンドウの作成
void	Window::CreateWindows(const HINSTANCE& hInstance)
{
	if (isFullScreen)
	{
		int sw;
		int sh;
		// 画面全体の幅と高さを取得
		sw = GetSystemMetrics(SM_CXSCREEN);
		sh = GetSystemMetrics(SM_CYSCREEN);

		screen->GetHWND() = CreateWindow(
			className, 			// 登録されているクラス名
			windowName, 		// ウインドウ名
			WS_POPUP,			// ウインドウスタイル（ポップアップウインドウを作成）
			0, 					// ウインドウの横方向の位置
			0, 					// ウインドウの縦方向の位置
			screen->GetWidth(), 		// ウインドウの幅
			screen->GetHeight(),		// ウインドウの高さ
			nullptr,			// 親ウインドウのハンドル（省略）
			nullptr,			// メニューや子ウインドウのハンドル
			hInstance, 			// アプリケーションインスタンスのハンドル
			nullptr				// ウインドウの作成データ
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

		// ウィンドウサイズを再設定する
		RECT rect;
		int ww = 0, wh = 0;
		int cw = 0, ch = 0;

		// クライアント領域の外の幅を計算
		GetClientRect(screen->GetHWND(), &rect);		// クライアント部分のサイズの取得
		cw = rect.right - rect.left;					// クライアント領域外の横幅を計算
		ch = rect.bottom - rect.top;					// クライアント領域外の縦幅を計算

														// ウインドウ全体の横幅の幅を計算
		GetWindowRect(screen->GetHWND(), &rect);		// ウインドウ全体のサイズ取得
		ww = rect.right - rect.left;					// ウインドウ全体の幅の横幅を計算
		wh = rect.bottom - rect.top;					// ウインドウ全体の幅の縦幅を計算
		ww = ww - cw;									// クライアント領域以外に必要な幅
		wh = wh - ch;									// クライアント領域以外に必要な高さ

		// ウィンドウサイズの再計算
		ww = screen->GetWidth() + ww;					// 必要なウインドウの幅
		wh = screen->GetHeight() + wh;					// 必要なウインドウの高さ

		// ウインドウサイズの再設定
		SetWindowPos(screen->GetHWND(), HWND_TOP, 0, 0, ww, wh, SWP_NOMOVE);
	}
}

//!@brief ウィンドウの表示
void	Window::Show(const int& cmdShow)
{
	ShowWindow(screen->GetHWND(), cmdShow);
	UpdateWindow(screen->GetHWND());
	ValidateMessage();
}



//!@brief メッセージ処理＆描画ループ
//!@return 更新するならtrue
bool	Window::Run()
{
	if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
	{
		if (msg.message == WM_QUIT)
		{
			return false;	//ループの終了
		}
		else
		{
			//メッセージの翻訳とディスパッチ
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			return true;
		}
	}
	else
	{
		//処理するメッセージがない場合、描画を行う
		//ウィンドウが見えているときだけ描画する
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




//!@brief WM_PAINTを呼ばないようにする
void	Window::ValidateMessage()
{
	ValidateRect(screen->GetHWND(), 0);
}




extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
//!@brief メッセージ処理用コールバック関数
//!@param[in] hWnd ハンドル
//!@param[in] msg メッセージ
//!@param[in] wParam パラメータ
//!@param[in] lParam パラメータ
//!@return 出力結果
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
	case WM_CLOSE:				// ウインドウが閉じられた
		PostQuitMessage(0);		// アプリケーションを終了する
		break;
	case WM_KEYDOWN:				// キーが押された
		if (wParam == VK_ESCAPE) {	// 押されたのはESCキーだ
			PostQuitMessage(0);		// アプリケーションを終了する
		}
		break;
	default:
		return DefWindowProc(hWnd, msg, wParam, lParam);
	}
	return DefWindowProc(hWnd,msg,wParam,lParam);
}