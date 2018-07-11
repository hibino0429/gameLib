
//!@brief	�s�N�Z���V�F�[�_�[
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
	float4		lightPos;			//���C�g�̈ʒu
	float4		attenuation;		//����������	
	float4		lightColor;			//���C�g�̐F
};

//! @brief		�s�N�Z���V�F�[�_�[�̏���
//!	@return		�F
float4 main(PS_INPUT input) : SV_Target
{
	float3	dir;
	float	len;
	float	colorDiffuse;
	float	colorAttenuation;
	float	color;

	//�_�����̕���
	dir = lightPos.xyz - input.posWorld.xyz;
	//�_�����̋���
	len = length(dir);
	//�_�����̕����𐳋K��
	dir = dir / len;
	//�g�U
	colorDiffuse = saturate(dot(normalize(input.normalWorld.xyz), dir));
	//����
	colorAttenuation = saturate(1.0f / (attenuation.x + attenuation.y * len + attenuation.z * len * len));

	//�F�̌v�Z
	color = colorDiffuse * colorAttenuation;
	return float4(color, color, color, 1.0f);
}