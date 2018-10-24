#pragma once
#pragma warning(disable:4081)
#pragma warning(disable:4996)

#include <DirectXMath.h>
#include <algorithm>

//---------------------------------------------------------------------------
//!@class		Math
//!@brief	���w�������N���X
//!@brief	Vector�Ȃǂ�����
//---------------------------------------------------------------------------
namespace Math
{
	//------------------------------------------------------------------------------
	//!@brief		float�^�̗v�f2������
	//------------------------------------------------------------------------------
	class Vector2 : public DirectX::XMFLOAT2
	{
	public:
		//!@brief	�R���X�g���N�^
		Vector2();
		Vector2(float x, float y);
		Vector2(float  value);
		Vector2(const DirectX::XMVECTOR& vector);
		
		//!@brief	operator�񍀉��Z�q
		Vector2&	operator=(const DirectX::XMVECTOR& vector);
		operator DirectX::XMVECTOR() const;
		Vector2 operator+() const;
		Vector2 operator-() const;
		Vector2& operator=(const Vector2& value);
		Vector2& operator=(const float& value);
		Vector2& operator+=(const Vector2& value);
		Vector2& operator+=(const float& value);
		Vector2& operator-=(const Vector2& value);
		Vector2& operator-=(const float& value);
		Vector2& operator*=(const Vector2& value);
		Vector2& operator*=(const float& value);
		Vector2& operator/=(const Vector2& value);
		Vector2& operator/=(const float& value);

		//!@brief	�����̎擾
		float		Length() const;
		//!@brief	���K��
		void		Normalize();
		//!@brief	���K��
		//!@return	���K�������x�N�g��
		Vector2&	Normalized();
	};

	//!@brief	operator�P�����Z�q
	Vector2 operator+(const Vector2& t1, const Vector2& t2);
	Vector2 operator+(const Vector2& t1, const float& t2);
	Vector2 operator-(const Vector2& t1, const Vector2& t2);
	Vector2 operator-(const Vector2& t1, const float& t2);
	Vector2 operator*(const Vector2& t1, const Vector2& t2);
	Vector2 operator*(const Vector2& t1, const float& t2);
	Vector2 operator/(const Vector2& t1, const Vector2& t2);
	Vector2 operator/(const Vector2& t1, const float& t2);


	//----------------------------------------------------------------------------------
	//!@brief		float�^�̗v�f3������
	//----------------------------------------------------------------------------------
	class Vector3 : public DirectX::XMFLOAT3
	{
	public:
		//!@brief	�R���X�g���N�^
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(float value);
		Vector3(const DirectX::XMVECTOR& vector);

		//!@brief	operator�񍀉��Z�q
		Vector3& operator=(const DirectX::XMVECTOR& vector);
		operator DirectX::XMVECTOR() const;
		Vector3 operator+() const;
		Vector3 operator-() const;
		Vector3& operator=(const Vector3& value);
		Vector3& operator=(const float& value);
		Vector3& operator+=(const Vector3& value);
		Vector3& operator+=(const float& value);
		Vector3& operator-=(const Vector3& value);
		Vector3& operator-=(const float& value);
		Vector3& operator*=(const Vector3& value);
		Vector3& operator*=(const float& value);
		Vector3& operator/=(const Vector3& value);
		Vector3& operator/=(const float& value);

		//!@brief	���������߂�
		//!@return	�x�N�g���̒���
		float		Length() const;
		//!@brief	���K��
		void		Normalize();
		//!@brief	���K��
		//!@return	���K�������x�N�g��
		const Vector3&	Normalized();
	};

	//!@brief	operator�P�����Z�q
	Vector3 operator+(const Vector3& t1, const Vector3& t2);
	Vector3 operator+(const Vector3& t1, const float& t2);
	Vector3 operator-(const Vector3& t1, const Vector3& t2);
	Vector3 operator-(const Vector3& t1, const float& t2);
	Vector3 operator*(const Vector3& t1, const Vector3& t2);
	Vector3 operator*(const Vector3& t1, const float& t2);
	Vector3 operator/(const Vector3& t1, const Vector3& t2);
	Vector3 operator/(const Vector3& t1, const float& t2);

	//----------------------------------------------------------------------------------
	//!@brief		float�^�̗v�f4������
	//----------------------------------------------------------------------------------
	class Vector4 : public DirectX::XMFLOAT4
	{
	public:
		//!@	�R���X�g���N�^
		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(float value);
		Vector4(const DirectX::XMVECTOR& vector);

		//!@brief	operator�񍀉��Z�q
		Vector4& operator=(const DirectX::XMVECTOR& vector);
		operator DirectX::XMVECTOR() const;
		Vector4 operator+() const;
		Vector4 operator-() const;
		Vector4& operator=(const Vector4& value);
		Vector4& operator=(const float& value);
		Vector4& operator+=(const Vector4& value);
		Vector4& operator+=(const float& value);
		Vector4& operator-=(const Vector4& value);
		Vector4& operator-=(const float& value);
		Vector4& operator*=(const Vector4& value);
		Vector4& operator*=(const float& value);
		Vector4& operator/=(const Vector4& value);
		Vector4& operator/=(const float& value);
	};

