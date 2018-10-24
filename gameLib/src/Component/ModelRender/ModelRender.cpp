#include "ModelRender.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/Component/Material/Material.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"


ModelRender::ModelRender(FbxModel * model)
{
	modelData.fbxModel = model;
	modelData.animationData = new AnimationData();
	modelData.primitive = new Primitive();
	constantBuf = new ConstantBuffer();

	//fbxからアニメーション番号を受け取る
	modelData.animationData->SetAnimationNumber(modelData.fbxModel->GetNowAnimationNumber());
	modelData.animationData->SetAnimationName(modelData.fbxModel->GetNowAnimationName());
	//プリミティブの生成と追加
	modelData.primitive->AddVertexDatas(modelData.fbxModel->GetVertexData());
	modelData.primitive->AddIndexDatas(modelData.fbxModel->GetVertexPolygonVertices());
	modelData.primitive->CreateVertexBuffer();
	modelData.primitive->CreateIndexBuffer();
}

ModelRender::~ModelRender()
{
	//Delete
	Utility::SafeDelete(modelData.primitive);
	Utility::SafeDelete(modelData.animationData);
	Utility::SafeDelete(constantBuf);
}

void ModelRender::UpDateAnimation(const int & upDateAnimationNumber)
{
	modelData.fbxModel->SetAnimationNumber(upDateAnimationNumber);
	modelData.fbxModel->CreateAnimation();
	modelData.fbxModel->CreateAnimationTime();
}

void ModelRender::UpDateMatrix(const Camera& camera,const DirectionalLight& light)
{
	if (GetEntity()->HasComponent<Transform>())
	{
		Transform	transform = GetEntity()->GetComponent<Transform>();

		DirectX::XMMATRIX	matT = Math::TransformMatrix(transform.position);
		DirectX::XMMATRIX	matR = Math::RotationMatrix(transform.rotation);
		DirectX::XMMATRIX	matS = Math::ScaleMatrix(transform.scale);

		transMat.worldMat = matS * matR * matT;
		transMat.viewMat = camera.GetViewMatrix();
		transMat.projMat = camera.GetProjectionMatrix();
	}

	CBuffer	cBuf;
	DirectX::XMStoreFloat4x4(&cBuf.world, DirectX::XMMatrixTranspose(transMat.worldMat));
	DirectX::XMStoreFloat4x4(&cBuf.view, transMat.viewMat);
	DirectX::XMStoreFloat4x4(&cBuf.projection, transMat.projMat);
	DirectX::XMStoreFloat4(&cBuf.lightDirection,DirectX::XMVECTOR(light.GetLightDir()));
	DirectX::XMStoreFloat4(&cBuf.lightColor, DirectX::XMVECTOR(light.GetLightColor()));

	constantBuf->UpDate(&cBuf);
}

void ModelRender::SetDrawMode(const D3D11_FILL_MODE & fillMode, const D3D11_CULL_MODE& cullMode)
{
	modelData.primitive->SetDrawMode(fillMode, cullMode);
}

void ModelRender::SetColor(const Math::Vector4 & color)
{
	modelData.fbxModel->SetVertexColor(color.x, color.y, color.z, color.w);
}



void ModelRender::Initialize()
{
	if (GetEntity()->HasComponent<Material>())
	{
		Math::Vector4 color = GetEntity()->GetComponent<Material>().GetColor();
		//マテリアルの色を反映
		modelData.fbxModel->SetVertexColor(color.x, color.y, color.z, color.w);
	}
}

void ModelRender::UpDate()
{
	//Fbxのアニメーション行列
	if (modelData.fbxModel->IsAnimation())
	{
		modelData.fbxModel->AnimationMatrix();
	}
	modelData.primitive->UpDateVertexDatas(modelData.fbxModel->GetVertexData());
	//頂点データとインデックスデータの再設定
	//modelData.primitive->CreateVertexBuffer();
	//modelData.primitive->CreateIndexBuffer();
	//アニメーション番号の設定
	modelData.animationData->SetAnimationNumber(modelData.animationData->GetAnimationNumber());
	modelData.animationData->SetAnimationName(modelData.fbxModel->GetNowAnimationName());
	//アニメーション情報を表示
	//modelData.animationData->Output();

	this->UpDateMatrix(
		Manager::GetEntityManager().GetEntity("Camera").GetComponent<Camera>(),
		Manager::GetEntityManager().GetEntity("DirectionalLight").GetComponent<DirectionalLight>()
	);
}

void ModelRender::Render2D()
{
	constantBuf->Render();
	modelData.primitive->Attach();
}

void ModelRender::Render3D()
{
	constantBuf->Render();
	modelData.primitive->Attach();
}
