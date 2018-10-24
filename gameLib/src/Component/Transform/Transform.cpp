#include "Transform.h"
#include "../../src/GUISystem/GUISystem.h"



//!@brief	�R���X�g���N�^
//!@param[in]	pos		�ʒu
//!@param[in]	rotate	��]
//!@param[in]	scale	�g�k
Transform::Transform(const Math::Vector3& pos, const Math::Vector3& rotate, const Math::Vector3& scale)
	: position(pos),rotation(rotate),scale(scale)
{
	
}
//!@brief	�f�X�g���N�^
Transform::~Transform()
{
	
}

//!@brief	������
void	Transform::Initialize()
{
	
}
//!@brief	�X�V
void	Transform::UpDate()
{
	
}
//!@brief	�`��2D
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
//!@brief	�`��3D
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
