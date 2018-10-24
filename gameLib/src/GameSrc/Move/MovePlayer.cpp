#include "MovePlayer.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/Utility/Utility.hpp"



MovePlayer::MovePlayer()
{
	key = new DirectKey(Engine<DXDevice>::GetDevice().GetScreen().GetHWND());
	moveSpeed = 10.0f;
}

MovePlayer::~MovePlayer()
{
	Utility::SafeDelete(key);
}

void MovePlayer::Initialize()
{

}

void MovePlayer::UpDate()
{
	if (!GetEntity()->HasComponent<Transform>()) { return; }
	Transform& trans = GetEntity()->GetComponent<Transform>();
	if (key->Push(DirectKey::Key::Left))
	{
		trans.position.x -= moveSpeed;
	}
	if (key->Push(DirectKey::Key::Right))
	{
		trans.position.x += moveSpeed;
	}
	if (key->Push(DirectKey::Key::Up))
	{
		trans.position.y += moveSpeed;
	}
	if (key->Push(DirectKey::Key::Down))
	{
		trans.position.y -= moveSpeed;
	}
}

void MovePlayer::Render2D()
{
}

void MovePlayer::Render3D()
{
}
