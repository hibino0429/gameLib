//#include "GLDevice.h"
//
//
//GLDevice::GLDevice()
//{
//	
//}
//GLDevice::~GLDevice()
//{
//
//}
//
//
////!@brief	生成処理
//bool	GLDevice::Create()
//{
//	auto window = CreateWindowA("edit", 0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 320, 240, 0, 0, 0, 0);
//	auto deviceContext = GetDC(window);
//
//	//ピクセルフォーマットの作成
//	const PIXELFORMATDESCRIPTOR pixelFormatDesc = 
//	{
//		0, 1, PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 32, 0, 0, 0,
//		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0
//	};
//	SetPixelFormat(deviceContext, ChoosePixelFormat(deviceContext, &pixelFormatDesc), &pixelFormatDesc);
//	//OpenGlコンテキストの取得
//	auto context = wglCreateContext(deviceContext);
//	wglMakeCurrent(deviceContext, context);
//	
//	return true;
//}
////!@brief	解放処理
//void	GLDevice::Run()
//{
//	MSG	msg = {};
//	while (true)
//	{
//		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
//		{
//			if (msg.message == WM_NCLBUTTONDOWN && msg.wParam == HTCLOSE)
//			{
//				return;
//			}
//			TranslateMessage(&msg);
//			DispatchMessage(&msg);
//		}
//		/*glColor3f(1, 1, 0);
//		glRecti(1, 1, -1, 1);
//		SwapBuffers(deviceContext);*/
//	}
//}
////!@brief 終了
//bool	GLDevice::CleanUp()
//{
//	return true;
//}
////!@brief 消失
//bool	GLDevice::Remove()
//{
//	return true;
//}
//
