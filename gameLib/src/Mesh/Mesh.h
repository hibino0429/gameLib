#pragma once
#include <vector>
#include "../../src/Device/DXDevice/DXDevice.h"
#include "../../src/Math/Math.h"
#include "../../src/Material/Material.h"

//-------------------------------------------------------------------
//!@class		Mesh
//!@brief	ポリゴンの集合クラス
//-------------------------------------------------------------------
class Mesh
{
private:
	//!@brief	定数バッファの定義
	struct Constant
	{
		DirectX::XMMATRIX	worldMat;
	};

public:
	//!@brief	コンストラクタ
	Mesh();
	//!@brief	デストラクタ
	~Mesh();

	//!@brief	平面の作成
	//!@param[in]	ポリゴンの大きさ
	//!@param[in]	ポリゴンのオフセット位置
	//!@param[in]	頂点・インデックスの初期化フラグ
	//!@param[in]	左方向の向き
	//!@param[in]	上方向の向き
	//!@param[in]	法線の向き
	void	CreatePlane(
		Math::Vector2 size,
		Math::Vector3 offset = Math::Vector3(0.0f, 0.0f, 0.0f),
		bool		 shoudClear = true,
		Math::Vector3 leftDir = Math::Vector3(1.0f, 0.0f, 0.0f),
		Math::Vector3 upDir = Math::Vector3(0.0f, 1.0f, 0.0f),
		Math::Vector3 forwardDir = Math::Vector3(0.0f, 0.0f, 1.0f)
	);

	//!@brief	四面体の作成
	//!@param[in]	頂点・インデックスの初期化フラグ
	void	CreateCube(bool	shoudClear = true);

	//!@brief	ポイントの作成
	//!@param[in]	pos	ポイント位置
	//!@param[in]	offset	オフセット
	//!@param[in]	forwardDir	方向
	//!@param[in]	shoudClear	頂点・インデックスの初期化フラグ
	void	CreatePoint(
		const Math::Vector3& pos,
		const Math::Vector3& offset,
		const Math::Vector3& forwardDir,
		bool	shoudClear);

	//!@brief	マテリアルの取得
	//!@return マテリアル
	Material&	GetMaterial();

	//!@brief	位置の設定
	//!@param[in]	pos	位置
	void	SetPos(const Math::Vector3& pos);
	//!@brief	角度の設定
	//!@param[in]	angle	角度
	void	SetAngle(const Math::Vector3& angle);
	//!@brief	スケールの設定
	//!@param[in]	scale	スケール
	void	SetScale(const Math::Vector3& scale);
	
	//!@brief	カリングモードの設定
	//!@param[in]	カリングの設定
	void	SetCullingMode(D3D11_CULL_MODE cullingMode);

	//!@brief	変更点を適応させる
	void	Apply();

	//!@brief	位置・回転・スケールの設定
	//!@param[in]	pos_		位置
	//!@param[in]	rotation_	回転
	//!@param[in]	scale_		スケール
	void	SetParams(const Math::Vector3& pos_, const Math::Vector3& rotation_, const Math::Vector3& scale_);

	//!@brief	描画する
	void	Draw();
	//!@brief	ポイントを描画する
	void	DrawPoint();

	void*	operator new(size_t i)
	{
		return _mm_malloc(i, 16);
	}
	void	operator delete(void* p)
	{
		_mm_free(p);
	}

private:
	Constant				constantBuf;		//定数バッファ
	ID3D11Buffer*			vertexBuf;			//頂点バッファ
	ID3D11Buffer*			indexBuf;			//インデックスバッファ
	ID3D11RasterizerState*	rasterizerState;	//ラスタライザステート

	std::vector<Math::VertexData>	vertices;		//頂点データ
	std::vector<UINT>				indices;		//インデックスデータ

	Material			material;
	Math::Vector3		position;
	Math::Vector3		angle;
	Math::Vector3		scale;
};