#include "DXDevice.h"


//�R���X�g���N�^
DXDevice::DXDevice(Screen* screen)
	: screen(screen)
	, device3D(nullptr)
	, deviceContext3D(nullptr)
	, device2D(nullptr)
	, deviceContext2D(nullptr)
	, swapChain(nullptr)
	, textureFactory(nullptr)
	, textFactory(nullptr)
	, renderTargetView(nullptr)
	, texture2D(nullptr)
	, depthStencilView(nullptr)
{

}

//�f�X�g���N�^
DXDevice::~DXDevice()
{
	if (texture2D != nullptr)
	{
		texture2D->Release();
		texture2D = nullptr;
	}
	if (depthStencilView != nullptr)
	{
		depthStencilView->Release();
		depthStencilView = nullptr;
	}
	if (swapChain != nullptr)
	{
		swapChain->Release();
		swapChain = nullptr;
	}
	if (deviceContext3D != nullptr)
	{
		deviceContext3D->Release();
		deviceContext3D = nullptr;
	}
	if (device3D != nullptr)
	{
		device3D->Release();
		device3D = nullptr;
	}
}





ID3D11Device&			DXDevice::GetDevice3D() const
{
	return *device3D; 
}
ID3D11DeviceContext&	DXDevice::GetDeviceContext3D() const
{
	return *deviceContext3D;
}
ID2D1Device&			DXDevice::GetDevice2D() const
{
	return *device2D;
}
ID2D1DeviceContext&		DXDevice::GetDeviceContext2D() const
{
	return *deviceContext2D;
}
IDXGISwapChain&			DXDevice::GetSwapChain() const
{
	return *swapChain;
}
IWICImagingFactory&		DXDevice::GetTextureFactory() const
{
	return *textureFactory;
}
IDWriteFactory&			DXDevice::GetTextFactory() const
{
	return *textFactory;
}

ID3D11RenderTargetView*	DXDevice::GetRenderTargetView() const
{
	return renderTargetView;
}
ID3D11Texture2D*		DXDevice::GetTexture2D() const
{
	return texture2D;
}
ID3D11DepthStencilView*	DXDevice::GetDepthStencilView() const
{
	return depthStencilView;
}



bool	DXDevice::Create()
{
	this->CreateDirect3D();
	return true;
}

void	DXDevice::Run()
{
	
}

bool	DXDevice::CleanUp()
{
	//�f�o�C�X�E�X�e�[�g�̃N���A
	if (&deviceContext3D != nullptr)
	{
		deviceContext3D->ClearState();
		return true;
	}
	return false;
}

bool	DXDevice::Remove()
{
	HRESULT hr = S_OK;

	//�f�o�C�X�̏����m�F
	hr = device3D->GetDeviceRemovedReason();

	switch (hr) {
	case S_OK:	break;	//����
	case DXGI_ERROR_DEVICE_HUNG:
	case DXGI_ERROR_DEVICE_RESET:
		CleanUp();					//Direct3D(�f�o�C�X)�̉��
		if (FAILED(hr))
		{
			return false;	//���s
		}
		break;
	case DXGI_ERROR_DEVICE_REMOVED:
	case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
	case DXGI_ERROR_INVALID_CALL:
	default:
		return false;	//�ǂ����悤���Ȃ��̂ŁA�A�v���P�[�V�������I��
	}
	return true;
}



bool	DXDevice::CreateDirect3D()
{
	//�X���b�v�`�F�C���̐���
	if (!this->CreateSwapChain())
	{
		
	}
	//�o�b�N�o�b�t�@�̐���
	if (!this->CreateBackBuffer())
	{
		
	}


	//device2D�̍쐬
	if (!this->CreateDirect2D())
	{
		MessageBoxA(nullptr, "device2D�̍쐬�Ɏ��s", "CreateDirect2D()", MB_OK);
	}
	
	//�u�����h�X�e�[�g�̍쐬
	this->CreateBlendState();


	return true;
}


