#include "Map.h"
#include "../../src/DXEngine/DXEngine/DXEngine.h"
#include "../../src/Component/Transform/Transform.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Component/ModelRender/ModelRender.h"



Map::Map()
{
	
}

Map::~Map()
{
	
}

void Map::Initialize()
{
	if (!GetEntity()->HasComponent<Transform>()) { return; }
	Transform& trans = GetEntity()->GetComponent<Transform>();
	trans.scale = Math::Vector3(750, 50, 50);
	if (!GetEntity()->HasComponent<ModelRender>()) { return; }
	ModelRender& model = GetEntity()->GetComponent<ModelRender>();
	model.SetDrawMode(D3D11_FILL_SOLID, D3D11_CULL_BACK);
}

void Map::UpDate()
{
	if (!GetEntity()->HasComponent<Transform>()) { return; }
	Transform& trans = GetEntity()->GetComponent<Transform>();
	counter.Add();
	if (counter.GetCurrentCount() >= 300 + rand() % 300)
	{
		counter.Reset();
		if (rotateCnt.GetCurrentCount() <= 120 + rand() % 120)
		{
			trans.rotation.y += 1.0f;
			rotateCnt.Add();
		}
		else
		{
			rotateCnt.Reset();
		}
	}
}

void Map::Render2D()
{
}

void Map::Render3D()
{
}
