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
////!@brief	��������
//bool	GLDevice::Create()
//{
//	auto window = CreateWindowA("edit", 0, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, 320, 240, 0, 0, 0, 0);
//	auto deviceContext = GetDC(window);
//
//	//�s�N�Z���t�H�[�}�b�g�̍쐬
//	const PIXELFORMATDESCRIPTOR pixelFormatDesc = 
//	{
//		0, 1, PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, 32, 0, 0, 0,
//		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 32, 0, 0, 0, 0, 0, 0, 0
//	};
//	SetPixelFormat(deviceContext, ChoosePixelFormat(deviceContext, &pixelFormatDesc), &pixelFormatDesc);
//	//OpenGl�R���e�L�X�g�̎擾
//	auto context = wglCreateContext(deviceContext);
//	wglMakeCurrent(deviceContext, context);
//	
//	return true;
//}
////!@brief	�������
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
////!@brief �I��
//bool	GLDevice::CleanUp()
//{
//	return true;
//}
////!@brief ����
//bool	GLDevice::Remove()
//{
//	return true;
//}
//
