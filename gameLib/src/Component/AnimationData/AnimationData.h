#pragma once
#include <string>
#include <iostream>

//-------------------------------------------------------------
//!@class		AnimationData
//!@brief	アニメーションのデータを保持します
//-------------------------------------------------------------
class AnimationData
{
public:
	//!@brief	コンストラクタ
	AnimationData();
	//!@brief	コンストラクタ
	//!@param[in]	animationNumber	アニメーション番号
	//!@param[in]	animationName	アニメーション名
	AnimationData(const int& animationNumber, const char* animationName);
	//!@brief	デストラクタ
	~AnimationData();

public:
	/////////////////////////////////////////////////
	//取得処理
	/////////////////////////////////////////////////
	//!@brief	アニメーション番号の取得
	const int&	GetAnimationNumber() const;
	//!@brief	アニメーション名の取得
	const std::string&	GetAnimationName() const;

public:
	/////////////////////////////////////////////////
	//設定処理
	/////////////////////////////////////////////////
	//!@brief	アニメーション番号設定
	//!@param[in]	animationNumber	アニメーション番号
	void	SetAnimationNumber(const int& animationNumber);
	//!@brief	アニメーション名の設定
	//!@param[in]	animationName	アニメーション名
	void	SetAnimationName(const char* animationName);

public:
	//!@brief	番号と名前の出力
	void	Output();

private:
	int			animationNumber;	//アニメーション番号
	std::string	animationName;		//アニメーション名
};

