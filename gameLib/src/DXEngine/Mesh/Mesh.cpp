#include "Mesh.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"

//-------------------------------------------------------
//!@brief		コンストラクタ
//-------------------------------------------------------
Mesh::Mesh()
	: vertexBuf(nullptr)
	, indexBuf(nullptr)
	, rasterizerState(nullptr)
{
	position = Math::Vector3(0.0f, 0.0f, 0.0f);
	angle = Math::Vector3(0.0f, 0.0f, 0.0f);
	scale = Math::Vector3(1.0f, 1.0f, 1.0f);

	material = new Material(Math::Vector4(1,1,1,1));
	
	SetCullingMode(D3D11_CULL_NONE);
}

//-------------------------------------------------------
//!@brief		デストラクタ
//-------------------------------------------------------
Mesh::~Mesh()
{
	Utility::SafeRelease(vertexBuf);
	Utility::SafeRelease(indexBuf);
	Utility::SafeRelease(rasterizerState);
}

//-------------------------------------------------------------------------------
//!@brief		平面の作成
//!@param[in]	ポリゴンの大きさ
//!@param[in]	ポリゴンのオフセット位置
//!@param[in]	頂点・インデックスの初期化フラグ
//!@param[in]	左方向の向き
//!@param[in]	上方向の向き
//!@param[in]	法線の向き
//--------------------------------------------------------------------------------
void	Mesh::CreatePlane(
	Math::Vector2 size,
	Math::Vector3 offset,
	bool		 shoudClear,
	Math::Vector3 leftDir,
	Math::Vector3 upDir,
	Math::Vector3 forwardDir
)
{
	if (shoudClear)
	{
		vertices.clear();
		indices.clear();
	}

	leftDir = DirectX::XMVector3Normalize(leftDir);
	upDir = DirectX::XMVector3Normalize(upDir);
	forwardDir = DirectX::XMVector3Normalize(forwardDir);

	vertices.push_back(Math::VertexData(leftDir * -size.x + upDir * size.y + offset, -forwardDir, Math::Vector2(0.0f, 0.0f)));
	vertices.push_back(Math::VertexData(leftDir * size.x + upDir * size.y + offset, -forwardDir, Math::Vector2(1.0f, 0.0f)));
	vertices.push_back(Math::VertexData(leftDir * -size.x + upDir * -size.y + offset, -forwardDir, Math::Vector2(0.0f, 1.0f)));
	vertices.push_back(Math::VertexData(leftDir * size.x + upDir * -size.y + offset, -forwardDir, Math::Vector2(1.0f, 1.0f)));

	size_t indexOffset = vertices.size() - 4;
	indices.push_back(indexOffset + 0);
	indices.push_back(indexOffset + 1);
	indices.push_back(indexOffset + 2);
	indices.push_back(indexOffset + 3);
	indices.push_back(indexOffset + 2);
	indices.push_back(indexOffset + 1);

	Apply();
}


//-----------------------------------------------------------------------------
//!@brief	四面体の作成
//!@param[in]	頂点・インデックスの初期化フラグ
//-----------------------------------------------------------------------------
void	Mesh::CreateCube(bool	shoudClear)
{
	if (shoudClear)
	{
		vertices.clear();
		indices.clear();
	}

	CreatePlane(Math::Vector2(0.5f, 0.5f), Math::Vector3(0.0f, 0.0f, -0.5f), false, Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 1.0f));	// front
	CreatePlane(Math::Vector2(0.5f, 0.5f), Math::Vector3(0.0f, 0.0f, 0.5f), false, Math::Vector3(-1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f));	// back
	CreatePlane(Math::Vector2(0.5f, 0.5f), Math::Vector3(0.5f, 0.0f, 0.0f), false, Math::Vector3(0.0f, 0.0f, 1.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(-1.0f, 0.0f, 0.0f));	// left
	CreatePlane(Math::Vector2(0.5f, 0.5f), Math::Vector3(-0.5f, 0.0f, 0.0f), false, Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(0.0f, 1.0f, 0.0f), Math::Vector3(1.0f, 0.0f, 0.0f));	// right
	CreatePlane(Math::Vector2(0.5f, 0.5f), Math::Vector3(0.0f, 0.5f, 0.0f), false, Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, 1.0f), Math::Vector3(0.0f, -1.0f, 0.0f));	// up
	CreatePlane(Math::Vector2(0.5f, 0.5f), Math::Vector3(0.0f, -0.5f, 0.0f), false, Math::Vector3(1.0f, 0.0f, 0.0f), Math::Vector3(0.0f, 0.0f, -1.0f), Math::Vector3(0.0f, 1.0f, 0.0f));	// down
}

//!@brief	ポイントの作成
//!@param[in]	pos	ポイント位置
//!@param[in]	offset	オフセット
//!@param[in]	forwardDir	方向
//!@param[in]	shoudClear	頂点・インデックスの初期化フラグ
void	Mesh::CreatePoint(
	const Math::Vector3& pos,
	const Math::Vector3& offset,
	const Math::Vector3& forwardDir,
	bool	shoudClear)
{
	if (shoudClear)
	{
		vertices.clear();
		indices.clear();
	}
	

	vertices.push_back(Math::VertexData(
		pos + offset,
		-forwardDir,
		Math::Vector2(0.0f, 1.0f)));
	size_t indexOffset = vertices.size() - 1;
	indices.push_back(indexOffset + 0);
	
	Apply();
}

