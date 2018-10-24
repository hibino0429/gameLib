#include "Model.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/DXEngine/DXEngine/DXEngine.h"

//!@brief	コンストラクタ
Model::Model()
	: pos(Math::Vector3(0,0,0))
	, angle(Math::Vector3(0,0,0))
	, scale(Math::Vector3(1,1,1))
	, constantBuf(nullptr)
{
	fbxModel = new FbxModel("./data/image/ball.fbx");
	animationData = new AnimationData();
	vertexShader = new VertexShader();
	pixelShader = new PixelShader();
	primitive = new Primitive();

	primitive->AddVertexDatas(fbxModel->GetVertexData());
	primitive->AddIndexDatas(fbxModel->GetVertexPolygonVertices());

	primitive->CreateVertexBuffer();
	primitive->CreateIndexBuffer();

	CreateInputLayout();
	CreateConstantBuffer();
}

//!@brief	コンストラクタ
//!@param[in]	filePath	ファイルパス
Model::Model(const std::string& filePath)
	: pos(Math::Vector3(0,0,0))
	, angle(Math::Vector3(0,0,0))
	, scale(Math::Vector3(1,1,1))
	, constantBuf(nullptr)
{
	fbxModel = new FbxModel(filePath);
	animationData = new AnimationData();
	vertexShader = new VertexShader();
	pixelShader = new PixelShader();
	primitive = new Primitive();
	//fbxからアニメーション番号を受け取る
	animationData->SetAnimationNumber(fbxModel->GetNowAnimationNumber());
	animationData->SetAnimationName(fbxModel->GetNowAnimationName());
	//プリミティブの生成と追加
	primitive->AddVertexDatas(fbxModel->GetVertexData());
	primitive->AddIndexDatas(fbxModel->GetVertexPolygonVertices());
	primitive->CreateVertexBuffer();
	primitive->CreateIndexBuffer();
	//インプットレイアウトと定数バッファ
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
	Utility::SafeDelete(fbxModel);
	Utility::SafeDelete(animationData);
	//Release
	Utility::SafeRelease(constantBuf);
}

//!@brief	位置の設定
void	Model::SetPos(const Math::Vector3& pos)
{
	this->pos = pos;
}
//!@brief	スケールの設定
void	Model::SetScale(const Math::Vector3& scale)
{
	this->scale = scale;
}
void	Model::UpDate()
{
	vertexShader->Set();
	pixelShader->Set();
	//Fbxのアニメーション行列の更新
	if (fbxModel->IsAnimation())
	{
		fbxModel->AnimationMatrix();
	}
	primitive->UpDateVertexDatas(fbxModel->GetVertexData());
	//頂点データとインデックスデータの再設定
	primitive->CreateVertexBuffer();
	primitive->CreateIndexBuffer();
	//アニメーション番号の設定
	animationData->SetAnimationNumber(fbxModel->GetNowAnimationNumber());
	animationData->SetAnimationName(fbxModel->GetNowAnimationName());
	//animationData->Output();
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
	constantBufDesc.ByteWidth	= sizeof(ConstantBuffer);
	constantBufDesc.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.Usage		= D3D11_USAGE_DEFAULT;

	Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&constantBufDesc, nullptr, &constantBuf);
}

//!@brief	アニメーションの更新
//!@param[in]	upDateAnimationNumber	更新するアニメーション番号
void	Model::UpDateAnimation(const int& upDateAnimationNumber)
{
	fbxModel->SetAnimationNumber(upDateAnimationNumber);
	fbxModel->CreateAnimation();
	fbxModel->CreateAnimationTime();
}

//!@brief	マトリックスの設定
//void	Model::SetMatrix(Camera* camera)
//{
//	DirectX::XMMATRIX	matT = DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
//	DirectX::XMMATRIX	matR = DirectX::XMMatrixRotationRollPitchYaw(
//		DirectX::XMConvertToRadians(angle.y),
//		DirectX::XMConvertToRadians(angle.x), 
//		DirectX::XMConvertToRadians(angle.z));
//	DirectX::XMMATRIX	matS = DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
//	
//	DirectX::XMMATRIX worldMatrix = matS * matR * matT;
//	
//	//マトリックスの設定
//	ConstantBuffer cb;
//	DirectX::XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(worldMatrix));
//	DirectX::XMStoreFloat4x4(&cb.view, camera->GetView());
//	DirectX::XMStoreFloat4x4(&cb.projection, camera->GetProj());
//	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &cb, 0, 0);
//}