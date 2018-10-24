#pragma once
#include "../../src/Component/ModelRender/ModelData.h"
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/ConstantBuffer/ConstantBuffer.h"
#include "../../src/Component/Camera/Camera.h"
#include "../../src/Component/Light/Light.h"




//---------------------------------------------------------------
//!@class		ModelRender
//!@brief	モデルを扱う
//---------------------------------------------------------------
class ModelRender : public Component
{
public:
	ModelRender() = delete;
	//!@brief	コンストラクタ
	//!@param[in]	model	fbxModelを生成したポインタ
	ModelRender(FbxModel* model);
	//!@brief	デストラクタ
	~ModelRender();
public:
	//!@brief	アニメーションの更新
	//!@brief	アニメーションを切り替えるときに呼ぶ
	//!@brief	頻繁に呼ぶとうまくいかない
	//!@param[in]	animationNumber	更新するアニメーション番号
	void	UpDateAnimation(const int& upDateAnimationNumber);
	//!@brief	マトリックスの更新
	void	UpDateMatrix(const Camera& camera,const DirectionalLight& light);
	//!@brief	描画モードのセット
	void	SetDrawMode(const D3D11_FILL_MODE& fillMode = D3D11_FILL_SOLID,const D3D11_CULL_MODE& cullMode = D3D11_CULL_BACK);
	//!@brief	色の設定
	void	SetColor(const Math::Vector4& color);
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	void*	operator new(size_t ptr)
	{
		return _mm_malloc(ptr, 16);
	}
	void	operator delete(void* ptr)
	{
		_mm_free(ptr);
	}
private:
	ModelData		modelData;
	ConstantBuffer*	constantBuf;
	CBuffer			cBuf;
	TransMatrix		transMat;
};