//--------------------------------------------------------------------------------
//!@brief	マテリアルの取得
//!@return マテリアル
//--------------------------------------------------------------------------------
Material&	Mesh::GetMaterial()
{
	return *material;
}

//---------------------------------------------------------------------------------
//!@brief	位置の設定
//!@param[in]	pos	位置
//---------------------------------------------------------------------------------
void	Mesh::SetPos(const Math::Vector3& pos)
{
	this->position = pos;
}

//---------------------------------------------------------------------------------
//!@brief	角度の設定
//!@param[in]	angle	角度
//---------------------------------------------------------------------------------
void	Mesh::SetAngle(const Math::Vector3& angle)
{
	this->angle = angle;
}

//---------------------------------------------------------------------------------
//!@brief	スケールの設定
//!@param[in]	scale	スケール
//---------------------------------------------------------------------------------
void	Mesh::SetScale(const Math::Vector3& scale)
{
	this->scale = scale;
}

//---------------------------------------------------------------------------------
//!@brief	カリングモードの設定
//!@param[in]	カリングの設定
//---------------------------------------------------------------------------------
void	Mesh::SetCullingMode(D3D11_CULL_MODE cullingMode)
{
	D3D11_RASTERIZER_DESC	rasterizerDesc;
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = cullingMode;
	if (rasterizerState != nullptr)
	{
		rasterizerState->Release();
	}
	Engine<DXDevice>::GetDevice().GetDevice3D().CreateRasterizerState(&rasterizerDesc, &rasterizerState);
}

//----------------------------------------------------------------------------------
//!@brief	変更点を適応させる
//----------------------------------------------------------------------------------
void	Mesh::Apply()
{
	if (vertexBuf != nullptr)
	{
		vertexBuf->Release();
	}
	if (vertices.size() > 0)
	{
		D3D11_BUFFER_DESC	vertexBufDesc;
		SecureZeroMemory(&vertexBufDesc, sizeof(vertexBufDesc));
		vertexBufDesc.ByteWidth = sizeof(Math::VertexData) * vertices.size();
		vertexBufDesc.Usage = D3D11_USAGE_DEFAULT;
		vertexBufDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA vertexSubresourceData;
		SecureZeroMemory(&vertexSubresourceData, sizeof(vertexSubresourceData));
		vertexSubresourceData.pSysMem = vertices.data();

		Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&vertexBufDesc, &vertexSubresourceData, &vertexBuf);
	}

	if (indexBuf != nullptr)
	{
		indexBuf->Release();
	}
	if (indices.size() > 0)
	{
		D3D11_BUFFER_DESC indexBufferDesc;
		SecureZeroMemory(&indexBufferDesc, sizeof(indexBufferDesc));
		indexBufferDesc.ByteWidth = sizeof(int) * indices.size();
		indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
		indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

		D3D11_SUBRESOURCE_DATA indexSubresourceData;
		SecureZeroMemory(&indexSubresourceData, sizeof(indexSubresourceData));
		indexSubresourceData.pSysMem = indices.data();

		Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(&indexBufferDesc, &indexSubresourceData, &indexBuf);
	}
}

//-------------------------------------------------------------------------------
//!@brief	位置・回転・スケールの設定
//!@param[in]	pos_		位置
//!@param[in]	rotation_	回転
//!@param[in]	scale_		スケール
//-------------------------------------------------------------------------------
void	Mesh::SetParams(const Math::Vector3& pos_, const Math::Vector3& rotation_, const Math::Vector3& scale_)
{
	position = pos_;
	angle = rotation_;
	scale = scale_;
}

//--------------------------------------------------------------------------------
//!@brief	描画する
//--------------------------------------------------------------------------------
void	Mesh::Draw()
{
	if (vertexBuf == nullptr) { return; }

	constantBuf.worldMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angle.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angle.y)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angle.z)) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z)
	);
	
	material->UpDate();
	material->Render3D();

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().RSSetState(rasterizerState);

	UINT	stride = sizeof(Math::VertexData);
	UINT	offset = 0;

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuf, &stride, &offset);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	if (indexBuf == nullptr)
	{
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().Draw(vertices.size(), 0);
	}
	else
	{
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetIndexBuffer(indexBuf, DXGI_FORMAT_R32_UINT, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().DrawIndexed(indices.size(), 0, 0);
	}
}


//!@brief	ポイントを描画する
void	Mesh::DrawPoint()
{
	if (vertexBuf == nullptr) { return; }

	constantBuf.worldMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixScaling(scale.x, scale.y, scale.z) *
		DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angle.x)) *
		DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angle.y)) *
		DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angle.z)) *
		DirectX::XMMatrixTranslation(position.x, position.y, position.z)
	);

	material->UpDate();
	material->Render3D();

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().RSSetState(rasterizerState);
	UINT stride = sizeof(Math::VertexData);
	UINT offset = 0;

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetVertexBuffers(0, 1, &vertexBuf, &stride, &offset);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
	if (indexBuf == nullptr)
	{
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().Draw(vertices.size(), 0);
	}
	else
	{
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().IASetIndexBuffer(indexBuf, DXGI_FORMAT_R32_UINT, 0);
		Engine<DXDevice>::GetDevice().GetDeviceContext3D().DrawIndexed(indices.size(), 0, 0);
	}
}