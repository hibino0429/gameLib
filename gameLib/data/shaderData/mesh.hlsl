
//!@brief	�萔�o�b�t�@(CPU���̒l�̎󂯎��ꏊ)
cbuffer ConstantBuf
{
	float4x4		worldMatrix;	//���[���h�s��
	float4x4		viewMatrix;		//�r���[�s��
	float4x4		projMatrix;		//�v���W�F�N�V�����s��
	float4			lightDirection;	//���C�g�̌���
	float4			lightColor;		//���C�g�̐F
};

Texture2D		tex : register(t0);				//�摜�̎󂯎��
SamplerState	defaultSampler : register(s0);	//�T���v��

struct VS_Input
{
	float4	position : POSITION;
	float4	diffuse	: COLOR;
	float2	textureUV : TEXCOORD;
	float3	normal : NORMAL;
};

//!@brief	���_�V�F�[�_����o�͂����\����
struct VS_Output
{
	float4	position : SV_POSITION;
	float4	diffuse	: COLOR0;
	float2	textureUV : TEXCOORD;
	float3	normal : NORMAL0;
};


//!@brief	���_�V�F�[�_
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


//!@brief	�s�N�Z���V�F�[�_
float4		PS_main(VS_Output input) : SV_Target
{
	float3	normal = normalize(input.normal);							//���K��
	float3	lightDir = normalize(lightDirection.xyz);					//���K��
	float4	diffuseColor = tex.Sample(defaultSampler, input.textureUV);	//�g�U��
	float3	diffuseIntensity = dot(-lightDir, normal) * lightColor.xyz;	//�g�U������
	float3	ambientIntensity = lightColor.xyz * 2.0f;					//����
	return diffuseColor * float4(diffuseIntensity + ambientIntensity, 1.0f);
}

