#include "DXDevice.h"


//コンストラクタ
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

//デストラクタ
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
	//デバイス・ステートのクリア
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

	//デバイスの消失確認
	hr = device3D->GetDeviceRemovedReason();

	switch (hr) {
	case S_OK:	break;	//正常
	case DXGI_ERROR_DEVICE_HUNG:
	case DXGI_ERROR_DEVICE_RESET:
		CleanUp();					//Direct3D(デバイス)の解放
		if (FAILED(hr))
		{
			return false;	//失敗
		}
		break;
	case DXGI_ERROR_DEVICE_REMOVED:
	case DXGI_ERROR_DRIVER_INTERNAL_ERROR:
	case DXGI_ERROR_INVALID_CALL:
	default:
		return false;	//どうしようもないので、アプリケーションを終了
	}
	return true;
}



bool	DXDevice::CreateDirect3D()
{
	//スワップチェインの生成
	if (!this->CreateSwapChain())
	{
		
	}
	//バックバッファの生成
	if (!this->CreateBackBuffer())
	{
		
	}


	//device2Dの作成
	if (!this->CreateDirect2D())
	{
		MessageBoxA(nullptr, "device2Dの作成に失敗", "CreateDirect2D()", MB_OK);
	}
	
	//ブレンドステートの作成
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

	swapDesc.BufferCount = 1;	//シングルバックバッファ(裏画面)
	swapDesc.BufferDesc.Width = screen->GetWidth();
	swapDesc.BufferDesc.Height = screen->GetHeight();
	swapDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.OutputWindow = screen->GetHWND();	//ハンドル
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.Windowed = true;	//ウィドウモード
	swapDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapDesc.Flags = 0;

	//ドライバータイプの列挙
	std::array<D3D_DRIVER_TYPE, 5> driverType =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE,
		D3D_DRIVER_TYPE_SOFTWARE,
	};
	//DirectX11の機能レベルの設定
	D3D_FEATURE_LEVEL feature[] = {
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1,
	};

	//スワップチェインの作成
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

	//スワップチェインから最初のバックバッファを取得
	ID3D11Texture2D*	backBuffer;		//バッファアクセス用
	hr = GetSwapChain().GetBuffer(
		0,                         // バック・バッファの番号
		__uuidof(ID3D11Texture2D), // バッファにアクセスするインターフェイス
		(LPVOID*)&backBuffer	   // バッファを受け取る変数
	);

	if (FAILED(hr))
	{
		return false;
	}

	//バックバッファの情報
	D3D11_TEXTURE2D_DESC	backBufDesc;
	backBuffer->GetDesc(&backBufDesc);

	//バックバッファの描画ターゲットビューの作成
	hr = GetDevice3D().CreateRenderTargetView(
		backBuffer,					// ビューでアクセスするリソース
		nullptr,					// 描画ターゲット・ビューの定義
		&renderTargetView			// 描画ターゲット・ビューを受け取る変数
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

	// 深度/ステンシル・テクスチャの作成
	D3D11_TEXTURE2D_DESC depthDesc = backBufDesc;
	depthDesc.Width     = backBufDesc.Width;   // 幅
	depthDesc.Height    = backBufDesc.Height;  // 高さ
	depthDesc.MipLevels = 1;					// ミップマップ・レベル数
	depthDesc.ArraySize = 1;					// 配列サイズ
	depthDesc.Format = DXGI_FORMAT_D32_FLOAT;	// フォーマット(深度のみ)
	depthDesc.SampleDesc.Count   = 1;			// マルチサンプリングの設定
	depthDesc.SampleDesc.Quality = 0;			// マルチサンプリングの品質
	depthDesc.Usage = D3D11_USAGE_DEFAULT;      // デフォルト使用法
	depthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL; // 深度/ステンシルとして使用
	depthDesc.CPUAccessFlags = 0;				// CPUからはアクセスしない
	depthDesc.MiscFlags = 0;					// その他の設定なし

	hr = GetDevice3D().CreateTexture2D(
		&depthDesc,					// 作成する2Dテクスチャの設定
		nullptr,             
		&texture2D					// 作成したテクスチャを受け取る変数
	);

	if (FAILED(hr))
	{
		return false;
	}
	
	//深度ステンシルビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC	depStenViewDesc;
	depStenViewDesc.Format = depthDesc.Format;            // ビューのフォーマット
	depStenViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depStenViewDesc.Flags = 0;
	depStenViewDesc.Texture2D.MipSlice = 0;

	hr = GetDevice3D().CreateDepthStencilView(
		texture2D,					 // 深度/ステンシル・ビューを作るテクスチャ
		&depStenViewDesc,			 // 深度/ステンシル・ビューの設定
		&depthStencilView			 // 作成したビューを受け取る変数
	);

	if (FAILED(hr))
	{
		return false;
	}

	//ビューポートの設定
	SetViewPort((float)backBufDesc.Width, (float)backBufDesc.Height);
	return true;
}


