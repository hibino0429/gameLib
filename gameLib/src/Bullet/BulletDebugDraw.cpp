#include "BulletDebugDraw.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"


//�v���R���p�C���ς݃V�F�[�_�R�[�h
#include "../../src/Bullet/btdbg_psh.hpp"
#include "../../src/Bullet/btdbg_vsh.hpp"


//���b�V���f�[�^�̃C���N���[�h
namespace MeshSphere
{
#include "../Bullet/mesh/sphere.hpp"
}
namespace MeshBox
{
#include "../Bullet/mesh/box.hpp"
}
namespace MeshCylinder
{
#include "../Bullet/mesh/cylinder.hpp"
}
namespace MeshCapsule
{
#include "../Bullet/mesh/capsule.hpp"
}
namespace MeshCone
{
#include "../Bullet/mesh/cone.hpp"
}


namespace Physics
{
	//�V�F�[�_�萔�o�b�t�@
	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4	projMatrix;
		DirectX::XMFLOAT4X4	viewMatrix;
		DirectX::XMFLOAT4X4	world;
		DirectX::XMFLOAT4	diffuse;
	};


	BulletDebugDraw::BulletDebugDraw()
	{
		renderScene = (RenderScene*)_aligned_malloc(sizeof(RenderScene), __alignof(RenderScene));
		renderScene->projMatrix = renderScene->viewMatrix = DirectX::XMMatrixIdentity();

		Setup();
		setDebugMode(btIDebugDraw::DBG_DrawWireframe);
	}

	BulletDebugDraw::~BulletDebugDraw()
	{
		_aligned_free(renderScene);
		for (auto it : meshModels)
		{
			_aligned_free(it);
			it = nullptr;
		}
	}

	void BulletDebugDraw::Draw()
	{
		for (auto it : meshModels)
		{
			it->Draw(DirectX::XMMatrixIdentity());
		}
	}

	/*void BulletDebugDraw::SetCameraMatrix(Camera & camera)
	{
		for (auto it : meshModels)
		{
			it->SetCameraMatrix(camera);
		}
	}*/

	void BulletDebugDraw::CreateBox()
	{
		MeshModel*	meshModel = new MeshModel();
		meshModel->CreateBox();
		meshModels.emplace_back(meshModel);
	}

	void BulletDebugDraw::CreateSphere()
	{
		MeshModel*	meshModel = new MeshModel();
		meshModel->CreateSphere();
		meshModels.emplace_back(meshModel);
	}

	void BulletDebugDraw::CreateCylinder()
	{
		MeshModel*	meshModel = new MeshModel();
		meshModel->CreateCylinder();
		meshModels.emplace_back(meshModel);
	}

	void BulletDebugDraw::CreteCone()
	{
		MeshModel*	meshModel = new MeshModel();
		meshModel->CreateCone();
		meshModels.emplace_back(meshModel);
	}

	void BulletDebugDraw::CreateCapsule()
	{
		MeshModel*	meshModel = new MeshModel();
		meshModel->CreateCapsule();
		meshModels.emplace_back(meshModel);
	}

	void BulletDebugDraw::Setup()
	{
		auto hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateVertexShader(btdbg_vsh, sizeof(btdbg_vsh), nullptr, &vertexShader);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "���_�V�F�[�_�̐����Ɏ��s", "BulletDebugDraw::Setup()", MB_OK);
			return;
		}
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreatePixelShader(btdbg_psh, sizeof(btdbg_psh), nullptr, &pixelShader);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�s�N�Z���V�F�[�_�̐����Ɏ��s", "BulletDebugDraw::Setup()", MB_OK);
			return;
		}

		D3D11_INPUT_ELEMENT_DESC	layoutDesc[] = {
			{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
			{ "COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		UINT elemNum = ARRAYSIZE(layoutDesc);
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateInputLayout(layoutDesc, elemNum, btdbg_vsh, sizeof(btdbg_vsh), &inputLayout);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�C���v�b�g���C�A�E�g�̍쐬�Ɏ��s", "BulletDebugDraw::Setup()", MB_OK);
			return;
		}

		//�X�e�[�g�̐ݒ�
		//���X�^���C�Y�X�e�[�g
		D3D11_RASTERIZER_DESC	rsDesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
		rsDesc.AntialiasedLineEnable = true;
		rsDesc.MultisampleEnable = false;
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateRasterizerState(&rsDesc, &rasterizeState);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "���X�^���C�X�X�e�[�g�̍쐬�Ɏ��s", "BulletDebugDraw::Setup()", MB_OK);
			return;
		}

		//�u�����h�X�e�[�g�̍쐬
		D3D11_BLEND_DESC	blendDesc = {};
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC1_ALPHA;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBlendState(&blendDesc, &blendState);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�u�����h�X�e�[�g�̍쐬�Ɏ��s", "BulletDebugDraw::Setup()", MB_OK);
			return;
		}

		//�f�v�X�X�e���V���X�e�[�g�̍쐬
		D3D11_DEPTH_STENCIL_DESC	depDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
		depDesc.DepthEnable = true;
		depDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateDepthStencilState(&depDesc, &depthStencilStateOn);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�f�v�X�X�e���V���̍쐬�Ɏ��s", "BulletDebugDraw::Setup()", MB_OK);
			return;
		}
		depDesc.DepthEnable = false;
		depDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateDepthStencilState(&depDesc, &depthStencilStateOff);

		//�萔�o�b�t�@�̍쐬
		ConstantBuffer	cBuffer;
		D3D11_BUFFER_DESC	bufferDesc;
		memset(&bufferDesc, 0, sizeof(bufferDesc));
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.ByteWidth = sizeof(ConstantBuffer);
		bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bufferDesc.CPUAccessFlags = 0;
		D3D11_SUBRESOURCE_DATA	subResData;
		memset(&subResData, 0, sizeof(subResData));
		subResData.pSysMem = &cBuffer;
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&bufferDesc, &subResData, &constantBuf);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�萔�o�b�t�@�̍쐬�Ɏ��s", "BulletDebugDraw::Setup()", MB_OK);
			return;
		}
		line.clear();
	}

	void BulletDebugDraw::setDebugMode(int drawMode)
	{
		mode = static_cast<DrawMode>(drawMode);
	}

	int BulletDebugDraw::getDebugMode() const
	{
		return static_cast<int>(mode);
	}

	void BulletDebugDraw::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & color)
	{
		drawLine(from, to, color, color);
	}

	void BulletDebugDraw::drawLine(const btVector3 & from, const btVector3 & to, const btVector3 & fromColor, const btVector3 & toColor)
	{
		if (line.size() >= MaxLine) { return; }
		line.push_back(Line(from, to, fromColor, toColor));
	}

	void BulletDebugDraw::flushLines()
	{
		if (line.size() == 0) { return; }

		struct VertexData
		{
			DirectX::XMFLOAT3 pos;
			DirectX::XMFLOAT3 color;
		};

		ComPtr<ID3D11Buffer>	vertexBuf;
		ComPtr<ID3D11Buffer>	indexBuf;

		D3D11_BUFFER_DESC	bufDesc;
		memset(&bufDesc, 0, sizeof(bufDesc));
		bufDesc.Usage = D3D11_USAGE_DEFAULT;
		bufDesc.ByteWidth = sizeof(Line) * line.size();
		bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bufDesc.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA	subResDesc;
		memset(&subResDesc, 0, sizeof(subResDesc));
		subResDesc.pSysMem = line.data();
		auto hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&bufDesc, &subResDesc, &vertexBuf);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s", "BulletDebugDraw::flushLines()", MB_OK);
			return;
		}

		//�萔�o�b�t�@
		ConstantBuffer	cbuffer;
		DirectX::XMStoreFloat4x4(&cbuffer.viewMatrix, renderScene->viewMatrix);
		DirectX::XMStoreFloat4x4(&cbuffer.projMatrix, renderScene->projMatrix);
		DirectX::XMStoreFloat4x4(&cbuffer.world, DirectX::XMMatrixIdentity());
		cbuffer.diffuse = DirectX::XMFLOAT4(0.5f, 0.5f, 0.5f, 0.25f);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf.Get(), 0, nullptr, &cbuffer, 0, 0);

		//���̓��C�A�E�g
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetInputLayout(inputLayout.Get());

		//���_�o�b�t�@
		UINT stride = sizeof(VertexData);
		UINT offset = 0;
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuf, &stride, &offset);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		//�V�F�[�_
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(0, 1, &constantBuf);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(0, 1, &constantBuf);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetShader(vertexShader.Get(), nullptr, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetShader(nullptr, nullptr, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShader(pixelShader.Get(), nullptr, 0);

		//�X�e�[�g
		FLOAT	blendColor[4] = { 0,0,0,0 };
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().RSSetState(rasterizeState.Get());
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().OMSetBlendState(blendState.Get(), blendColor, 0xffffffff);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().OMSetDepthStencilState(depthStencilStateOff.Get(), 0);

		//�|���S���`��
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().Draw(line.size() * 2, 0);

		cbuffer.diffuse = DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf.Get(), 0, nullptr, &cbuffer, 0, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().OMSetDepthStencilState(depthStencilStateOn.Get(), 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().Draw(line.size() * 2, 0);

		line.clear();
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetShader(nullptr, nullptr, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetShader(nullptr, nullptr, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShader(nullptr, nullptr, 0);
	}


	void BulletDebugDraw::SetProjMatrix(const DirectX::XMMATRIX& projMatrix)
	{
		renderScene->projMatrix = projMatrix;
	}

	void BulletDebugDraw::SetViewMatrix(const DirectX::XMMATRIX& viewMatrix)
	{
		renderScene->viewMatrix = viewMatrix;
	}

	void BulletDebugDraw::drawContactPoint(const btVector3 & point, const btVector3 & normal, btScalar distance, int lifeTime, const btVector3 & color)
	{
		drawLine(point, point + normal, normal * distance, color);
		btVector3 ncolor(0, 0, 0);
		drawLine(point, point + normal, normal * 0.01f, ncolor);
	}

	void BulletDebugDraw::reportErrorWarning(const char * warningString)
	{
	}

	void BulletDebugDraw::draw3dText(const btVector3 & location, const char * textString)
	{
	}


	//���b�V�����f��
	MeshModel::MeshModel()
	{
		this->LoadMeshData();
	}

	MeshModel::~MeshModel()
	{
	}

	bool MeshModel::Create(const MeshModel::MeshData& meshInfo)
	{
		ComPtr<ID3D11InputLayout>	inputLayout;
		ComPtr<ID3D11RasterizerState>	rs;
		ComPtr<ID3D11BlendState>		bd;
		ComPtr<ID3D11DepthStencilState>	ds;
		ComPtr<ID3D11SamplerState>		sm;
		ComPtr<ID3D11Buffer>			vBuf;
		ComPtr<ID3D11Buffer>			iBuf;
		ComPtr<ID3D11Buffer>			cBuf[2];
		
		//���̓��C�A�E�g�̍쐬
		auto hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateInputLayout(meshInfo.layout, meshInfo.numLayout, meshInfo.inVS, meshInfo.sizeVS, &inputLayout);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "���̓��C�A�E�g�̍쐬�Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
			return false;
		}

		//�X�e�[�g�ݒ�
		D3D11_RASTERIZER_DESC	rsDesc = CD3D11_RASTERIZER_DESC(CD3D11_DEFAULT());
		D3D11_BLEND_DESC	bdDesc = CD3D11_BLEND_DESC(CD3D11_DEFAULT());
		D3D11_DEPTH_STENCIL_DESC depDesc = CD3D11_DEPTH_STENCIL_DESC(CD3D11_DEFAULT());
		depDesc.DepthEnable = true;
		depDesc.StencilWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;

		//���X�^���C�Y�X�e�[�g�̍쐬
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateRasterizerState(&rsDesc, &rs);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "���X�^���C�Y�̍쐬�Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
			return false;
		}

		//�u�����h�X�e�[�g�̍쐬
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBlendState(&bdDesc, &bd);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�u�����h�X�e�[�g�̍쐬�Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
			return false;
		}

		//�f�v�X�X�e���V���X�e�[�g�̍쐬
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateDepthStencilState(&depDesc, &ds);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�f�v�X�X�e���V���X�e�[�g�̍쐬�Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
			return false;
		}

		//�T���v���[�̍쐬
		D3D11_SAMPLER_DESC	sampDesc = { };
		sampDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		sampDesc.MaxAnisotropy = 0;
		sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		sampDesc.MinLOD = 0;
		sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateSamplerState(&sampDesc, &sm);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�T���v���[�̍쐬�Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
			return false;
		}

		{
			//���_�o�b�t�@
			D3D11_BUFFER_DESC	bufDesc = { 0 };
			bufDesc.Usage = D3D11_USAGE_DEFAULT;
			bufDesc.ByteWidth = meshInfo.sizeVertex;
			bufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
			bufDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA	subResData;
			subResData.pSysMem = meshInfo.pVertex;
			hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&bufDesc, &subResData, &vBuf);
			if (FAILED(hr))
			{
				MessageBoxA(nullptr, "���_�o�b�t�@�̍쐬�Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
				return false;
			}
		}
		{
			//�C���f�b�N�X�o�b�t�@�̍쐬
			D3D11_BUFFER_DESC	indexDesc = { 0 };
			indexDesc.Usage = D3D11_USAGE_DEFAULT;
			indexDesc.ByteWidth = meshInfo.sizeIndex;
			indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
			indexDesc.CPUAccessFlags = 0;
			D3D11_SUBRESOURCE_DATA	indexSubData = { 0 };
			indexSubData.pSysMem = meshInfo.pIndex;
			hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&indexDesc, &indexSubData, &iBuf);
			if (FAILED(hr))
			{
				MessageBoxA(nullptr, "Index�o�b�t�@�̍쐬�Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
				return false;
			}
		}

		//���ʒ萔�o�b�t�@
		cBuf[0] = meshInfo.cBuffer;
		MeshCBuffer meshCBuf;
		{
			meshCBuf.world = meshInfo.transform;
			meshCBuf.diffuse = meshInfo.diffuse;
			meshCBuf.texture = meshInfo.texSRV.Get() != nullptr;

			D3D11_BUFFER_DESC	meshDesc = { 0 };
			meshDesc.Usage = D3D11_USAGE_DEFAULT;
			meshDesc.ByteWidth = sizeof(meshCBuf);
			meshDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
			meshDesc.CPUAccessFlags = 0;

			D3D11_SUBRESOURCE_DATA	meshSubData = { 0 };
			meshSubData.pSysMem = &meshCBuf;
			hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&meshDesc, &meshSubData, &cBuf[1]);
			if (FAILED(hr))
			{
				MessageBoxA(nullptr, "���b�V���̒萔�o�b�t�@�̍쐬�Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
				return false;
			}
		}

		//�R�s�[
		this->meshBuf = meshCBuf;
		this->stride = meshInfo.stride;
		this->numIndex = meshInfo.numIndex;

		this->texSRV = meshInfo.texSRV;
		this->vertexBuf = vertexBuf;
		this->indexBuf = indexBuf;
		this->cBuffer[0] = cBuf[0];
		this->cBuffer[1] = cBuf[1];
		this->layout = inputLayout;
		this->vertexShader = meshInfo.vertexShader;
		this->pixelShader = meshInfo.pixelShader;
		this->rsState = rs;
		this->blendState = bd;
		this->depthState = ds;
		this->samplerState = sm;

		return true;
	}

	void MeshModel::Draw(const DirectX::XMMATRIX & transform)
	{
		//�萔�o�b�t�@�̍X�V
		MeshCBuffer	meshCBuf = this->meshBuf;
		meshCBuf.world = DirectX::XMMatrixTranspose(transform);
		meshCBuf.diffuse = meshCBuf.diffuse;
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(this->cBuffer[1].Get(), 0, nullptr, &meshCBuf, 0, 0);
		
		//���̓��C�A�E�g
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetInputLayout(this->layout.Get());

		//���_�o�b�t�@
		UINT offset = 0;
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuf, &this->stride, &offset);

		//�v���~�e�B�u�`��
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		//�C���f�b�N�X
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetIndexBuffer(this->indexBuf.Get(), DXGI_FORMAT_R32_UINT, 0);

		//�V�F�[�_
		ID3D11Buffer*	cb[2] = { this->cBuffer[0].Get(),this->cBuffer[1].Get() };
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(0, 2, cb);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetShader(this->vertexShader.Get(), nullptr, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetShader(nullptr, nullptr, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(0, 2, cb);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShader(this->pixelShader.Get(), nullptr, 0);

		//�V�F�[�_���\�[�X�r���[
		UINT	srvSlot = 0;
		ID3D11ShaderResourceView* srv[1] = { this->texSRV.Get() };
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetShaderResources(srvSlot, 1, srv);

		//�T���v���[
		UINT	samSlot = 0;
		ID3D11SamplerState*	smp[1] = { this->samplerState.Get() };
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetSamplers(samSlot, 1, smp);

		//�X�e�[�g
		FLOAT	state[4] = { 0,0,0,0 };
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().RSSetState(this->rsState.Get());
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().OMSetBlendState(this->blendState.Get(), state, 0xffffffff);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().OMSetDepthStencilState(this->depthState.Get(), 0);

		//�|���S���`��
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().DrawIndexed(this->numIndex, 0, 0);
	}

	bool MeshModel::LoadMeshData()
	{
		meshConstant.vsCode.Load("./data/shaderData/mesh/mesh_vsh.cso");
		meshConstant.psCode.Load("./data/shaderData/mesh/mesh_psh.cso");

		auto hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreateVertexShader(meshConstant.vsCode.Get(), meshConstant.vsCode.Size(), nullptr, &meshConstant.meshVS);
		hr = Engine<DXDevice>::GetDevice().GetDevice3D().CreatePixelShader(meshConstant.psCode.Get(), meshConstant.psCode.Size(), nullptr, &meshConstant.meshPS);
		if (FAILED(hr))
		{
			MessageBoxA(nullptr, "�V�F�[�_�̓ǂݍ��݂Ɏ��s", "BulletDebugDraw::MeshModel::Create()", MB_OK);
			return false;
		}
		return true;
	}

	void MeshModel::CreateSphere()
	{
		MeshModel::MeshData meshData = {
			meshConstant.constantBuf.Get(),
			nullptr,
			meshConstant.meshVS,meshConstant.meshPS,meshConstant.vsCode.Get(),(UINT)meshConstant.vsCode.Size(),
			MeshSphere::layout_num,MeshSphere::mesh_layout,
			MeshSphere::mesh_vertex,sizeof(MeshSphere::mesh_vertex),
			MeshSphere::vertex_stride,
			MeshSphere::mesh_index,sizeof(MeshSphere::mesh_index),
			MeshSphere::index_num,
			Math::Vector4(MeshSphere::diffuse[0],MeshSphere::diffuse[1],MeshSphere::diffuse[2],MeshSphere::diffuse[3]),
			DirectX::XMMatrixIdentity(),
		};
		auto hr = this->Create(meshData);
	}

	void MeshModel::CreateBox()
	{
		MeshModel::MeshData	meshData = {
			meshConstant.constantBuf.Get(),
			nullptr,
			meshConstant.meshVS,meshConstant.meshPS,meshConstant.vsCode.Get(),(UINT)meshConstant.vsCode.Size(),
			MeshBox::layout_num,MeshBox::mesh_layout,
			MeshBox::mesh_vertex,sizeof(MeshBox::mesh_vertex),
			MeshBox::vertex_stride,
			MeshBox::mesh_index,sizeof(MeshBox::mesh_index),
			MeshBox::index_num,
			Math::Vector4(MeshBox::diffuse[0],MeshBox::diffuse[1],MeshBox::diffuse[2],MeshBox::diffuse[3]),
			DirectX::XMMatrixIdentity(),
		};
		auto hr = this->Create(meshData);
	}

	void MeshModel::CreateCylinder()
	{
		MeshModel::MeshData meshData = {
			meshConstant.constantBuf.Get(),
			nullptr,
			meshConstant.meshVS,meshConstant.meshPS,meshConstant.vsCode.Get(),(UINT)meshConstant.vsCode.Size(),
			MeshCylinder::layout_num,MeshCylinder::mesh_layout,
			MeshCylinder::mesh_vertex,sizeof(MeshCylinder::mesh_vertex),
			MeshCylinder::vertex_stride,
			MeshCylinder::mesh_index,sizeof(MeshCylinder::mesh_index),
			MeshCylinder::index_num,
			Math::Vector4(MeshCylinder::diffuse[0],MeshCylinder::diffuse[1],MeshCylinder::diffuse[2],MeshCylinder::diffuse[3]),
			DirectX::XMMatrixIdentity(),
		};
		auto hr = this->Create(meshData);
	}

	void MeshModel::CreateCapsule()
	{
		MeshModel::MeshData meshData = {
			meshConstant.constantBuf.Get(),
			nullptr,
			meshConstant.meshVS,meshConstant.meshPS,meshConstant.vsCode.Get(),(UINT)meshConstant.vsCode.Size(),
			MeshCapsule::layout_num,MeshCapsule::mesh_layout,
			MeshCapsule::mesh_vertex,sizeof(MeshCapsule::mesh_vertex),
			MeshCapsule::vertex_stride,
			MeshCapsule::mesh_index,sizeof(MeshCapsule::mesh_index),
			MeshCapsule::index_num,
			Math::Vector4(MeshCapsule::diffuse[0],MeshCapsule::diffuse[1],MeshCapsule::diffuse[2],MeshCapsule::diffuse[3]),
			DirectX::XMMatrixIdentity(),
		};
		auto hr = this->Create(meshData);
	}

	void MeshModel::CreateCone()
	{
		MeshModel::MeshData meshData = {
			meshConstant.constantBuf.Get(),
			nullptr,
			meshConstant.meshVS,meshConstant.meshPS,meshConstant.vsCode.Get(),(UINT)meshConstant.vsCode.Size(),
			MeshCone::layout_num,MeshCone::mesh_layout,
			MeshCone::mesh_vertex,sizeof(MeshCone::mesh_vertex),
			MeshCone::vertex_stride,
			MeshCone::mesh_index,sizeof(MeshCone::mesh_index),
			MeshCone::index_num,
			Math::Vector4(MeshCone::diffuse[0],MeshCone::diffuse[1],MeshCone::diffuse[2],MeshCone::diffuse[3]),
			DirectX::XMMatrixIdentity(),
		};
		auto hr = this->Create(meshData);
	}

	/*void MeshModel::SetCameraMatrix(Camera& camera)
	{
		meshConstant.constantBuf = camera.GetConstantBuf();
	}
*/
}