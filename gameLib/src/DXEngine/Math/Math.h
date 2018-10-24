#pragma once
#pragma warning(disable:4081)
#pragma warning(disable:4996)

#include <DirectXMath.h>
#include <algorithm>

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

		//!@brief	長さの取得
		float		Length() const;
		//!@brief	正規化
		void		Normalize();
		//!@brief	正規化
		//!@return	正規化したベクトル
		Vector2&	Normalized();
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

		//!@brief	長さを求める
		//!@return	ベクトルの長さ
		float		Length() const;
		//!@brief	正規化
		void		Normalize();
		//!@brief	正規化
		//!@return	正規化したベクトル
		const Vector3&	Normalized();
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

	
	//-----------------------------------------------------------------------------
	//!@class		Color
	//!@brief	色の情報を扱う
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
	//!@brief	2Dベクトル同士の内積
	//!@param[in]	vector1	1つ目のベクトル
	//!@param[in]	vector2	2つ目のベクトル
	//!return	内積の値
	float	Dot2D(const Vector2& vector1, const Vector2& vector2);
	//!@brief	3Dベクトル同士の内積
	//!@param[in]	vector1	1つ目のベクトル
	//!@param[in]	vector2	2つ目のベクトル
	//!@return	内積の値
	float	Dot3D(const Vector3& vector1, const Vector3& vector2);
	//!@brief	2Dベクトル同士の外積
	//!@param[in]	vector1	1つ目のベクトル
	//!@param[in]	vector2	2つ目のベクトル
	//!@return	外積の値
	float	Cross2D(const Vector2& vector1, const Vector2& vector2);
	//!@brief	3Dベクトル同士の外積
	//!@param[in]	vector1	1つ目のベクトル
	//!@param[in]	vector2	2つ目のベクトル
	//!@return	外積の値
	Vector3&	Cross3D(const Vector3& vector1, const Vector3& vector2);
	//!@brief	3点からの外積
	//!@param[in]	pos1	1つ目の点座標
	//!@param[in]	pos2	2つ目の点座標
	//!@param[in]	pos3	3つ目の点座標
	//!@return	外積の値
	Vector3&	Cross3D(const Vector3& pos1, const Vector3& pos2, const Vector3& pos3);
	//!@brief	座標変換行列
	//!@param[in]	position	座標
	DirectX::XMMATRIX&		TransformMatrix(const Math::Vector3& position);
	//!@brief	回転変換行列
	//!@param[in]	rotation	角度(度数)
	DirectX::XMMATRIX&		RotationMatrix(const Math::Vector3& rotation);
	//!@brief	拡縮変換行列
	//!@param[in]	scale	拡縮
	DirectX::XMMATRIX&		ScaleMatrix(const Math::Vector3& scale);
	//!@brief	中間値を算出する
	float Clamp(float x, float minValue, float maxValue);
	//!@brief	分離軸に投影された軸成分から投影線分の長さを求める
	float LengthSegmentOnSeparateAxis(const Vector3& sep, const Vector3& e1, const Vector3& e2, const Vector3& e3 = Vector3(0, 0, 0));
	//!@brief	ベクトルの長さを求める
	const float	VectorLength(const Vector3& pos1, const Vector3& pos2);
}
