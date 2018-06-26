#include "Camera.h"
#include "../../src/Engine/Engine.h"

//!@brief	コンストラクタ
//!@brief	eyePos		視点
//!@brief	targetPos	注視点
//!@brief	upVec		上ベクトル
Camera::Camera(const Math::Vector3& eyePos, const Math::Vector3& targetPos, const Math::Vector3& upVec)
	: position(eyePos)
	, angle(targetPos)
	, eyePos(eyePos)
	, targetPos(targetPos)
	, upVec(upVec)
	, constantBuf(nullptr)
{
	float asp = Engine<DXDevice>::GetDevice().GetViewPort().Width / Engine<DXDevice>::GetDevice().GetViewPort().Height;

	this->SetFovAngle(45.0f);
	this->SetAspect(asp);
	this->SetNearZ(0.1f);
	this->SetFarZ(100.0f);	
	//Create();
}

//!@brief	デストラクタ
Camera::~Camera()
{

}


//!@brief	カメラの生成
bool	Camera::Create()
{
	D3D11_BUFFER_DESC	constantBufDesc;
	SecureZeroMemory(&constantBufDesc,sizeof(constantBufDesc));
	constantBufDesc.ByteWidth	= sizeof(ConstantBuffer);
	constantBufDesc.Usage		= D3D11_USAGE_DEFAULT;
	constantBufDesc.BindFlags	= D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags		= 0;
	constantBufDesc.MiscFlags			= 0;
	constantBufDesc.StructureByteStride = 0;

	auto result = Engine<DXDevice>::GetDevice().GetDevice3D().CreateBuffer(
		&constantBufDesc,
		nullptr,
		&constantBuf
	);

	if (FAILED(result))
	{
		MessageBoxA(nullptr, "バッファの作成に失敗", "Camera.Create()", MB_OK);
		return false;
	}
	return true;
}

//!@brief	View変換を行う
void	Camera::LookAtLH()
{
	//view変換する
	DirectX::XMMATRIX viewMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixLookAtLH(eyePos, targetPos, upVec)
	);
	
	DirectX::XMStoreFloat4x4(&constant.view, viewMat);
}

//!@brief	Ortho変換を行う
void	Camera::OrthoFovLH()
{
	DirectX::XMMATRIX orthoViewMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixOrthographicLH(
			Engine<DXDevice>::GetDevice().GetViewPort().Width,
			Engine<DXDevice>::GetDevice().GetViewPort().Height,
			nearZ,
			farZ)
	);

	//Orthoビュー変換を行う
	DirectX::XMStoreFloat4x4(&constant.view,orthoViewMat);	
}

//!@brief	Perspective変換を行う
void	Camera::PerspectiveFovLH()
{
	//perspectiveの変換を行う
	DirectX::XMMATRIX perspectiveMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(fovAngle),
			aspect,
			nearZ,
			farZ
		)
	);

	DirectX::XMMATRIX worldMat = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixTranslation(eyePos.x, eyePos.y, eyePos.z)
	);

	DirectX::XMStoreFloat4x4(&constant.projection, perspectiveMat);
	DirectX::XMStoreFloat4x4(&constant.world, worldMat);
	//Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &constant, 0, 0);
}




//概要: 視点の設定
//引数: eyePos_ 視点
void	Camera::SetEyePos(const Math::Vector3& eyePos_)
{
	eyePos = eyePos_;
}
//概要: 注視点の設定
//引数: targetPos_ 注視点
void	Camera::SetTargetPos(const Math::Vector3& targetPos_)
{
	targetPos = targetPos_;
}
//概要: 上方向ベクトルの設定
//引数: upVec_ 上方向ベクトル
void	Camera::SetUpVec(const Math::Vector3& upVec_)
{
	upVec = upVec_;
}

//概要: 視野角(度数)の設定
//引数: fovAngle_ 視野角
void	Camera::SetFovAngle(const float& fovAngle_)
{
	fovAngle = fovAngle_;
}
//概要: アスペクトの設定
//引数: aspect_ アスペクト比
void	Camera::SetAspect(const float& aspect_)
{
	aspect = aspect_;
}
//概要: 前方投影面までの距離の設定
//引数: nearZ_ 前方投影面までの距離
void	Camera::SetNearZ(const float& nearZ_)
{
	nearZ = nearZ_;
}
//概要: 後方投影面までの距離の設定
//引数: farZ_ 後方投影面までの距離
void	Camera::SetFarZ(const float& farZ_)
{
	farZ = farZ_;
}

//!@brief	カメラの位置を動かす
//!@param[in]	moveVec	移動量
void	Camera::AddVec(const Math::Vector3& moveVec)
{
	position += moveVec;
}

//!@brief	ビュー行列の取得
DirectX::XMFLOAT4X4&	Camera::GetViewMatrix()
{
	return this->constant.view;
}
//!@brief	プロジェクション行列の取得
DirectX::XMFLOAT4X4&	Camera::GetProjectionMatrix()
{
	return this->constant.projection;
}