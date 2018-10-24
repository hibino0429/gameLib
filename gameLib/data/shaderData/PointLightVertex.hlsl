//!	@struct		入力情報
//! @brief		入力情報
//!	@note		D3D11_INPUT_ELEMENT_DESCで設定する情報と合わせる
//!	@note		positionの後ろのPOSITIONはセマンティックと呼ばれるものです。
struct VS_INPUT
{
	float4	position : POSITION;
	float4	normal	: NORMAL;
};

//!	@struct		出力情報
//!	@brief		出力情報
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 posWorld : POSITION;
	float4 normalWorld : NORMAL;
};

cbuffer ConstantBuf : register(b0)
{
	float4x4		world;
	float4x4		view;
	float4x4		proj;			
	float4			lightPos;		//ライト位置
	float4			attenuation;	//光源減数パラメータ
};

//! @brief		頂点シェーダーの処理
//!	@param[in]	IN			入力情報
//!	@return		出力情報
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float3	normal;
	float	color;
	
	//位置をワールド空間へ
	output.posWorld = mul(input.position, world);
	output.posWorld = mul(output.posWorld, view);
	output.posWorld = mul(output.posWorld, proj);
	//法線をワールド空間へ
	output.normalWorld = mul(input.normal, world);

	return output;
}