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
	float4 color : COLOR;
};

//!@brief	ピクセルシェーダー
struct PS_INPUT
{
	float4	position	: SV_POSITION;
	float4	color		: COLOR0;
};



cbuffer ConstantBuf : register(b0)
{
	float4x4		world;
	float4x4		view;
	float4x4		proj;
	float4			lightDir;	//ライトの方向
	float4			lightColor;	//ライトの色
};





//! @brief		頂点シェーダーの処理
//!	@param[in]	IN			入力情報
//!	@return		出力情報
VS_OUTPUT VS_main(VS_INPUT input)
{
	VS_OUTPUT output;
	float	normal;
	float	color;
	//位置をワールド空間へ
	output.position = mul(input.position, world);
	output.position = mul(input.position, view);
	output.position = mul(input.position, proj);
	//法線をワールド空間へ
	normal = mul(input.normal, world).xyz;
	normal = normalize(normal);
	//法線とライトの方向ベクトルから、色の算出
	color = saturate(dot(normal, (float3)lightDir));
	color = color * 0.5f + 0.5f;	//0.5fをプラスしているのは、裏面を明るくするため

	output.color = float4(color, color, color + 0.5f, 1.0f);
	return output;
}


//! @brief		ピクセルシェーダーの処理
//!	@return		色
float4 PS_main(PS_INPUT input) : SV_Target
{
	return input.color;
}