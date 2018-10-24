#include "Ray.h"
#include "../../src/Component/Camera/Camera.h"
#include "../../src/Component/Light/Light.h"


Ray::Ray(const Math::Vector3 & beginPos, const Math::Vector3 & dirVec)
	:beginPos(beginPos),dirVec(dirVec)
{
	constantBuf = new ConstantBuffer();
}

Ray::~Ray()
{
	if (constantBuf != nullptr)
	{
		delete constantBuf;
		constantBuf = nullptr;
	}
}

const Math::Vector3 & Ray::GetBeginPos() const
{
	return beginPos;
}

const Math::Vector3 & Ray::GetDirVec() const
{
	return dirVec;
}

void Ray::Initialize()
{
	
}

void Ray::UpDate()
{
	//始点と方向ベクトルを移動、回転する際には、Matrixを計算する
	transform.position = beginPos;
	DirectX::XMMATRIX	matT = Math::TransformMatrix(transform.position);
	DirectX::XMMATRIX	matR = Math::RotationMatrix(transform.rotation);
	DirectX::XMMATRIX	matS = Math::ScaleMatrix(transform.scale);

	Camera camera = Manager::GetEntityManager().GetEntity("Camera").GetComponent<Camera>();
	DirectionalLight light = Manager::GetEntityManager().GetEntity("DirectionalLight").GetComponent<DirectionalLight>();
	DirectX::XMMATRIX	world = matS * matR * matT;
	DirectX::XMMATRIX	view = camera.GetViewMatrix();
	DirectX::XMMATRIX	proj = camera.GetProjectionMatrix();

	CBuffer	cBuf;
	DirectX::XMStoreFloat4x4(&cBuf.world, DirectX::XMMatrixTranspose(world));
	DirectX::XMStoreFloat4x4(&cBuf.view, view);
	DirectX::XMStoreFloat4x4(&cBuf.projection, proj);
	DirectX::XMStoreFloat4(&cBuf.lightDirection, DirectX::XMVECTOR(light.GetLightDir()));
	DirectX::XMStoreFloat4(&cBuf.lightColor, DirectX::XMVECTOR(light.GetLightColor()));

	constantBuf->UpDate(&cBuf);
}

void Ray::Render2D()
{
	
}

void Ray::Render3D()
{
	constantBuf->Render();
}
