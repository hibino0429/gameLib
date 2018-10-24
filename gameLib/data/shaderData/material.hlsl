//!	@struct		���͏��
//! @brief		���͏��
//!	@note		D3D11_INPUT_ELEMENT_DESC�Őݒ肷����ƍ��킹��
//!	@note		position�̌���POSITION�̓Z�}���e�B�b�N�ƌĂ΂����̂ł��B
struct VS_INPUT
{
	float4	position : POSITION;
	float4	diffuse : COLOR;
	float3	normal : NORMAL;
};

//!	@struct		�o�͏��
//!	@brief		�o�͏��
struct VS_OUTPUT
{
	float4 position : SV_POSITION;
	float4 color : COLOR0;
	float3	normal : NORMAL;
};

//!@brief	�萔�o�b�t�@
cbuffer ConstantBuf : register(b0)
{
	float4x4		world;
	float4x4		view;
	float4x4		proj;
};



//!@brief	�s�N�Z���V�F�[�_�[
struct PS_INPUT
{
	float4	position	: SV_POSITION;
	float4	color		: COLOR0;
};



//! @brief		���_�V�F�[�_�[�̏���
//!	@param[in]	IN			���͏��
//!	@return		�o�͏��
VS_OUTPUT	VS_main(VS_INPUT input)
{
	VS_OUTPUT OUT = (VS_OUTPUT)0;
	OUT.position = mul(input.position, world);
	OUT.position = mul(OUT.position, view);
	OUT.position = mul(OUT.position, proj);
	OUT.color = input.diffuse;
	OUT.normal = mul(input.normal, (float3x3)world);
	return OUT;
}


//! @brief		�s�N�Z���V�F�[�_�[�̏���
//!	@return		�F
float4	PS_main(PS_INPUT input) : SV_Target
{
	return input.color;
}