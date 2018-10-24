#include "Math.h"


namespace Math
{
	//------------------------------------------------------------------------------
	//!@brief		float型の要素2つを持つ
	//------------------------------------------------------------------------------
	Vector2::Vector2() : DirectX::XMFLOAT2()
	{
	}
	Vector2::Vector2(float x, float y) : DirectX::XMFLOAT2(x, y)
	{
	}
	Vector2::Vector2(float value) : DirectX::XMFLOAT2(value, value)
	{
	}
	Vector2::Vector2(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT2()
	{
		DirectX::XMStoreFloat2(this, vector);
	}
	Vector2& Vector2::operator=(const DirectX::XMVECTOR& vector)
	{
		DirectX::XMStoreFloat2(this, vector);
		return *this;
	}
	Vector2::operator DirectX::XMVECTOR() const
	{
		return DirectX::XMLoadFloat2(this);
	}
	Vector2 Vector2::operator+() const
	{
		return Vector2(this->x, this->y);
	}
	Vector2 Vector2::operator-() const
	{
		return Vector2(-this->x, -this->y);
	}
	Vector2& Vector2::operator=(const Vector2& value)
	{
		x = value.x;
		y = value.y;
		return *this;
	}
	Vector2& Vector2::operator=(const float& value)
	{
		x = value;
		y = value;
		return *this;
	}
	Vector2& Vector2::operator+=(const Vector2& value)
	{
		x += value.x;
		y += value.y;
		return *this;
	}
	Vector2& Vector2::operator+=(const float& value)
	{
		x += value;
		y += value;
		return *this;
	}
	Vector2& Vector2::operator-=(const Vector2& value)
	{
		x -= value.x;
		y -= value.y;
		return *this;
	}
	Vector2& Vector2::operator-=(const float& value)
	{
		x -= value;
		y -= value;
		return *this;
	}
	Vector2& Vector2::operator*=(const Vector2& value)
	{
		x *= value.x;
		y *= value.y;
		return *this;
	}
	Vector2& Vector2::operator*=(const float& value)
	{
		x *= value;
		y *= value;
		return *this;
	}
	Vector2& Vector2::operator/=(const Vector2& value)
	{
		x /= value.x;
		y /= value.y;
		return *this;
	}
	Vector2& Vector2::operator/=(const float& value)
	{
		x /= value;
		y /= value;
		return *this;
	}

	//!@brief	長さの取得
	float	Vector2::Length() const
	{
		return sqrtf(x * x + y * y);
	}
	//!@brief	正規化
	void	Vector2::Normalize()
	{
		float length = Length();
		x /= length;
		y /= length;
	}
	//!@brief	正規化
	//!@return	正規化したベクトル
	Vector2&	Vector2::Normalized()
	{
		Normalize();
		return *this;
	}

	Vector2 operator+(const Vector2& t1, const Vector2& t2)
	{
		return Vector2(t1) += t2;
	}
	Vector2 operator+(const Vector2& t1, const float& t2)
	{
		return Vector2(t1) += t2;
	}
	Vector2 operator-(const Vector2& t1, const Vector2& t2)
	{
		return Vector2(t1) -= t2;
	}
	Vector2 operator-(const Vector2& t1, const float& t2)
	{
		return Vector2(t1) -= t2;
	}
	Vector2 operator*(const Vector2& t1, const Vector2& t2)
	{
		return Vector2(t1) *= t2;
	}
	Vector2 operator*(const Vector2& t1, const float& t2)
	{
		return Vector2(t1) *= t2;
	}
	Vector2 operator/(const Vector2& t1, const Vector2& t2)
	{
		return Vector2(t1) /= t2;
	}
	Vector2 operator/(const Vector2& t1, const float& t2)
	{
		return Vector2(t1) /= t2;
	}


	//----------------------------------------------------------------------------------
	//!@brief		float型の要素3つを持つ
	//----------------------------------------------------------------------------------
	Vector3::Vector3() : DirectX::XMFLOAT3()
	{
	}
	Vector3::Vector3(float x, float y, float z) : DirectX::XMFLOAT3(x, y, z)
	{
	}
	Vector3::Vector3(float value) : DirectX::XMFLOAT3(value, value, value)
	{
	}
	Vector3::Vector3(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT3()
	{
		DirectX::XMStoreFloat3(this, vector);
	}
	Vector3& Vector3::operator=(const DirectX::XMVECTOR& vector)
	{
		DirectX::XMStoreFloat3(this, vector);
		return *this;
	}
	Vector3::operator DirectX::XMVECTOR() const
	{
		return DirectX::XMLoadFloat3(this);
	}
	Vector3 Vector3::operator+() const
	{
		return Vector3(this->x, this->y, this->z);
	}
	Vector3 Vector3::operator-() const
	{
		return Vector3(-this->x, -this->y, -this->z);
	}
	Vector3& Vector3::operator=(const Vector3& value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
		return *this;
	}
	Vector3& Vector3::operator=(const float& value)
	{
		x = value;
		y = value;
		z = value;
		return *this;
	}
	Vector3& Vector3::operator+=(const Vector3& value)
	{
		x += value.x;
		y += value.y;
		z += value.z;
		return *this;
	}
	Vector3& Vector3::operator+=(const float& value)
	{
		x += value;
		y += value;
		z += value;
		return *this;
	}
	Vector3& Vector3::operator-=(const Vector3& value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;
		return *this;
	}
	Vector3& Vector3::operator-=(const float& value)
	{
		x -= value;
		y -= value;
		z -= value;
		return *this;
	}
	Vector3& Vector3::operator*=(const Vector3& value)
	{
		x *= value.x;
		y *= value.y;
		z *= value.z;
		return *this;
	}
	Vector3& Vector3::operator*=(const float& value)
	{
		x *= value;
		y *= value;
		z *= value;
		return *this;
	}
	Vector3& Vector3::operator/=(const Vector3& value)
	{
		x /= value.x;
		y /= value.y;
		z /= value.z;
		return *this;
	}
	Vector3& Vector3::operator/=(const float& value)
	{
		x /= value;
		y /= value;
		z /= value;
		return *this;
	}

	//!@brief	長さを求める
	//!@return	ベクトルの長さ
	float		Vector3::Length() const
	{
		return sqrtf(x * x + y * y + z * z);
	}
	//!@brief	正規化
	void		Vector3::Normalize()
	{
		float length = Length();
		Vector3	normal;
		x /= length;
		y /= length;
		z /= length;
	}
	//!@brief	正規化
	//!@return	正規化したベクトル
	const Vector3&	Vector3::Normalized()
	{
		Normalize();
		return *this;
	}

	Vector3 operator+(const Vector3& t1, const Vector3& t2)
	{
		return Vector3(t1) += t2;
	}
	Vector3 operator+(const Vector3& t1, const float& t2)
	{
		return Vector3(t1) += t2;
	}
	Vector3 operator-(const Vector3& t1, const Vector3& t2)
	{
		return Vector3(t1) -= t2;
	}
	Vector3 operator-(const Vector3& t1, const float& t2)
	{
		return Vector3(t1) -= t2;
	}
	Vector3 operator*(const Vector3& t1, const Vector3& t2)
	{
		return Vector3(t1) *= t2;
	}
	Vector3 operator*(const Vector3& t1, const float& t2)
	{
		return Vector3(t1) *= t2;
	}
	Vector3 operator/(const Vector3& t1, const Vector3& t2)
	{
		return Vector3(t1) /= t2;
	}
	Vector3 operator/(const Vector3& t1, const float& t2)
	{
		return Vector3(t1) /= t2;
	}



	//----------------------------------------------------------------------------------
	//!@brief		float型の要素4つを持つ
	//----------------------------------------------------------------------------------
	Vector4::Vector4() : DirectX::XMFLOAT4()
	{
	}
	Vector4::Vector4(float x, float y, float z, float w) : DirectX::XMFLOAT4(x, y, z, w)
	{
	}
	Vector4::Vector4(float value) : DirectX::XMFLOAT4(value, value, value, value)
	{
	}
	Vector4::Vector4(const DirectX::XMVECTOR& vector) : DirectX::XMFLOAT4()
	{
		DirectX::XMStoreFloat4(this, vector);
	}
	Vector4& Vector4::operator=(const DirectX::XMVECTOR& vector)
	{
		DirectX::XMStoreFloat4(this, vector);
		return *this;
	}
	Vector4::operator DirectX::XMVECTOR() const
	{
		return DirectX::XMLoadFloat4(this);
	}
	Vector4 Vector4::operator+() const
	{
		return Vector4(this->x, this->y, this->z, this->w);
	}
	Vector4 Vector4::operator-() const
	{
		return Vector4(-this->x, -this->y, -this->z, -this->w);
	}
	Vector4& Vector4::operator=(const Vector4& value)
	{
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;
		return *this;
	}
	Vector4& Vector4::operator=(const float& value)
	{
		x = value;
		y = value;
		z = value;
		w = value;
		return *this;
	}
	Vector4& Vector4::operator+=(const Vector4& value)
	{
		x += value.x;
		y += value.y;
		z += value.z;
		w += value.w;
		return *this;
	}
	Vector4& Vector4::operator+=(const float& value)
	{
		x += value;
		y += value;
		z += value;
		w += value;
		return *this;
	}
	Vector4& Vector4::operator-=(const Vector4& value)
	{
		x -= value.x;
		y -= value.y;
		z -= value.z;
		w -= value.w;
		return *this;
	}
	Vector4& Vector4::operator-=(const float& value)
	{
		x -= value;
		y -= value;
		z -= value;
		w -= value;
		return *this;
	}
	Vector4& Vector4::operator*=(const Vector4& value)
	{
		x *= value.x;
		y *= value.y;
		z *= value.z;
		w *= value.w;
		return *this;
	}
	Vector4& Vector4::operator*=(const float& value)
	{
		x *= value;
		y *= value;
		z *= value;
		w *= value;
		return *this;
	}
	Vector4& Vector4::operator/=(const Vector4& value)
	{
		x /= value.x;
		y /= value.y;
		z /= value.z;
		w /= value.w;
		return *this;
	}
	Vector4& Vector4::operator/=(const float& value)
	{
		x /= value;
		y /= value;
		z /= value;
		w /= value;
		return *this;
	}

	Vector4 operator+(const Vector4& t1, const Vector4& t2)
	{
		return Vector4(t1) += t2;
	}
	Vector4 operator+(const Vector4& t1, const float& t2)
	{
		return Vector4(t1) += t2;
	}
	Vector4 operator-(const Vector4& t1, const Vector4& t2)
	{
		return Vector4(t1) -= t2;
	}
	Vector4 operator-(const Vector4& t1, const float& t2)
	{
		return Vector4(t1) -= t2;
	}
	Vector4 operator*(const Vector4& t1, const Vector4& t2)
	{
		return Vector4(t1) *= t2;
	}
	Vector4 operator*(const Vector4& t1, const float& t2)
	{
		return Vector4(t1) *= t2;
	}
	Vector4 operator/(const Vector4& t1, const Vector4& t2)
	{
		return Vector4(t1) /= t2;
	}
	Vector4 operator/(const Vector4& t1, const float& t2)
	{
		return Vector4(t1) /= t2;
	}


	//----------------------------------------------------------------------------
	//!@brief		頂点データ
	//!@param[in]	位置情報
	//!@param[in]	法線情報
	//!@param[in]	UV情報
	//----------------------------------------------------------------------------
	VertexData::VertexData(Vector3 position, Vector3 normal, Vector2 uv)
	{
		this->position = position;
		this->normal = normal;
		this->uv = uv;
	}
}


namespace Math
{
	//!@brief	2Dベクトル同士の内積
	//!@param[in]	vector1	1つ目のベクトル
	//!@param[in]	vector2	2つ目のベクトル
	//!return	内積の値
	float	Dot2D(const Vector2& vector1, const Vector2& vector2)
	{
		return vector1.x * vector2.x + vector2.y * vector2.y;
	}
	//!@brief	3Dベクトル同士の内積
	//!@param[in]	vector1	1つ目のベクトル
	//!@param[in]	vector2	2つ目のベクトル
	//!@return	内積の値
	float	Dot3D(const Vector3& vector1, const Vector3& vector2)
	{
		return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
	}
	//!@brief	2Dベクトル同士の外積
	//!@param[in]	vector1	1つ目のベクトル
	//!@param[in]	vector2	2つ目のベクトル
	//!@return	外積の値
	float	Cross2D(const Vector2& vector1, const Vector2& vector2)
	{
		return vector1.x * vector2.y - vector1.y * vector2.x;
	}
	//!@brief	3Dベクトル同士の外積
	//!@param[in]	vector1	1つ目のベクトル
	//!@param[in]	vector2	2つ目のベクトル
	//!@return	外積の値
	Vector3&	Cross3D(const Vector3& vector1, const Vector3& vector2)
	{
		Vector3	cross;
		cross.x = vector1.y * vector2.z - vector1.z * vector2.y;
		cross.y = vector1.z * vector2.x - vector1.x * vector2.z;
		cross.z = vector1.x * vector2.y - vector1.y * vector2.x;
		return cross;
	}
	//!@brief	3点からの外積
	//!@param[in]	pos1	1つ目の点座標
	//!@param[in]	pos2	2つ目の点座標
	//!@param[in]	pos3	3つ目の点座標
	//!@return	外積の値
	Vector3&	Cross3D(const Vector3& pos1, const Vector3& pos2, const Vector3& pos3)
	{
		//ベクトルの作成
		Vector3	vector1 = pos2 - pos1;
		Vector3 vector2 = pos3 - pos2;
		//ベクトルから外積を計算
		return Cross3D(vector1, vector2);
	}
	DirectX::XMMATRIX & TransformMatrix(const Math::Vector3 & position)
	{
		return DirectX::XMMatrixTranslation(position.x, position.y, position.z);
	}
	DirectX::XMMATRIX & RotationMatrix(const Math::Vector3 & rotation)
	{
		return DirectX::XMMatrixRotationRollPitchYaw(
			DirectX::XMConvertToRadians(rotation.y),
			DirectX::XMConvertToRadians(rotation.x),
			DirectX::XMConvertToRadians(rotation.z));
	}
	DirectX::XMMATRIX & ScaleMatrix(const Math::Vector3 & scale)
	{
		return DirectX::XMMatrixScaling(scale.x, scale.y, scale.z);
	}

	float Clamp(float x, float minValue, float maxValue)
	{
		return std::min<float>(std::max<float>(x, minValue), maxValue);
	}
	
	float LengthSegmentOnSeparateAxis(const Vector3& sep, const Vector3& e1, const Vector3& e2, const Vector3& e3)
	{
		//3つの内積の絶対値の綿和で投影線分長を計算
		//分離軸Sepは標準化されている
		float r1 = fabs(Dot3D(sep, e1));
		float r2 = fabs(Dot3D(sep, e2));
		float r3 = 0.0f;
		if (e3.x == 0 && e3.y == 0 && e3.z == 0)
		{
			r3 = 0.0f;
		}
		else
		{
			r3 = fabs(Dot3D(sep, e3));
		}
		return r1 + r2 + r3;
	}

	const float	VectorLength(const Vector3& pos1, const Vector3& pos2)
	{
		Vector3 vec = pos2 - pos1;
		return fabsf(vec.Length());
	}
}