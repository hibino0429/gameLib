#include "SpriteRender.h"


Sprite2D::Sprite2D(const std::string& filePath)
{
	spriteBatch = new DirectX::SpriteBatch(&Engine<DXDevice>::GetDevice().GetDeviceContext3D());

	std::wstring wstr = std::wstring(filePath.begin(), filePath.end());
	LPCWSTR sw = wstr.c_str();
	DirectX::CreateWICTextureFromFile(&Engine<DXDevice>::GetDevice().GetDevice3D(), sw, &resource, &textureResourceView);

	rotate = 0.0f;
	pivot = Math::Vector2(0, 0);
}


Sprite2D::~Sprite2D()
{
	Utility::SafeRelease(textureResourceView);
	Utility::SafeRelease(resource);
	Utility::SafeDelete(spriteBatch);
}


void	Sprite2D::Draw(const Math::Box2D& draw, const Math::Box2D& src, bool isCente, const Math::Color& color)
{
	DirectX::FXMVECTOR convertColor = DirectX::XMVectorSet(color.GetRed(), color.GetGreen(), color.GetBlue(), color.GetAlpha());
	Math::Vector2	pos(draw.x, draw.y);
	Math::Vector2	scale(draw.width / src.width, draw.height / src.height);
	if (isCente)
	{
		pivot = Math::Vector2((src.x + src.width) / 2.0f, (src.y + src.height) / 2.0f);
	}
	spriteBatch->Begin();
	spriteBatch->Draw(textureResourceView, pos, &src, convertColor, rotate, pivot, scale);
	spriteBatch->End();
}

void	Sprite2D::SetRotation(const float rotate)
{
	this->rotate = rotate;
}