bool	DXDevice::CreateSwapChain()
{
	DXGI_SWAP_CHAIN_DESC	swapDesc;

	HRESULT hr;
	SecureZeroMemory(&swapDesc, sizeof(swapDesc));

#if defined(DEBUG) || defined(_DEBUG)
	UINT createDeviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT createDeviceFlag = 0;
#endif

	swapDesc.BufferCount = 1;	//�V���O���o�b�N�o�b�t�@(�����)
	swapDesc.BufferDesc.Width = screen->GetWidth();
	swapDesc.BufferDesc.Height = screen->GetHeight();
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = screen->GetHWND();	//�n���h��
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Windowed = true;	//�E�B�h�E���[�h
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;

	//�h���C�o�[�^�C�v�̗�
	std::array<D3D_DRIVER_TYPE, 5> driverType =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
	};
	//DirectX11�̋@�\���x���̐ݒ�
	D3D_FEATURE_LEVEL feature[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	//�X���b�v�`�F�C���̍쐬
	for (size_t i = 0; i < driverType.size(); i++)
	{
		hr = D3D11CreateDeviceAndSwapChain(
			nullptr,
			driverType[i],
			nullptr,
			createDeviceFlag,
			feature,
			6,
			D3D11_SDK_VERSION,
			&swapDesc,
			&swapChain,
			&device3D,
			nullptr,
			&deviceContext3D
		);
		if (SUCCEEDED(hr))
		{
			break;
		}
	}
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

bool	DXDevice::CreateBackBuffer()
{
	HRESULT hr = S_OK;

	//�X���b�v�`�F�C������ŏ��̃o�b�N�o�b�t�@���擾
	ID3D11Texture2D*	backBuffer;		//�o�b�t�@�A�N�Z�X�p
	hr = GetSwapChain().GetBuffer(
		0,                         // �o�b�N�E�o�b�t�@�̔ԍ�
		__uuidof(ID3D11Texture2D), // �o�b�t�@�ɃA�N�Z�X����C���^�[�t�F�C�X
		(LPVOID*)&backBuffer	   // �o�b�t�@���󂯎��ϐ�
	);

	if (FAILED(hr))
	{
		return false;
	}

	//�o�b�N�o�b�t�@�̏��
	D3D11_TEXTURE2D_DESC	backBufDesc;
	backBuffer->GetDesc(&backBufDesc);

	//�o�b�N�o�b�t�@�̕`��^�[�Q�b�g�r���[�̍쐬
	hr = GetDevice3D().CreateRenderTargetView(
		backBuffer,					// �r���[�ŃA�N�Z�X���郊�\�[�X
		nullptr,					// �`��^�[�Q�b�g�E�r���[�̒�`
		&renderTargetView			// �`��^�[�Q�b�g�E�r���[���󂯎��ϐ�
	);

	if (backBuffer != nullptr)
	{
		backBuffer->Release();
		backBuffer = nullptr;
	}
	if (FAILED(hr))
	{
		return false;
	}

	// �[�x/�X�e���V���E�e�N�X�`���̍쐬
	D3D11_TEXTURE2D_DESC depthDesc = backBufDesc;
	depthDesc.Width     = backBufDesc.Width;   // ��
	depthDesc.Height    = backBufDesc.Height;  // ����
	depthDesc.MipLevels = 1;					// �~�b�v�}�b�v�E���x����
	depthDesc.ArraySize = 1;					// �z��T�C�Y
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;	// �t�H�[�}�b�g(�[�x�̂�)
	depthDesc.SampleDesc.Count   = 1;			// �}���`�T���v�����O�̐ݒ�
	depthDesc.SampleDesc.Quality = 0;			// �}���`�T���v�����O�̕i��
	depthDesc.Usage = D3D11_USAGE_DEFAULT;      // �f�t�H���g�g�p�@
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // �[�x/�X�e���V���Ƃ��Ďg�p
	depthDesc.CPUAccessFlags = 0;				// CPU����̓A�N�Z�X���Ȃ�
	depthDesc.MiscFlags = 0;					// ���̑��̐ݒ�Ȃ�

	hr = GetDevice3D().CreateTexture2D(
		&depthDesc,					// �쐬����2D�e�N�X�`���̐ݒ�
		nullptr,             
		&texture2D					// �쐬�����e�N�X�`�����󂯎��ϐ�
	);

	if (FAILED(hr))
	{
		return false;
	}
	
	//�[�x�X�e���V���r���[�̍쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC	depStenViewDesc;
	depStenViewDesc.Format = depthDesc.Format;            // �r���[�̃t�H�[�}�b�g
	depStenViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depStenViewDesc.Flags = 0;
	depStenViewDesc.Texture2D.MipSlice = 0;

	hr = GetDevice3D().CreateDepthStencilView(
		texture2D,					 // �[�x/�X�e���V���E�r���[�����e�N�X�`��
		&depStenViewDesc,			 // �[�x/�X�e���V���E�r���[�̐ݒ�
		&depthStencilView			 // �쐬�����r���[���󂯎��ϐ�
	);

	if (FAILED(hr))
	{
		return false;
	}

	//�r���[�|�[�g�̐ݒ�
	SetViewPort((float)backBufDesc.Width, (float)backBufDesc.Height);
	return true;
}


bool	DXDevice::CreateBlendState()
{
	HRESULT hr;
	ID3D11BlendState* blendState = nullptr;
	D3D11_BLEND_DESC blendDesc;
	SecureZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	//�A���t�@�u�����f�B���O�̐ݒ�
	blendDesc.RenderTarget[0].BlendEnable = true;									//�u�����f�B���O��L��(�܂��͖���) 
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;						//�ŏ���RGB�f�[�^�\�[�X���w��
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;				//2�Ԗڂ�RGB�f�[�^�\�[�X���w��
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;							//RGB�f�[�^�\�[�X�̑g�������@���`
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;						//�ŏ��̃A���t�@�f�[�^�\�[�X���w��
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;						//2�Ԗڂ̃A���t�@�f�[�^�\�[�X���w��
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;					//�A���t�@�f�[�^�\�[�X�̑g�������@���`
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;	//�������݃}�X�N

	float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
	hr = device3D->CreateBlendState(&blendDesc, &blendState);
	if (FAILED(hr))
	{
		return false;
	}
	deviceContext3D->OMSetBlendState(blendState, blendFactor, 0xffffffff);
	
	return true;
}

bool	DXDevice::CreateDirect2D()
{
	HRESULT hr;
	D2D1_FACTORY_OPTIONS options;
	
#if defined(_DEBUG)
	options.debugLevel = D2D1_DEBUG_LEVEL_INFORMATION;
#endif
	SecureZeroMemory(&options, sizeof(D2D1_FACTORY_OPTIONS));

	ID2D1Factory1* factory = nullptr;

	//Direct2D�t�@�N�g���̍쐬
	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,		//�t�@�N�g���Ƃ��̃t�@�N�g���ɂ���č쐬����郊�\�[�X�̃X���b�h���f��
		options,												//�f�o�b�O���C���[�Ɏw�肳�ꂽ�ڍׂ̃��x��
		&factory);											//���̃��\�b�h���Ԃ����Ƃ��ɁA�V�����t�@�N�g���ւ̃|�C���^�[�̃A�h���X���i�[�����
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "��������1", "a", MB_OK);
		return false;
	}

	IDXGIDevice* dxgiDevice = nullptr;
	//�ړI�̃C���^�[�t�F�[�X���g���邩�𓾂�
	hr = device3D->QueryInterface(&dxgiDevice);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "��������2", "b", MB_OK);
		return false;
	}
	
	//Direct2D��DirectX11�ŘA�g�ł��邩�ǂ���
	hr = factory->CreateDevice(dxgiDevice, &device2D);
	
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "��������3", "c", MB_OK);
		return false;
	}
	//Direct2DContext�̍쐬
	hr = device2D->CreateDeviceContext(
		D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
		&deviceContext2D);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "������4", "d", MB_OK);
		return false;
	}
	//COM�I�u�W�F�N�g�̍쐬
	/*hr = textureFactory->CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER);
	if (FAILED(hr))
	{
		return false;
	}*/
	//DirectWrite�I�u�W�F�N�g���쐬
	/*hr = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		&textureFactory);
	if (FAILED(hr))
	{
		return false;
	}
*/
	return true;
}

