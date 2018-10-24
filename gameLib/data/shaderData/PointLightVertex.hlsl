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
	float4 posWorld : POSITION;
	float4 normalWorld : NORMAL;
};

cbuffer ConstantBuf : register(b0)
{
	float4x4		world;
	float4x4		view;
	float4x4		proj;			
	float4			lightPos;		//���C�g�ʒu
	float4			attenuation;	//���������p�����[�^
};

//! @brief		���_�V�F�[�_�[�̏���
//!	@param[in]	IN			���͏��
//!	@return		�o�͏��
VS_OUTPUT main(VS_INPUT input)
{
	VS_OUTPUT output = (VS_OUTPUT)0;
	float3	normal;
	float	color;
	
	//�ʒu�����[���h��Ԃ�
	output.posWorld = mul(input.position, world);
	output.posWorld = mul(output.posWorld, view);
	output.posWorld = mul(output.posWorld, proj);
	//�@�������[���h��Ԃ�
	output.normalWorld = mul(input.normal, world);

	return output;
}