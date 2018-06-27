//!@brief	定数バッファ(CPU側の値の受け取り場所)
cbuffer ConstantBuf
{
	float4x4		worldMatrix;	//ワールド行列
	float4x4		viewMatrix;		//ビュー行列
	float4x4		projMatrix;		//プロジェクション行列
};

Texture2D		tex : register(t0);				//画像の受け取り
SamplerState	defaultSampler : register(s0);	//サンプラ

struct VS_Input
{
	float4	position : POSITION;
	float2	textureUV : TEXCOORD;
};

//!@brief	頂点シェーダから出力される構造体
struct VS_Output
{
	float4	position : SV_POSITION;
	float2	textureUV : TEXCOORD;
};


//!@brief	頂点シェーダ
VS_Output	VS_main(VS_Input input)
{
	VS_Output output;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projMatrix);
	output.textureUV = input.textureUV;

	return output;
}


//!@brief	ピクセルシェーダ
float4		PS_main(VS_Output input) : SV_Target
{
	return tex.Sample(defaultSampler,input.textureUV);
}

