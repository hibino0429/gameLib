#include "AnimationData.h"

//!@brief	コンストラクタ
AnimationData::AnimationData()
	: animationNumber(0)
	, animationName("")
{

}
//!@brief	コンストラクタ
//!@param[in]	animationNumber	アニメーション番号
//!@param[in]	animationName	アニメーション名
AnimationData::AnimationData(const int& animationNumber, const char* animationName)
	: animationNumber(animationNumber)
	, animationName(animationName)
{

}
//!@brief	デストラクタ
AnimationData::~AnimationData()
{

}

/////////////////////////////////////////////////
//取得処理
/////////////////////////////////////////////////
//!@brief	アニメーション番号の取得
const int&	AnimationData::GetAnimationNumber() const
{
	return animationNumber;
}
//!@brief	アニメーション名の取得
const std::string&	AnimationData::GetAnimationName() const
{
	return animationName;
}

/////////////////////////////////////////////////
//設定処理
/////////////////////////////////////////////////
//!@brief	アニメーション番号設定
//!@param[in]	animationNumber	アニメーション番号
void	AnimationData::SetAnimationNumber(const int& animationNumber)
{
	this->animationNumber = animationNumber;
}
//!@brief	アニメーション名の設定
//!@param[in]	animationName	アニメーション名
void	AnimationData::SetAnimationName(const char* animationName)
{
	this->animationName = animationName;
}

//!@brief	番号と名前の出力
void	AnimationData::Output()
{
	std::cout << "アニメーション番号[ " << animationNumber << " ]" << " : "
		<< "アニメーション名:" << animationName << std::endl;
}