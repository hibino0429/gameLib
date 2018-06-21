#include "Shader.h"


//�T�v: �R���X�g���N�^
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

//�T�v: �f�X�g���N�^
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
//�T�v: ���_�V�F�[�_�̃R�[�h�R���p�C��
//�߂�l: �����Ȃ�true
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

//�T�v: �s�N�Z���V�F�[�_�̃R�[�h�R���p�C��
//�߂�l: �����Ȃ�true
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

//�T�v: �W�I���g���̃R�[�h�R���p�C��
//�߂�l: �����Ȃ�true
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


//�T�v: ���_�V�F�[�_�̍쐬
//�߂�l: �����Ȃ�true
bool	Shader::CreateVertexShader()
{
	HRESULT hr = S_OK;
	DXEngine::GetDevice3D().CreateVertexShader(
		vertexBlob->GetBufferPointer(),		//�o�C�g�E�R�[�h�ւ̃|�C���^
		vertexBlob->GetBufferSize(),		//�o�C�g�E�R�[�h�ւ̒���
		nullptr,
		&vertexShader						//���_�V�F�[�_���󂯎��
	);
	//�o�C�g�R�[�h�̉��
	//vertexBlob->Release();
	if (FAILED(hr))
	{
		return false;
	}
	
	return true;
}

//�T�v: �s�N�Z���V�F�[�_�̍쐬
//�߂�l: �����Ȃ�true
bool	Shader::CreatePixelShader()
{
	HRESULT hr = S_OK;
	DXEngine::GetDevice3D().CreatePixelShader(
		pixelBlob->GetBufferPointer(),			//�o�C�g�E�R�[�h�ւ̃|�C���^
		pixelBlob->GetBufferSize(),				//�o�C�g�E�R�[�h�ւ̒���
		nullptr,
		&pixelShader							//���_�V�F�[�_���󂯎��
	);

	//�o�C�g�R�[�h�̉��
	pixelBlob->Release();
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}
//�T�v: �W�I���g���V�F�[�_�̍쐬
//�߂�l: �����Ȃ�true
bool	Shader::CreateGeometryShader()
{
	HRESULT hr = S_OK;
	DXEngine::GetDevice3D().CreateGeometryShader(
		geometryBlob->GetBufferPointer(),		//�o�C�g�E�R�[�h�ւ̃|�C���^
		geometryBlob->GetBufferSize(),			//�o�C�g�E�R�[�h�ւ̒���
		nullptr,
		&geometryShader							//���_�V�F�[�_���󂯎��
	);
	//�o�C�g�R�[�h�̉��
	geometryBlob->Release();
	if (FAILED(hr))
	{
		return false;
	}
	
	return true;
}






//�T�v: �V�F�[�_�̒萔�o�b�t�@�̐ݒ�
void	Shader::SetShaderConstantBuffer()
{
	/*Dev::GetDeviceContext()->VSSetConstantBuffers(0, 3, Dev::GetConstantBuffer());
	Dev::GetDeviceContext()->GSSetConstantBuffers(0, 3, Dev::GetConstantBuffer());
	Dev::GetDeviceContext()->PSSetConstantBuffers(0, 3, Dev::GetConstantBuffer());*/
}


//�T�v: ���_�C���v�b�g���C�A�E�g�̍쐬
//�߂�l: �����Ȃ�true
bool	Shader::CreateInputLayout()
{
	D3D11_INPUT_ELEMENT_DESC	layout[] =
	{
		{"POSITION",0,DXGI_FORMAT_R32G32B32A32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 }
	};

	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	//���_�C���v�b�g���C�A�E�g�̍쐬
	if (FAILED(DXEngine::GetDevice3D().CreateInputLayout(layout, numElements,
		vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &inputLayout)))
	{
		return false;
	}
	
	vertexBlob->Release();
	return true;
}


//�T�v: ���_�V�F�[�_�I�u�W�F�N�g�̎擾
ID3D11VertexShader*	Shader::GetVertexShader() const
{
	return vertexShader;
}
//�T�v: �s�N�Z���V�F�[�_�I�u�W�F�N�g�̎擾
ID3D11PixelShader*	Shader::GetPixelShader() const
{
	return pixelShader;
}


//�T�v: �u�����h�E�X�e�[�g�E�I�u�W�F�N�g�̍쐬
//�߂�l: �����Ȃ�true
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

//�T�v: ���X�^���C�U�E�X�e�[�g�E�I�u�W�F�N�g�̍쐬
//�߂�l: �����Ȃ�true
bool	Shader::CreateRasterizerState()
{
	D3D11_RASTERIZER_DESC rasterizerDesc;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;   // ���ʂɕ`�悷��
	rasterizerDesc.CullMode = D3D11_CULL_NONE;    // ���ʂ�`�悷��
	rasterizerDesc.FrontCounterClockwise = FALSE; // ���v��肪�\��
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


//�T�v: �[�x/�X�e���V���E�X�e�[�g�E�I�u�W�F�N�g�̍쐬
//�߂�l: �����Ȃ�true
bool	Shader::CreateDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc;
	depthStencilDesc.DepthEnable = TRUE;							// �[�x�e�X�g����
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;   // ��������
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;				// ��O�̕��̂�`��
	depthStencilDesc.StencilEnable = FALSE;		// �X�e���V���E�e�X�g�Ȃ�
	depthStencilDesc.StencilReadMask = 0;		// �X�e���V���ǂݍ��݃}�X�N�B
	depthStencilDesc.StencilWriteMask = 0;		// �X�e���V���������݃}�X�N�B
    // �ʂ��\�������Ă���ꍇ�̃X�e���V���E�e�X�g�̐ݒ�
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;		// �ێ�
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;  // �ێ�
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		// �ێ�
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_NEVER;		// ��Ɏ��s
	// �ʂ����������Ă���ꍇ�̃X�e���V���E�e�X�g�̐ݒ�
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;		// �ێ�
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;   // �ێ�
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;		// �ێ�
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;		// ��ɐ���

	HRESULT hr;
	hr = DXEngine::GetDevice3D().CreateDepthStencilState(&depthStencilDesc, &depthStencilState);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
	
}