bool	DXDevice::CreateBlendState()
{
	HRESULT hr;
	ID3D11BlendState* blendState = nullptr;
	D3D11_BLEND_DESC blendDesc;
	SecureZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));

	//アルファブレンディングの設定
	blendDesc.RenderTarget[0].BlendEnable = true;									//ブレンディングを有効(または無効) 
	blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;						//最初のRGBデータソースを指定
	blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;				//2番目のRGBデータソースを指定
	blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;							//RGBデータソースの組合せ方法を定義
	blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;						//最初のアルファデータソースを指定
	blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ONE;						//2番目のアルファデータソースを指定
	blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;					//アルファデータソースの組合せ方法を定義
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;	//書き込みマスク

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

	//Direct2Dファクトリの作成
	hr = D2D1CreateFactory(
		D2D1_FACTORY_TYPE_SINGLE_THREADED,		//ファクトリとそのファクトリによって作成されるリソースのスレッドモデル
		options,												//デバッグレイヤーに指定された詳細のレベル
		&factory);											//このメソッドが返されるときに、新しいファクトリへのポインターのアドレスが格納される
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "ここかな1", "a", MB_OK);
		return false;
	}

	IDXGIDevice* dxgiDevice = nullptr;
	//目的のインターフェースが使えるかを得る
	hr = device3D->QueryInterface(&dxgiDevice);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "ここかな2", "b", MB_OK);
		return false;
	}
	
	//Direct2DとDirectX11で連携できるかどうか
	hr = factory->CreateDevice(dxgiDevice, &device2D);
	
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "ここかな3", "c", MB_OK);
		return false;
	}
	//Direct2DContextの作成
	hr = device2D->CreateDeviceContext(
		D2D1_DEVICE_CONTEXT_OPTIONS_NONE,
		&deviceContext2D);
	if (FAILED(hr))
	{
		MessageBoxA(nullptr, "ここか4", "d", MB_OK);
		return false;
	}
	//COMオブジェクトの作成
	/*hr = textureFactory->CoCreateInstance(
		CLSID_WICImagingFactory,
		nullptr,
		CLSCTX_INPROC_SERVER);
	if (FAILED(hr))
	{
		return false;
	}*/
	//DirectWriteオブジェクトを作成
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
	//描画ターゲットの解除
	deviceContext3D->OMSetRenderTargets(0, nullptr, nullptr);
	if (renderTargetView != nullptr)
	{
		delete renderTargetView;
		renderTargetView = nullptr;
	}

	int width = 640, height = 480;
	//バックバッファのサイズ変更
	swapChain->ResizeBuffers(1, width, height, DXGI_FORMAT_B8G8R8A8_UNORM, 0);

	//描画ターゲットの再設定
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

	//スワップチェインから最初のバックバッファを取得
	ID3D11Texture2D*	backBuf;	//バックバッファのアクセスに使用するインターフェイス
	hr = swapChain->GetBuffer(
		0,							//バックバッファの番号
		__uuidof(ID3D11Texture2D),	//バッファにアクセスするインターフェイス
		(LPVOID*)&backBuf			//バッファを受け取る変数
	);

	if (FAILED(hr))
	{
		return false;
	}

	//バックバッファの情報
	D3D11_TEXTURE2D_DESC	descBackBuf;
	backBuf->GetDesc(&descBackBuf);

	//バックバッファの描画ターゲットビューの作成
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

	//深度・ステンシルテクスチャの作成
	D3D11_TEXTURE2D_DESC	descDepth = descBackBuf;
	descDepth.Width = descBackBuf.Width;		//幅
	descDepth.Height = descBackBuf.Height;		//高さ
	descDepth.MipLevels = 1;					//ミップラップレベル数
	descDepth.ArraySize = 1;					//配列サイズ
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;	//深度フォーマット
	descDepth.SampleDesc.Count = 1;				//マルチサンプリングの設定
	descDepth.SampleDesc.Quality = 0;			//マルチサンプリングの品質
	descDepth.Usage = D3D11_USAGE_DEFAULT;		//デフォルト使用法
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;	//深度ステンシルと使用
	descDepth.CPUAccessFlags = 0;				//CPUからアクセスしない
	descDepth.MiscFlags = 0;					//その他の設定なし

	hr = device3D->CreateTexture2D(
		&descDepth,
		nullptr,
		&texture2D
	);
	if (FAILED(hr))
	{
		return false;
	}

	//深度ステンシル・ビューの作成
	D3D11_DEPTH_STENCIL_VIEW_DESC	descDSV;
	descDSV.Format = descDepth.Format;	//ビューのフォーマット
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Flags = 0;
	descDSV.Texture2D.MipSlice = 0;
	hr = device3D->CreateDepthStencilView(
		texture2D,				//深度ステンシルビューを作成するテクスチャ
		&descDSV,				//深度ステンシルビューの設定
		&depthStencilView		//作成したビューを受け取る変数
	);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}


