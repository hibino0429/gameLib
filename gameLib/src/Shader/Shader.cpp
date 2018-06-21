#include "Shader.h"


//概要: コンストラクタ
Shader::Shader()
{
	vertexBlob = nullptr;
	pixelBlob = nullptr;
	geometryBlob = nullptr;

	vertexShader = nullptr;
	pixelShader = nullptr;
	geometryShader = nullptr;

	blendState = nullptr;
	rasterizerState = nullptr;
	depthStencilState = nullptr;

	inputLayout = nullptr;
}

//概要: デストラクタ
Shader::~Shader()
{
	if (vertexShader != nullptr)
	{
		vertexShader->Release();
	}
	if (pixelShader != nullptr)
	{
		pixelShader->Release();
	}
	if (geometryShader != nullptr)
	{
		geometryShader->Release();
	}
	if (blendState != nullptr)
	{
		blendState->Release();
	}
	if (rasterizerState != nullptr)
	{
		rasterizerState->Release();
	}
	if (depthStencilState != nullptr)
	{
		depthStencilState->Release();
	}

	if (inputLayout != nullptr)
	{
		inputLayout->Release();
	}
}
//概要: 頂点シェーダのコードコンパイル
//戻り値: 成功ならtrue
bool	Shader::ComplieVertexShader()
{
	HRESULT hr;
	hr = D3DX11CompileFromFile(
		L"./data/shaderData/VertexShader.hlsl",
		nullptr, nullptr,
		"VS",
		"vs_4_0",
		compileOption,
		0, nullptr,
		&vertexBlob,
		nullptr, nullptr
	);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

//概要: ピクセルシェーダのコードコンパイル
//戻り値: 成功ならtrue
bool	Shader::CompliePixelShader()
{
	HRESULT hr;
	hr = D3DX11CompileFromFile(
		L"./data/shaderData/PixelShader.hlsl",
		nullptr, nullptr,
		"PS",
		"ps_4_0",
		compileOption,
		0, nullptr,
		&pixelBlob,
		nullptr, nullptr
	);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

//概要: ジオメトリのコードコンパイル
//戻り値: 成功ならtrue
bool	Shader::ComplieGeometryShader()
{
	HRESULT hr;
	hr = D3DX11CompileFromFile(
		L"./data/shaderData/GeometryShader.hlsl",
		nullptr, nullptr,
		"GS",
		"gs_4_0",
		compileOption,
		0, nullptr,
		&geometryBlob,
		nullptr, nullptr
	);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}


//概要: 頂点シェーダの作成
//戻り値: 成功ならtrue
bool	Shader::CreateVertexShader()
{
	HRESULT hr = S_OK;
	DXEngine::GetDevice3D().CreateVertexShader(
		vertexBlob->GetBufferPointer(),		//バイト・コードへのポインタ
		vertexBlob->GetBufferSize(),		//バイト・コードへの長さ
		nullptr,
		&vertexShader						//頂点シェーダを受け取る
	);
	//バイトコードの解放
	//vertexBlob->Release();
	if (FAILED(hr))
	{
		return false;
	}
	
	return true;
}

//概要: ピクセルシェーダの作成
//戻り値: 成功ならtrue
bool	Shader::CreatePixelShader()
{
	HRESULT hr = S_OK;
	DXEngine::GetDevice3D().CreatePixelShader(
		pixelBlob->GetBufferPointer(),			//バイト・コードへのポインタ
		pixelBlob->GetBufferSize(),				//バイト・コードへの長さ
		nullptr,
		&pixelShader							//頂点シェーダを受け取る
	);

	//バイトコードの解放
	pixelBlob->Release();
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
//概要: ジオメトリシェーダの作成
//戻り値: 成功ならtrue
bool	Shader::CreateGeometryShader()
{
	HRESULT hr = S_OK;
	DXEngine::GetDevice3D().CreateGeometryShader(
		geometryBlob->GetBufferPointer(),		//バイト・コードへのポインタ
		geometryBlob->GetBufferSize(),			//バイト・コードへの長さ
		nullptr,
		&geometryShader							//頂点シェーダを受け取る
	);
	//バイトコードの解放
	geometryBlob->Release();
	if (FAILED(hr))
	{
		return false;
	}
	
	return true;
}






//概要: シェーダの定数バッファの設定
void	Shader::SetShaderConstantBuffer()
{
	/*Dev::GetDeviceContext()->VSSetConstantBuffers(0, 3, Dev::GetConstantBuffer());
	Dev::GetDeviceContext()->GSSetConstantBuffers(0, 3, Dev::GetConstantBuffer());
	Dev::GetDeviceContext()->PSSetConstantBuffers(0, 3, Dev::GetConstantBuffer());*/
}


//概要: 頂点インプットレイアウトの作成
//戻り値: 成功ならtrue
bool	Shader::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC	layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//頂点インプットレイアウトの作成
	if (FAILED(DXEngine::GetDevice3D().CreateInputLayout(layout, numElements,
		vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &inputLayout)))
	{
		return false;
	}
	
	vertexBlob->Release();
	return true;
}


//概要: 頂点シェーダオブジェクトの取得
ID3D11VertexShader*	Shader::GetVertexShader() const
{
	return vertexShader;
}
//概要: ピクセルシェーダオブジェクトの取得
ID3D11PixelShader*	Shader::GetPixelShader() const
{
	return pixelShader;
}


//概要: ブレンド・ステート・オブジェクトの作成
//戻り値: 成功ならtrue
bool	Shader::CreateBlendState()
{
	D3D11_BLEND_DESC	blendDesc;
	ZeroMemory(&blendDesc, sizeof(D3D11_BLEND_DESC));
	blendDesc.AlphaToCoverageEnable = FALSE;
	blendDesc.IndependentBlendEnable = FALSE;
	blendDesc.RenderTarget[0].BlendEnable = FALSE;
	blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	HRESULT hr;
	hr = DXEngine::GetDevice3D().CreateBlendState(&blendDesc, &blendState);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

//概要: ラスタライザ・ステート・オブジェクトの作成
//戻り値: 成功ならtrue
bool	Shader::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;   // 普通に描画する
	rasterizerDesc.CullMode = D3D11_CULL_NONE;    // 両面を描画する
	rasterizerDesc.FrontCounterClockwise = FALSE; // 時計回りが表面
	rasterizerDesc.DepthBias = 0;
	rasterizerDesc.DepthBiasClamp = 0;
	rasterizerDesc.SlopeScaledDepthBias = 0;
	rasterizerDesc.DepthClipEnable = TRUE;
	rasterizerDesc.ScissorEnable = FALSE;
	rasterizerDesc.MultisampleEnable = FALSE;
	rasterizerDesc.AntialiasedLineEnable = FALSE;

	HRESULT hr;
	hr = DXEngine::GetDevice3D().CreateRasterizerState(&rasterizerDesc,&rasterizerState);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}


//概要: 深度/ステンシル・ステート・オブジェクトの作成
//戻り値: 成功ならtrue
bool	Shader::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	depthStencilDesc.DepthEnable = TRUE;							// 深度テストあり
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // 書き込む
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;				// 手前の物体を描画
	depthStencilDesc.StencilEnable = FALSE;		// ステンシル・テストなし
	depthStencilDesc.StencilReadMask = 0;		// ステンシル読み込みマスク。
	depthStencilDesc.StencilWriteMask = 0;		// ステンシル書き込みマスク。
    // 面が表を向いている場合のステンシル・テストの設定
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;		// 維持
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;  // 維持
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		// 維持
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER;		// 常に失敗
	// 面が裏を向いている場合のステンシル・テストの設定
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;		// 維持
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;   // 維持
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		// 維持
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;		// 常に成功

	HRESULT hr;
	hr = DXEngine::GetDevice3D().CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
	
}