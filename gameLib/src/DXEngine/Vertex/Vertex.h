#pragma once
#include <vector>



//�F�f�[�^
struct ColorData
{
	struct LambertData
	{
		float	ambient[3];		//�A���r�G���g
		float	diffuse[4];		//�f�B�q���[�Y
		float	emissive[3];	//�G�~�b�V�u
		float	bump[3];		//�o���v
	};

	struct PhongData
	{
		float	specular[3];		//rgb
		float	shininess;			//����x
		float	reflective[3];		//����
	};

	struct UVData
	{
		float	uvColor[2];			//uv�F
		std::string	uvName;			//uv��
	};

	struct TextureData
	{
		std::string	filePath;		//�t�@�C���p�X
		std::string	uvSetName;		//uvSet��
	};

	LambertData		lambert;
	PhongData		phong;
	UVData			uv;
	TextureData		texture;
};


//---------------------------------------------------------------------
//!@class		Vertex
//!@brief	���_�f�[�^�����f�[�^
//!@brief	�f�o�C�X�ȂǂɈˑ����Ȃ��f�[�^
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
	//!@brief	�R���X�g���N�^
	//!@detial	�f�t�H���g�Ŕ�
	Color()
	{
		red = 1.0f;
		green = 1.0f;
		blue = 1.0f;
		alpha = 1.0f;
	}
	//!@brief	�R���X�g���N�^
	//!@param[in]	red		�ԐF 0�`1
	//!@param[in]	green	�ΐF 0�`1
	//!@param[in]	blue	�F 0�`1
	//!@param[in]	alpha	�����x 0�`1
	Color(float red, float green, float blue, float alpha)
	{
		this->red = red;
		this->green = green;
		this->blue = blue;
		this->alpha = alpha;
	}
	//!@brief	�f�X�g���N�^
	~Color() {}
public:
	float	red;
	float	green;
	float	blue;
	float	alpha;
};

