#pragma once
#include <DirectXMath.h>


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
}

