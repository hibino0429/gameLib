#include "Math.h"


namespace Math
{
	//------------------------------------------------------------------------------
	//!@brief		floatŒ^‚Ì—v‘f2‚Â‚ðŽ‚Â
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
	//!@brief		floatŒ^‚Ì—v‘f3‚Â‚ðŽ‚Â
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
	//!@brief		floatŒ^‚Ì—v‘f4‚Â‚ðŽ‚Â
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
	//!@brief		’¸“_ƒf[ƒ^
	//!@param[in]	ˆÊ’uî•ñ
	//!@param[in]	–@üî•ñ
	//!@param[in]	UVî•ñ
	//----------------------------------------------------------------------------
	VertexData::VertexData(Vector3 position, Vector3 normal, Vector2 uv)
	{
		this->position = position;
		this->normal = normal;
		this->uv = uv;
	}
}