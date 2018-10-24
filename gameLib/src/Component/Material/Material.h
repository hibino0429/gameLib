#pragma once
#include "../../src/Component/Material/MaterialData.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Material/Shader.h"


//-------------------------------------------------------
//!@class	Material
//!@brief	マテリアルの情報を扱う
//!@brief	テクスチャのアタッチやそのもの自体の色
//-------------------------------------------------------
class Material : public Component
{
public:
	Material() = delete;
	//!@brief	コンストラクタ
	//!@param[in]	color	色
	Material(const Math::Vector4& color);
	//!@brief	コンストラクタ
	//!@param[in]	texture	テクスチャ
	Material(Texture* texture);
	//!@brief	デストラクタ
	virtual ~Material();
public:
	//!@brief	テクスチャを変更する
	//!@brief	前のテクスチャは破棄される
	//!@param[in]	texture	テクスチャ
	void	ChangeTexture(Texture* texture);
	//!@brief	色の取得
	//!@return	x: red, y: green, z: blue, w: alpha
	const Math::Vector4&	GetColor() const;
	//!@brief	使用するシェーダののセット
	//!@param[in]	shader	使用するシェーダ
	bool	SetShader(Shader* shader);
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
private:
	MaterialData	data;
	Shader*			shader;
};