void	DXDevice::SetViewPort(float width,float height)
{
	D3D11_VIEWPORT	viewPort;
	SecureZeroMemory(&viewPort, sizeof(viewPort));
	viewPort.Width		= width;
	viewPort.Height		= height;
	viewPort.MinDepth	= 0.0f;
	viewPort.MaxDepth	= 1.0f;
	deviceContext3D->RSSetViewports(1, &viewPort);
}

bool	DXDevice::ChangeScreenSize()
{
	//�`��^�[�Q�b�g�̉���
	deviceContext3D->OMSetRenderTargets(0, nullptr, nullptr);
	if (renderTargetView != nullptr)
	{
		delete renderTargetView;
		renderTargetView = nullptr;
	}

	int width = 640, height = 480;
	//�o�b�N�o�b�t�@�̃T�C�Y�ύX
	swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_B8G8R8A8_UNORM, 0);

	//�`��^�[�Q�b�g�̍Đݒ�
	DXGI_MODE_DESC	descMode;
	descMode.Width						= width;
	descMode.Height						= height;
	descMode.RefreshRate.Numerator		= 60;
	descMode.RefreshRate.Denominator	= 1;
	descMode.Format						= DXGI_FORMAT_R8G8B8A8_UNORM;
	descMode.ScanlineOrdering			= DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;;
	descMode.Scaling					= DXGI_MODE_SCALING_UNSPECIFIED;

	if (FAILED(swapChain->ResizeTarget(&descMode)))
	{
		return false;
	}
	return true;
}

