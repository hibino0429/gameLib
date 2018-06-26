//!	@struct		入力情報
//! @brief		入力情報
//!	@note		D3D11_INPUT_ELEMENT_DESCで設定する情報と合わせる
//!	@note		positionの後ろのPOSITIONはセマンティックと呼ばれるものです。
struct VS_INPUT
{
	float4	position : POSITION;
	float4	color : COLOR0;
};

//!	@struct		出力情報
//!	@brief		出力情報
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

cbuffer ConstantBuf : register(b0)
{
	float4x4		world;
	float4x4		view;
	float4x4		proj;
};

//! @brief		頂点シェーダーの処理
//!	@param[in]	IN			入力情報
//!	@return		出力情報
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT OUT = (VS_OUTPUT)0;
	OUT.position = mul(input.position, world);
	OUT.position = mul(OUT.position, view);
	OUT.position = mul(OUT.position, proj);
	OUT.color = input.color;
	return OUT;
}