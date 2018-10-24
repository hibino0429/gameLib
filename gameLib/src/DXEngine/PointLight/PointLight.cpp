#include "PointLight.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "..\..\Component\Light\Light.h"


////!@brief	コンストラクタ
//PointLight::PointLight()
//	:position(Math::Vector3(0,0,0))
//	,attenuation(0.0f)
//	, color(0.0f)
//{
//	D3D11_BUFFER_DESC	constantBufDesc;
//	SecureZeroMemory(&constantBufDesc, sizeof(constantBufDesc));
//	constantBufDesc.ByteWidth	= sizeof(ConstantBuffer);
//	constantBufDesc.Usage		= D3D11_USAGE_DEFAULT;
//	constantBufDesc.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;
//	constantBufDesc.CPUAccessFlags	= 0;
//	constantBufDesc.MiscFlags		= 0;
//	constantBufDesc.StructureByteStride = 0;
//
//	auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(
//		&constantBufDesc,
//		nullptr,
//		&constantBuf
//	);
//
//	vertexShader = new VertexShader();
//	pixelShader = new PixelShader();
//
//	D3D11_INPUT_ELEMENT_DESC vertexDesc[]{
//	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
//	};
//
//	vertexShader->Create("./data/shaderData/PointLightVertex",vertexDesc,2);
//	pixelShader->Create("./data/shaderData/PointLightPixel");
//}
//
//void PointLight::Initialize()
//{
//}
//
//void PointLight::UpDate()
//{
//}
//
//void PointLight::Render2D()
//{
//}
//
//void PointLight::Render3D()
//{
//}
//
////!@brief	デストラクタ
//PointLight::~PointLight()
//{
//	constantBuf->Release();
//	constantBuf = nullptr;
//	
//	delete vertexShader;
//	vertexShader = nullptr;
//	delete pixelShader;
//	pixelShader = nullptr;
//
//}
//
//
////!@brief	更新
//void	PointLight::UpDate(Camera* camera)
//{
//	vertexShader->Set();
//	pixelShader->Set();
//
//
//	DirectX::XMMATRIX	world = DirectX::XMMatrixTranslation(0, 0, 0);
//
//	this->position = Math::Vector4(0, 2.0f, -10.5f, 0.0f);
//	this->attenuation = Math::Vector4(12.0f, 10.0f, 10.2f, 0.0f);
//	
//	ConstantBuffer cb;
//	DirectX::XMStoreFloat4x4(&cb.world, DirectX::XMMatrixTranspose(world));
//	XMStoreFloat4x4(&cb.view,camera->GetView());
//	XMStoreFloat4x4(&cb.projection, camera->GetProj());
//	DirectX::XMStoreFloat4(&cb.lightPos, position);
//	DirectX::XMStoreFloat4(&cb.attenuation, attenuation);
//
//	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &cb, 0, 0);
//}