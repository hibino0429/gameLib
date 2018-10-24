
//!@brief	定数バッファ(CPU側の値の受け取り場所)
cbuffer ConstantBuf
{
	float4x4		worldMatrix;	//ワールド行列
	float4x4		viewMatrix;		//ビュー行列
	float4x4		projMatrix;		//プロジェクション行列
	float4			lightDirection;	//ライトの向き
	float4			lightColor;		//ライトの色
};

Texture2D		tex : register(t0);				//画像の受け取り
SamplerState	defaultSampler : register(s0);	//サンプラ

struct VS_Input
{
	float4	position : POSITION;
	float4	diffuse	: COLOR;
	float2	textureUV : TEXCOORD;
	float3	normal : NORMAL;
};

//!@brief	頂点シェーダから出力される構造体
struct VS_Output
{
	float4	position : SV_POSITION;
	float4	diffuse	: COLOR0;
	float2	textureUV : TEXCOORD;
	float3	normal : NORMAL0;
};


//!@brief	頂点シェーダ
VS_Output	VS_main(VS_Input input)
{
	VS_Output output;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projMatrix);
	output.textureUV = input.textureUV;
	output.diffuse = input.diffuse;
	output.normal = mul(input.normal, (float3x3)worldMatrix);

	return output;
}


//!@brief	ピクセルシェーダ
float4		PS_main(VS_Output input) : SV_Target
{
	float3	normal = normalize(input.normal);							//正規化
	float3	lightDir = normalize(lightDirection.xyz);					//正規化
	float4	diffuseColor = tex.Sample(defaultSampler, input.textureUV);	//拡散光
	float3	diffuseIntensity = dot(-lightDir, normal) * lightColor.xyz;	//拡散光強さ
	float3	ambientIntensity = lightColor.xyz * 2.0f;					//環境光
	return diffuseColor * float4(diffuseIntensity + ambientIntensity, 1.0f);
}

