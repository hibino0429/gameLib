#include "Transform.h"
#include "../../src/GUISystem/GUISystem.h"



//!@brief	コンストラクタ
//!@param[in]	pos		位置
//!@param[in]	rotate	回転
//!@param[in]	scale	拡縮
Transform::Transform(const Math::Vector3& pos, const Math::Vector3& rotate, const Math::Vector3& scale)
	: position(pos),rotation(rotate),scale(scale)
{
	
}
//!@brief	デストラクタ
Transform::~Transform()
{
	
}

//!@brief	初期化
void	Transform::Initialize()
{
	
}
//!@brief	更新
void	Transform::UpDate()
{
	
}
//!@brief	描画2D
void	Transform::Render2D()
{
	float pos[3] = { position.x,position.y,position.z };
	float rot[3] = { rotation.x,rotation.y,rotation.z };
	float sca[3] = { scale.x,scale.y,scale.z };
	ImGui::Begin("Transform");
	ImGui::InputFloat3("Position : ",pos,3);
	ImGui::InputFloat3("Rotation : ", rot, 3);
	ImGui::InputFloat3("Scale : ", sca, 3);
	ImGui::End();
}
//!@brief	描画3D
void	Transform::Render3D() 
{

}

const Math::Vector3 & Transform::GetPosition() const
{
	return position;
}

const Math::Vector3 & Transform::GetRotation() const
{
	return rotation;
}

const Math::Vector3 & Transform::GetScale() const
{
	return scale;
}
