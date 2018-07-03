#include "polygon.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/DXEngine/DXEngine.h"


//!@brief	コンストラクタ
Model::Model()
	: pos(Math::Vector3(0,0,0))
	, angle(Math::Vector3(0,0,0))
	, scale(Math::Vector3(1,1,1))
	, constantBuf(nullptr)
{
	//this->fbxModel = new FbxModel();
	//this->fbxModel->LoadFile("./data/image/ball.fbx");

	//図形のデータの作成
	//this->primitiveData = new PrimitiveData(fbxModel->GetVertexDatas());
	
	//頂点データをもらってくる
	//FBXから頂点データの座標をもらう
	//primitiveData->SetVertexDatas(fbxModel->GetVertexData());

	//primitiveData->SetVertexBuffer(fbxModel->GetVertexDatas());
	//primitiveData->SetIndexBuffer(fbxModel->GetVertexPolygonVertices(), fbxModel->GetVertexCount());


	std::vector<Vertex>	vertices;
	vertices.push_back(Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f));
	vertices.push_back(Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f));
	vertices.push_back(Vertex(-0.5f, -0.5f, 0.5f, 1.0f, 1.0f));
	vertices.push_back(Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f));

	vertexShader = new VertexShader();
	pixelShader = new PixelShader();
	primitive = new Primitive();

	std::vector<WORD>	indices;
	indices.push_back(0);
	indices.push_back(1);
	indices.push_back(2);
	indices.push_back(0);
	indices.push_back(3);
	indices.push_back(1);

	primitive->AddVertexDatas(vertices);
	primitive->AddIndexDatas(indices);

	primitive->CreateVertexBuffer();
	primitive->CreateIndexBuffer();

	CreateInputLayout();
	CreateConstantBuffer();
}

//!@brief	デストラクタ
Model::~Model()
{
	//Delete
	Utility::SafeDelete(vertexShader);
	Utility::SafeDelete(pixelShader);
	Utility::SafeDelete(primitive);
	//Release
	Utility::SafeRelease(constantBuf);
}

void	Model::UpDate()
{
	vertexShader->Set();
	pixelShader->Set();
}

void	Model::Render()
{
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().HSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().DSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(0, 1, &constantBuf);
	primitive->Attach();
}

//!@brief	インプットレイアウトの作成
void	Model::CreateInputLayout()
{
	//入力項目
	D3D11_INPUT_ELEMENT_DESC inputLayout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",    0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	vertexShader->Create("./data/shaderData/VertexShader", inputLayout, 2);
	pixelShader->Create("./data/shaderData/PixelShader");
}
//!@brief	定数バッファの作成
void	Model::CreateConstantBuffer()
{
	D3D11_BUFFER_DESC	constantBufDesc;
	memset(&constantBufDesc, 0, sizeof(constantBufDesc));
	constantBufDesc.ByteWidth = sizeof(ConstantBuffer);
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&constantBufDesc, nullptr, &constantBuf);
}

//!@brief	マトリックスの設定
void	Model::SetMatrix(Camera* camera)
{
	DirectX::XMMATRIX	matT = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	DirectX::XMMATRIX	matR = DirectX::XMMatrixRotationRollPitchYaw(
		DirectX::XMConvertToRadians(angle.y),
		DirectX::XMConvertToRadians(angle.x), 
		DirectX::XMConvertToRadians(angle.z));
	DirectX::XMMATRIX	matS = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	
	DirectX::XMMATRIX worldMatrix = matS * matR * matT;
	
	//マトリックスの設定
	ConstantBuffer cb;
	DirectX::XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(worldMatrix));
	DirectX::XMStoreFloat4x4(&cb.view, camera->GetView());
	DirectX::XMStoreFloat4x4(&cb.projection, camera->GetProj());
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &cb, 0, 0);
}