#include "PointLight.h"

//!@brief	コンストラクタ
PointLight::PointLight()
	:position(Math::Vector3(0,0,0))
	,attenuation(0.0f)
	, color(0.0f)
{

}

//!@brief	デストラクタ
PointLight::~PointLight()
{

}


//!@brief	更新
void	PointLight::UpDate()
{

}