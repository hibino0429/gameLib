#pragma once
#include <vector>



//色データ
struct ColorData
{
	struct LambertData
	{
		float	ambient[3];		//アンビエント
		float	diffuse[4];		//ディヒューズ
		float	emissive[3];	//エミッシブ
		float	bump[3];		//バンプ
	};

	struct PhongData
	{
		float	specular[3];		//rgb
		float	shininess;			//光沢度
		float	reflective[3];		//反射
	};

	struct UVData
	{
		float	uvColor[2];			//uv色
		std::string	uvName;			//uv名
	};

	struct TextureData
	{
		std::string	filePath;		//ファイルパス
		std::string	uvSetName;		//uvSet名
	};

	LambertData		lambert;
	PhongData		phong;
	UVData			uv;
	TextureData		texture;
};


//---------------------------------------------------------------------
//!@class		Vertex
//!@brief	頂点データをもつデータ
//!@brief	デバイスなどに依存しないデータ
//---------------------------------------------------------------------
class Vertex
{
public:
	Vertex();
	Vertex(float x, float y, float z);
	Vertex(float x, float y, float z, float uvX,float uvY);
	Vertex(const Vertex& vertex);

	~Vertex();
private:
	struct UVData
	{
	public:
		UVData()
		{
			x = y = 0.0f;
		}
		UVData(float x, float y)
			: x(x),y(y)
		{
		}
	public:
		float	x;
		float	y;
	};
	struct Vec3
	{
	public:
		Vec3()
		{
			x = y = z = 0.0f;
		}
		Vec3(float x, float y, float z)
			: x(x),y(y),z(z)
		{
		}
	public:
		float	x;
		float	y;
		float	z;
	};
	struct Vec4
	{
	public:
		Vec4()
			: x(0.0f),y(0.0f),z(0.0f),w(1.0f)
		{}
		Vec4(float x, float y, float z, float w)
			: x(x), y(y), z(z), w(w)
		{
		}
	public:
		float	x;
		float	y;
		float	z;
		float	w;
	};
public:
	Vec3	pos;
	Vec4	diffuse;
	UVData	uv;
	Vec3	normal;
};


class Color
{
public:
	//!@brief	コンストラクタ
	//!@detial	デフォルトで白
	Color()
	{
		red = 1.0f;
		green = 1.0f;
		blue = 1.0f;
		alpha = 1.0f;
	}
	//!@brief	コンストラクタ
	//!@param[in]	red		赤色 0～1
	//!@param[in]	green	緑色 0～1
	//!@param[in]	blue	青色 0～1
	//!@param[in]	alpha	透明度 0～1
	Color(float red, float green, float blue, float alpha)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}
	//!@brief	デストラクタ
	~Color() {}
public:
	float	red;
	float	green;
	float	blue;
	float	alpha;
};

