#pragma once

#include <string>
#include "../../src/GameSystem/Fbx/Fbx.h"
#include "../../src/DXEngine/PrimitiveData/PrimitiveData.h"
#include "../../src/DXEngine/Camera/Camera.h"
#include "../../src/Component/AnimationData/AnimationData.h"

//----------------------------------------------------------------------------------------
//!@class		Model
//!@brief	モデルを扱います
//----------------------------------------------------------------------------------------
class Model
{
public:
	Model();
	//!@brief	コンストラクタ
	//!@param[in]	filePath	ファイルパス
	Model(const std::string& filePath);
	~Model();

	void	UpDate();
	void	Render();

private:
	//!@brief	インプットレイアウトの作成
	void	CreateInputLayout();
	//!@brief	定数バッファの作成
	void	CreateConstantBuffer();
public:
	//!@brief	アニメーションの更新
	//!@brief	アニメーションを切り替えるときに呼ぶ
	//!@brief	頻繁に呼ぶとうまくいかない
	//!@param[in]	animationNumber	更新するアニメーション番号
	void	UpDateAnimation(const int& upDateAnimationNumber);
public:
	//!@brief	マトリックスの設定
	void	SetMatrix(Camera* camera);
private:
	//定数バッファ
	struct ConstantBuffer
	{
		DirectX::XMFLOAT4X4	world;
		DirectX::XMFLOAT4X4	view;
		DirectX::XMFLOAT4X4	projection;
	};
private:
	VertexShader*	vertexShader;
	PixelShader*	pixelShader;
	ID3D11Buffer*	constantBuf;
	Primitive*		primitive;
	FbxModel*		fbxModel;
	Math::Vector3	pos;
	Math::Vector3	angle;
	Math::Vector3	scale;
	AnimationData*	animationData;	
};