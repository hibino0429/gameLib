
//!@brief	ピクセルシェーダー
struct PS_INPUT
{
	float4	position	: SV_POSITION;
	float4	posWorld	: POSITION;
	float4	normalWorld	: NORMAL;
};

cbuffer ConstantBuffer
{
	float4x4	world;
	float4x4	view;
	float4x4	proj;
	float4		lightPos;			//ライトの位置
	float4		attenuation;		//光源減衰量	
	float4		lightColor;			//ライトの色
};

//! @brief		ピクセルシェーダーの処理
//!	@return		色
float4 main(PS_INPUT input) : SV_Target
{
	float3	dir;
	float	len;
	float	colorDiffuse;
	float	colorAttenuation;
	float	color;

	//点光源の方向
	dir = lightPos.xyz - input.posWorld.xyz;
	//点光源の距離
	len = length(dir);
	//点光源の方向を正規化
	dir = dir / len;
	//拡散
	colorDiffuse = saturate(dot(normalize(input.normalWorld.xyz), dir));
	//減衰
	colorAttenuation = saturate(1.0f / (attenuation.x + attenuation.y * len + attenuation.z * len * len));

	//色の計算
	color = colorDiffuse * colorAttenuation;
	return float4(color, color, color, 1.0f);
}