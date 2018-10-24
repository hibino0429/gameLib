#include "MoveCamera.h"
#include "../../src/GameSystem/ECS/Entity/Entity.h"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../src/Utility/Utility.hpp"


MoveInput::MoveInput()
	: DirOffset(90.0f)
	, speed(0.2f)
	, velocity(2.0f,2.0f,2.0f)
{
	key = new DirectKey(Engine<DXDevice>::GetDevice().GetScreen().GetHWND());
	mouse = new DirectMouse(Engine<DXDevice>::GetDevice().GetScreen().GetHWND());
}

MoveInput::~MoveInput()
{
	Utility::SafeDelete(key);
	Utility::SafeDelete(mouse);
}


void MoveInput::Initialize()
{
	
}


void MoveInput::UpDate()
{
	key->Run();
	mouse->Run();
	DecideForwardAndBackDir();
	MoveForwardAndBack();
	DecideLeftAndRightDir();
	MoveLeftAndRight();
	MoveRotation();
}

void MoveInput::Render2D()
{
}

void MoveInput::Render3D()
{
}

void MoveInput::MoveForwardAndBack()
{
	if (!GetEntity()->HasComponent<Transform>()) { return; }
	Transform& trans = GetEntity()->GetComponent<Transform>();
	if (mouse->UpWheelRotation())
	{
		trans.position += dir;
	}
	if (mouse->DownWheelRotation())
	{
		trans.position -= dir;
	}
}

void MoveInput::MoveLeftAndRight()
{
	if (!GetEntity()->HasComponent<Transform>()) { return; }
	Transform& trans = GetEntity()->GetComponent<Transform>();
	if (mouse->LButtonPush())
	{
		trans.position.x += (mouse->GetMousePos().x - Engine<DXDevice>::GetDevice().GetScreen().GetWidth() / 2.f) * 0.0003f;
		trans.position.y += (mouse->GetMousePos().y - Engine<DXDevice>::GetDevice().GetScreen().GetHeight() / 2.f) * 0.0003f;
	}
}

void MoveInput::DecideForwardAndBackDir()
{
	if (!GetEntity()->HasComponent<Transform>()) { return; }
	Transform& trans = GetEntity()->GetComponent<Transform>();
	dir.x = cosf(DirectX::XMConvertToRadians(-trans.rotation.y + DirOffset)) * cosf(DirectX::XMConvertToRadians(-trans.rotation.x)) * velocity.x;
	dir.y = sinf(DirectX::XMConvertToRadians(-trans.rotation.x)) * velocity.y;
	dir.z = cosf(DirectX::XMConvertToRadians(-trans.rotation.x)) * sinf(DirectX::XMConvertToRadians(-trans.rotation.y + DirOffset )) * velocity.z;
}

void MoveInput::DecideLeftAndRightDir()
{
	if (!GetEntity()->HasComponent<Transform>()) { return; }
	Transform& trans = GetEntity()->GetComponent<Transform>();
	dir.x = cosf(DirectX::XMConvertToRadians(-trans.rotation.y)) * cosf(DirectX::XMConvertToRadians(-trans.rotation.x)) * velocity.x;
	dir.y = sinf(DirectX::XMConvertToRadians(-trans.rotation.x)) * velocity.y;
	dir.z = cosf(DirectX::XMConvertToRadians(-trans.rotation.x)) * sinf(DirectX::XMConvertToRadians(-trans.rotation.y)) * velocity.z;
}

void MoveInput::MoveRotation()
{
	if (!GetEntity()->HasComponent<Transform>()) { return; }
	Transform& trans = GetEntity()->GetComponent<Transform>();
	if (mouse->RButtonPush())
	{
		trans.rotation.x += (mouse->GetMousePos().y - Engine<DXDevice>::GetDevice().GetScreen().GetHeight() / 2.f) * 0.0001f;
		trans.rotation.y += (mouse->GetMousePos().x - Engine<DXDevice>::GetDevice().GetScreen().GetWidth() / 2.f) * 0.0001f;
	}
	if (trans.rotation.x >= 20)
	{
		trans.rotation.x = 20;
	}
	if (trans.rotation.x <= -90)
	{
		trans.rotation.x = -90;
	}
}
