//!	@struct		���͏��
//! @brief		���͏��
//!	@note		D3D11_INPUT_ELEMENT_DESC�Őݒ肷����ƍ��킹��
//!	@note		position�̌���POSITION�̓Z�}���e�B�b�N�ƌĂ΂����̂ł��B
struct VS_INPUT
{
	float4	position : POSITION;
	float4	normal	: NORMAL;
};

//!	@struct		�o�͏��
//!	@brief		�o�͏��
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer ConstantBuf : register(b0)
{
	float4x4		world;
	float4x4		view;
	float4x4		proj;
	float4			lightDir;	//���C�g�̕���
	float4			lightColor;	//���C�g�̐F
};

//! @brief		���_�V�F�[�_�[�̏���
//!	@param[in]	IN			���͏��
//!	@return		�o�͏��
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output;
	float3 normal;
	float	color;
	//�ʒu�����[���h��Ԃ�
	output.position = mul(input.position, world);
	output.position = mul(input.position, view);
	output.position = mul(input.position, proj);
	//�@�������[���h��Ԃ�
	normal = mul(input.normal, world).xyz;
	normal = normalize(normal);
	//�@���ƃ��C�g�̕����x�N�g������A�F�̎Z�o
	color = saturate(dot(normal, (float3)lightPos));
	color = color * 0.5f + 0.5f;	//0.5f���v���X���Ă���̂́A���ʂ𖾂邭���邽��

	output.color = float4(color, color, color, 1.0f);
	return output;
}