
//!@brief	�s�N�Z���V�F�[�_�[
struct PS_INPUT
{
	float4	position	: SV_POSITION;
	float4	color		: COLOR0;
};


//! @brief		�s�N�Z���V�F�[�_�[�̏���
//!	@return		�F
float4 main(PS_INPUT input) : SV_Target
{
	return float4(1,0,0,1);
	return input.color;
}