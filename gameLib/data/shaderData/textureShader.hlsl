//!@brief	�萔�o�b�t�@(CPU���̒l�̎󂯎��ꏊ)
cbuffer ConstantBuf
{
	float4x4		worldMatrix;	//���[���h�s��
	float4x4		viewMatrix;		//�r���[�s��
	float4x4		projMatrix;		//�v���W�F�N�V�����s��
};

Texture2D		tex : register(t0);				//�摜�̎󂯎��
SamplerState	defaultSampler : register(s0);	//�T���v��

struct VS_Input
{
	float4	position : POSITION;
	float2	textureUV : TEXCOORD;
};

//!@brief	���_�V�F�[�_����o�͂����\����
struct VS_Output
{
	float4	position : SV_POSITION;
	float2	textureUV : TEXCOORD;
};


//!@brief	���_�V�F�[�_
VS_Output	VS_main(VS_Input input)
{
	VS_Output output;
	output.position = mul(input.position, worldMatrix);
	output.position = mul(output.position, viewMatrix);
	output.position = mul(output.position, projMatrix);
	output.textureUV = input.textureUV;

	return output;
}


//!@brief	�s�N�Z���V�F�[�_
float4		PS_main(VS_Output input) : SV_Target
{
	return tex.Sample(defaultSampler,input.textureUV);
}

