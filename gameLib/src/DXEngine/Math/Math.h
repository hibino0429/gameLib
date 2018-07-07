#pragma once
#include <DirectXMath.h>


//---------------------------------------------------------------------------
//!@class		Math
//!@brief	数学を扱うクラス
//!@brief	Vectorなどを扱う
//---------------------------------------------------------------------------
namespace Math
{
	//------------------------------------------------------------------------------
	//!@brief		float型の要素2つを持つ
	//------------------------------------------------------------------------------
	class Vector2 : public DirectX::XMFLOAT2
	{
	public:
		//!@brief	コンストラクタ
		Vector2();
		Vector2(float x, float y);
		Vector2(float  value);
		Vector2(const DirectX::XMVECTOR& vector);
		
		//!@brief	operator二項演算子
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

	//!@brief	operator単項演算子
	Vector2 operator+(const Vector2& t1, const Vector2& t2);
	Vector2 operator+(const Vector2& t1, const float& t2);
	Vector2 operator-(const Vector2& t1, const Vector2& t2);
	Vector2 operator-(const Vector2& t1, const float& t2);
	Vector2 operator*(const Vector2& t1, const Vector2& t2);
	Vector2 operator*(const Vector2& t1, const float& t2);
	Vector2 operator/(const Vector2& t1, const Vector2& t2);
	Vector2 operator/(const Vector2& t1, const float& t2);


	//----------------------------------------------------------------------------------
	//!@brief		float型の要素3つを持つ
	//----------------------------------------------------------------------------------
	class Vector3 : public DirectX::XMFLOAT3
	{
	public:
		//!@brief	コンストラクタ
		Vector3();
		Vector3(float x, float y, float z);
		Vector3(float value);
		Vector3(const DirectX::XMVECTOR& vector);

		//!@brief	operator二項演算子
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

	//!@brief	operator単項演算子
	Vector3 operator+(const Vector3& t1, const Vector3& t2);
	Vector3 operator+(const Vector3& t1, const float& t2);
	Vector3 operator-(const Vector3& t1, const Vector3& t2);
	Vector3 operator-(const Vector3& t1, const float& t2);
	Vector3 operator*(const Vector3& t1, const Vector3& t2);
	Vector3 operator*(const Vector3& t1, const float& t2);
	Vector3 operator/(const Vector3& t1, const Vector3& t2);
	Vector3 operator/(const Vector3& t1, const float& t2);

	//----------------------------------------------------------------------------------
	//!@brief		float型の要素4つを持つ
	//----------------------------------------------------------------------------------
	class Vector4 : public DirectX::XMFLOAT4
	{
	public:
		//!@	コンストラクタ
		Vector4();
		Vector4(float x, float y, float z, float w);
		Vector4(float value);
		Vector4(const DirectX::XMVECTOR& vector);

		//!@brief	operator二項演算子
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

	//!@brief	operator単項演算子
	Vector4 operator+(const Vector4& t1, const Vector4& t2);
	Vector4 operator+(const Vector4& t1, const float& t2);
	Vector4 operator-(const Vector4& t1, const Vector4& t2);
	Vector4 operator-(const Vector4& t1, const float& t2);
	Vector4 operator*(const Vector4& t1, const Vector4& t2);
	Vector4 operator*(const Vector4& t1, const float& t2);
	Vector4 operator/(const Vector4& t1, const Vector4& t2);
	Vector4 operator/(const Vector4& t1, const float& t2);


	//----------------------------------------------------------------------------
	//!@brief		頂点データ
	//!@param[in]	位置情報
	//!@param[in]	法線情報
	//!@param[in]	UV情報
	//----------------------------------------------------------------------------
	struct VertexData
	{
		Vector3 position;
		Vector3 normal;
		Vector2 uv;
		//!@brief	コンストラクタ
		VertexData(Vector3 position, Vector3 normal, Vector2 uv);
	};
}