	//!@brief	operator�P�����Z�q
	Vector4 operator+(const Vector4& t1, const Vector4& t2);
	Vector4 operator+(const Vector4& t1, const float& t2);
	Vector4 operator-(const Vector4& t1, const Vector4& t2);
	Vector4 operator-(const Vector4& t1, const float& t2);
	Vector4 operator*(const Vector4& t1, const Vector4& t2);
	Vector4 operator*(const Vector4& t1, const float& t2);
	Vector4 operator/(const Vector4& t1, const Vector4& t2);
	Vector4 operator/(const Vector4& t1, const float& t2);


	//----------------------------------------------------------------------------
	//!@brief		���_�f�[�^
	//!@param[in]	�ʒu���
	//!@param[in]	�@�����
	//!@param[in]	UV���
	//----------------------------------------------------------------------------
	struct VertexData
	{
		Vector3 position;
		Vector3 normal;
		Vector2 uv;
		//!@brief	�R���X�g���N�^
		VertexData(Vector3 position, Vector3 normal, Vector2 uv);
	};

	
	//-----------------------------------------------------------------------------
	//!@class		Color
	//!@brief	�F�̏�������
	//-----------------------------------------------------------------------------
	class Color
	{
	public:
		Color() {}
		Color(float red, float green, float blue, float alpha)
		{
			color.x = red;
			color.y = green;
			color.z = blue;
			color.w = alpha;
		}
		Color(const Color& color)
		{
			this->color.x = color.color.x;
			this->color.y = color.color.y;
			this->color.z = color.color.z;
			this->color.w = color.color.w;
		}
		const float	GetRed() const
		{
			return color.x;
		}
		const float GetGreen() const
		{
			return color.y;
		}
		const float GetBlue() const
		{
			return color.z;
		}
		const float GetAlpha() const
		{
			return color.w;
		}

	private:
		Math::Vector4 color;
	};
}

namespace Math
{
	//!@brief	2D�x�N�g�����m�̓���
	//!@param[in]	vector1	1�ڂ̃x�N�g��
	//!@param[in]	vector2	2�ڂ̃x�N�g��
	//!return	���ς̒l
	float	Dot2D(const Vector2& vector1, const Vector2& vector2);
	//!@brief	3D�x�N�g�����m�̓���
	//!@param[in]	vector1	1�ڂ̃x�N�g��
	//!@param[in]	vector2	2�ڂ̃x�N�g��
	//!@return	���ς̒l
	float	Dot3D(const Vector3& vector1, const Vector3& vector2);
	//!@brief	2D�x�N�g�����m�̊O��
	//!@param[in]	vector1	1�ڂ̃x�N�g��
	//!@param[in]	vector2	2�ڂ̃x�N�g��
	//!@return	�O�ς̒l
	float	Cross2D(const Vector2& vector1, const Vector2& vector2);
	//!@brief	3D�x�N�g�����m�̊O��
	//!@param[in]	vector1	1�ڂ̃x�N�g��
	//!@param[in]	vector2	2�ڂ̃x�N�g��
	//!@return	�O�ς̒l
	Vector3&	Cross3D(const Vector3& vector1, const Vector3& vector2);
	//!@brief	3�_����̊O��
	//!@param[in]	pos1	1�ڂ̓_���W
	//!@param[in]	pos2	2�ڂ̓_���W
	//!@param[in]	pos3	3�ڂ̓_���W
	//!@return	�O�ς̒l
	Vector3&	Cross3D(const Vector3& pos1, const Vector3& pos2, const Vector3& pos3);
	//!@brief	���W�ϊ��s��
	//!@param[in]	position	���W
	DirectX::XMMATRIX&		TransformMatrix(const Math::Vector3& position);
	//!@brief	��]�ϊ��s��
	//!@param[in]	rotation	�p�x(�x��)
	DirectX::XMMATRIX&		RotationMatrix(const Math::Vector3& rotation);
	//!@brief	�g�k�ϊ��s��
	//!@param[in]	scale	�g�k
	DirectX::XMMATRIX&		ScaleMatrix(const Math::Vector3& scale);
	//!@brief	���Ԓl���Z�o����
	float Clamp(float x, float minValue, float maxValue);
	//!@brief	�������ɓ��e���ꂽ���������瓊�e�����̒��������߂�
	float LengthSegmentOnSeparateAxis(const Vector3& sep, const Vector3& e1, const Vector3& e2, const Vector3& e3 = Vector3(0, 0, 0));
	//!@brief	�x�N�g���̒��������߂�
	const float	VectorLength(const Vector3& pos1, const Vector3& pos2);
}
