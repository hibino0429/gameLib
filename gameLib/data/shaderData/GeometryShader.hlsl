//!	@struct		���͏��
//! @brief		���͏��
//!	@note		D3D11_INPUT_ELEMENT_DESC�Őݒ肷����ƍ��킹��
//!	@note		position�̌���POSITION�̓Z�}���e�B�b�N�ƌĂ΂����̂ł��B
struct VS_INPUT
{
	float3	position : POSITION;
	float4	color : COLOR0;
};

//!	@struct		�o�͏��
//!	@brief		�o�͏��
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

cbuffer ConstantBuf : register(b0)
{
	float4x4	world;
	float4x4	view;
	float4x4	projection;
};

//! @brief		���_�V�F�[�_�[�̏���
//!	@param[in]	IN			���͏��
//!	@return		�o�͏��
VS_OUTPUT main(VS_INPUT IN)
{
	VS_OUTPUT OUT = (VS_OUTPUT)0;
	OUT.position = mul(world, IN.position);
	OUT.position = mul(view, OUT.position);
	OUT.position = mul(projection, OUT.position);
	OUT.color = IN.color;
	return OUT;
}