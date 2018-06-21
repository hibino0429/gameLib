#include "Camera.h"
#include "../../src/Engine/Engine.h"

//!@brief	コンストラクタ
//!@brief	eyePos		視点
//!@brief	targetPos	注視点
//!@brief	upVec		上ベクトル
Camera::Camera(const Math::Vector3& position, const Math::Vector3& angle)
	: position(position)
	, angle(angle)
	, constantBuf(nullptr)
{
	this->SetFovAngle(30.0f);
	this->SetAspect(640.0f / 480.0f);
	this->SetNearZ(1.0f);
	this->SetFarZ(20.0f);

	Create();
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
	constantBufDesc.ByteWidth = static_cast<UINT>(sizeof(constant));
	constantBufDesc.Usage = D3D11_USAGE_DEFAULT;
	constantBufDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufDesc.CPUAccessFlags = 0;
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
	constant.view = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixInverse(
			nullptr,
			DirectX::XMMatrixRotationX(DirectX::XMConvertToRadians(angle.x)) *
			DirectX::XMMatrixRotationY(DirectX::XMConvertToRadians(angle.y)) *
			DirectX::XMMatrixRotationZ(DirectX::XMConvertToRadians(angle.z)) *
			DirectX::XMMatrixTranslation(position.x, position.y, position.z)
		)
	);

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &constant, 0, 0);

	//DXEngine::GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &constant, 0, 0);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().VSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().HSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().DSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().GSSetConstantBuffers(0, 1, &constantBuf);
	Engine<DXDevice>::GetDevice().GetDeviceContext3D().PSSetConstantBuffers(0, 1, &constantBuf);
}

//!@brief	Ortho変換を行う
void	Camera::OrthoFovLH()
{
	float width = 0, height = 0;
	//Orthoビュー変換を行う
	constant.projection = DirectX::XMMatrixTranspose(
		DirectX::XMMatrixOrthographicLH(
			static_cast<float>(width),
			static_cast<float>(height),
			nearZ,
			farZ)
	);

	Engine<DXDevice>::GetDevice().GetDeviceContext3D().UpdateSubresource(constantBuf, 0, nullptr, &constant.projection, 0, 0);
}

//概要: Perspective変換を行う
void	Camera::PerspectiveFovLH()
{
	constant.projection = DirectX::XMMatrixPerspectiveFovLH(
		DirectX::XMConvertToRadians(fovAngle),
		aspect,
		nearZ,
		farZ
	);

}



//概要: 視点の設定
//引数: eyePos_ 視点
void	Camera::SetEyePos(const Math::Vector3& eyePos_)
{
	//eyePos = eyePos_;
}
//概要: 注視点の設定
//引数: targetPos_ 注視点
void	Camera::SetTargetPos(const Math::Vector3& targetPos_)
{
	//targetPos = targetPos_;
}
//概要: 上方向ベクトルの設定
//引数: upVec_ 上方向ベクトル
void	Camera::SetUpVec(const Math::Vector3& upVec_)
{
	//upVec = upVec_;
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



//!@brief 定数バッファの取得
ID3D11Buffer**	Camera::GetConstantBuf()
{
	return &constantBuf;
}



//!@brief	カメラの位置を動かす
//!@param[in]	moveVec	移動量
void	Camera::AddVec(const Math::Vector3& moveVec)
{
	position += moveVec;
}