bool	DXDevice::AcquireBackBuffer()
{
	HRESULT hr;

	//�X���b�v�`�F�C������ŏ��̃o�b�N�o�b�t�@���擾
	ID3D11Texture2D*	backBuf;	//�o�b�N�o�b�t�@�̃A�N�Z�X�Ɏg�p����C���^�[�t�F�C�X
	hr = swapChain->GetBuffer(
		0,							//�o�b�N�o�b�t�@�̔ԍ�
		__uuidof(ID3D11Texture2D),	//�o�b�t�@�ɃA�N�Z�X����C���^�[�t�F�C�X
		(LPVOID*)&backBuf			//�o�b�t�@���󂯎��ϐ�
	);

	if (FAILED(hr))
	{
		return false;
	}

	//�o�b�N�o�b�t�@�̏��
	D3D11_TEXTURE2D_DESC	descBackBuf;
	backBuf->GetDesc(&descBackBuf);

	//�o�b�N�o�b�t�@�̕`��^�[�Q�b�g�r���[�̍쐬
	hr = device3D->CreateRenderTargetView(
		backBuf,
		nullptr,
		&renderTargetView
	);
	backBuf->Release();
	if (backBuf != nullptr) { backBuf = nullptr; }

	if (FAILED(hr))
	{
		return false;
	}

	//�[�x�E�X�e���V���e�N�X�`���̍쐬
	D3D11_TEXTURE2D_DESC	descDepth = descBackBuf;
	descDepth.Width = descBackBuf.Width;		//��
	descDepth.Height = descBackBuf.Height;		//����
	descDepth.MipLevels = 1;					//�~�b�v���b�v���x����
	descDepth.ArraySize = 1;					//�z��T�C�Y
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;	//�[�x�t�H�[�}�b�g
	descDepth.SampleDesc.Count = 1;				//�}���`�T���v�����O�̐ݒ�
	descDepth.SampleDesc.Quality = 0;			//�}���`�T���v�����O�̕i��
	descDepth.Usage = D3D11_USAGE_DEFAULT;		//�f�t�H���g�g�p�@
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//�[�x�X�e���V���Ǝg�p
	descDepth.CPUAccessFlags = 0;				//CPU����A�N�Z�X���Ȃ�
	descDepth.MiscFlags = 0;					//���̑��̐ݒ�Ȃ�

	hr = device3D->CreateTexture2D(
		&descDepth,
		nullptr,
		&texture2D
	);
	if (FAILED(hr))
	{
		return false;
	}

	//�[�x�X�e���V���E�r���[�̍쐬
	D3D11_DEPTH_STENCIL_VIEW_DESC	descDSV;
	descDSV.Format = descDepth.Format;	//�r���[�̃t�H�[�}�b�g
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Flags = 0;
	descDSV.Texture2D.MipSlice = 0;
	hr = device3D->CreateDepthStencilView(
		texture2D,				//�[�x�X�e���V���r���[���쐬����e�N�X�`��
		&descDSV,				//�[�x�X�e���V���r���[�̐ݒ�
		&depthStencilView		//�쐬�����r���[���󂯎��ϐ�
	);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}


