
//!@brief	ピクセルシェーダー
struct PS_INPUT
{
	float4	position	: SV_POSITION;
	float4	color		: COLOR0;
};


//! @brief		ピクセルシェーダーの処理
//!	@return		色
float4 main(PS_INPUT input) : SV_Target
{
	return float4(1,0,0,1);
	return input.color;
}