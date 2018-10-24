#pragma once
#include "../../src/GameSystem/ECS/Component/Component.h"
#include "../../src/Component/Light/LightData.h"
#include "../../src/Component/ConstantBuffer/ConstantBuffer.h"
#include "../../src/Component/Material/Material.h"


//----------------------------------------------------
//!@class		ライトコンポーネント
//----------------------------------------------------
class Light : Component
{
public:
	//!@brief	コンストラクタ
	//!@param[in]	lightType	ライトの種類
	//!@param[in]	lightColor	ライトの色
	Light(const LightType& lightType, const Math::Vector3& lightColor);
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	const LightData&		GetLightData() const;
	const TransMatrix&		GetTransMat() const;
	void	SetMatrix(const TransMatrix& transMatrix);
	void*	operator new(size_t ptr)
	{
		return _mm_malloc(ptr, 16);
	}
	void	operator delete(void* ptr)
	{
		_mm_free(ptr);
	}
private:
	LightData		data;
	TransMatrix		transMat;
};


//----------------------------------------------------
//!@class		平行光源
//----------------------------------------------------
class	DirectionalLight : public Component
{
public:
	//!@brief	コンストラクタ
	DirectionalLight();
	//!@brief	コンストラクタ
	//!@param[in]	lightDir	光の向き
	DirectionalLight(const Math::Vector3& lightDir);
	//!@brief	コンストラクタ
	//!@param[in]	lightDir	光の向き
	//!@param[in]	lightColor	光の色
	DirectionalLight(const Math::Vector3& lightDir, const Math::Vector3& lightColor);
	//!@brief	デストラクタ
	~DirectionalLight();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	光の方向の取得
	const Math::Vector3&	GetLightDir() const;
	//!@brief	光の色の取得
	const Math::Vector3&	GetLightColor() const;
	//!@brief	光の方向の設定
	//!@param[in]	lightDir	光の向き
	void	SetLightDir(const Math::Vector3& lightDir);
	//!@brief	マトリックスの設定
	void	SetMatrix(const TransMatrix& transMatrix);
private:
	Light*					light;
	DirectinalLightData		data;
};



//-----------------------------------------------------
//!@class		点光源
//-----------------------------------------------------
class PointLight : public Component
{
public:
	//!@brief	コンストラクタ
	PointLight();
	//!@brief	コンストラクタ
	//!@param[in]	pos	光源位置
	//!@param[in]	attenuation	減衰率
	PointLight(const Math::Vector3& pos, const Math::Vector3& attenuation);
	//!@brief	デストラクタ
	~PointLight();
public:
	virtual void Initialize() override;
	virtual void UpDate() override;
	virtual void Render2D() override;
	virtual void Render3D() override;
public:
	//!@brief	マトリックスのセット
	//void	SetMatrix(const TransMatrix& transMatrix);
private:
	Light*				light;
	PointLightData		data;
};