#pragma once
#pragma warning(disable : 4005)
#include <fbxsdk.h>

#if defined(_DLL)
#pragma comment(lib,"libfbxsdk-md.lib")
#else 
#pragma comment(lib,"libfbxsdk-mt.lib")
#endif

#include <string>
#include <vector>
#include "../../src/DXEngine/Vertex/Vertex.h"



//-----------------------------------------------------------------------------
//!@brief FBXクラス
//-----------------------------------------------------------------------------
class FbxModel
{
public:
	FbxModel(const std::string& filePath);
	~FbxModel();
private:
	void	LoadFile(const std::string& filePath);
public:
	//!@brief	頂点の数の取得
	int			GetVertexDatas();
	//!@brief	頂点データのポリゴン数の取得
	int			GetVertexCount();
	//!@brief	ポリゴン数の取得
	int			GetPolygonCount();
	//!@brief	頂点データの取得
	std::vector<int>&		GetVertexPolygonVertices();
	//!@brief	頂点データを渡す
	std::vector<Vertex>&		GetVertexData();

public:
	////////////////////////////////////////////////////////////
	//取得処理
	////////////////////////////////////////////////////////////
	//!@brief	現在のアニメーション番号の取得
	const int&	GetNowAnimationNumber() const;
	//!@brief	現在のアニメーション名の取得
	const char*	GetNowAnimationName() const;

	////////////////////////////////////////////////////////////
	//設定処理
	////////////////////////////////////////////////////////////
	//!@brief	アニメーション番号の設定
	void	SetAnimationNumber(const int& animationNumber);

private:
	//!@brief	指定したノードを探す
	//!@param[in]	nodeType	探すノード
	//!@return	見つかったら true 見つからなかったら　false
	bool		SearchDesignationNode(const FbxNodeAttribute::EType& nodeType);
	//!@brief	メッシュの数だけノードの読み込みを行う
	void		LoadNodeForMeshNum();
	//!@brief	メッシュのデータを受け取る
	void		SetMeshData();
	//!@brief	モデルの色をセットする
public:
	void		SetVertexColor(const float red, const float green, const float blue, const float alpha);
public:
	//!@brief	アニメーションの生成
	void	CreateAnimation();
	//!@brief	アニメーションの時間の生成と設定
	void	CreateAnimationTime();
	//!@brief	アニメーションの行列計算
	void	AnimationMatrix();

private:
	//概要: FBXファイルの読み込み
	//戻り値: 成功ならtrue
	bool	LoadFbx(const std::string& fileName);

	//概要: 子ノードの数の取得
	void	GetChildNodeNum();
	//概要: 子ノードの取得
	void	GetChildNode();

	//概要: ノードのタイプの取得
	void	GetNodeAttribute();

	//概要: メッシュオブジェクトの取得
	void	GetMeshObject();
	//概要: ポリゴンの基本情報の取得
	void	GetPolygonInfo();

public:
	//!@brief	モデルのアニメーションがあるかチェック
	//!@return	true: ある false: なし
	bool	IsAnimation();

private:
	//!@brief	FBXから法線情報の格納
	bool	StoreMeshNormal();
	//!@brief	FBXからUV情報の格納
	bool	StoreMeshUV();
	//!@brief	FBXからマテリアル情報の格納
	bool	StoreMeshMaterial();
	//!@brief	取得したMeshデータをVertexに渡す
	void	PassMeshData();
	//!@brief	取得したMeshのUV情報を保存
	void	SaveMeshUV(const int num);
	//!@brief	取得したMeshのマテリアル情報を保存
	void	SaveMeshMaterial(const int num);
	//!@brief	取得したMeshの法線情報を保存
	void	SaveMeshNormal(const int num);
	//!@brief	テクスチャ名の取得
	void	SaveTextureNames();
	//!@brief	クラスタの格納
	void	SaveCluster();
	//!@brief	ボーンが影響を与える頂点情報の格納
	void	SaveBoneVertexData(FbxCluster* cluster, FbxMatrix* globalPosition, FbxAMatrix* geometryOffset, FbxMatrix* clusterDeformation);

private:
	//マテリアル
	//!@brief	マテリアル情報の格納
	void	SaveMaterialData(FbxSurfaceMaterial* material, const int materialNum);
	//!@brief	Lmbert情報の格納
	void	SaveLambertData(FbxSurfaceLambert* lambert,const int materialNum);
	//!@brief	Phong情報の格納
	void	SavePhongData(FbxSurfacePhong* phong,const int materialNum);
	//!@brief	Texture情報の格納
	void	SaveTextureData(FbxSurfaceMaterial* material,const int materialNum);
private:
	//情報の取得
	//!@brief	情報取得のオプション
	//!@return	true: 頂点単位 false: ポリゴン単位
	bool	GetOption();
	//!@brief	頂点単位で情報を取得する
	void	SaveVertexData();
	//!@brief	ポリゴン探知で情報を取得する
	void	SavePolygonData();
	//!@brief	メッシュデータの取得
	void	LoadMeshData();
private:
	FbxManager*				fbxManager;		//SDKコアクラス
	FbxImporter*			fbxImporter;	//インポータ
	FbxIOPluginRegistry*	plugin;			//プラグイン
	FbxScene*				scene;			//シーン
	FbxNode*				rootNode;		//ルートノード
	FbxNode*				childNode;		//子ノード
	FbxNodeAttribute*		nodeAttribute;	//ノードタイプ
	FbxNodeAttribute::EType type;			//ノードの種類
	FbxMesh*				mesh;			//メッシュ

private:
	int			childNodeNum;		//子ノードの数

	int			polygonNum;			//ポリゴン数
	int			polygonVertexNum;	//ポリゴン頂点インデックス数
	int*		polygonIndexArray;	//ポリゴン頂点インデックス配列

	int			findNodeTypeNum;	//ノードタイプが見つかった時の番号

	FbxNode*	meshNode;
	FbxArray<FbxString*>	animStackNameArray;
	int			animStackNumber;
	FbxTime		frameTime;
	FbxTime		timeCount;
	FbxTime		start;
	FbxTime		stop;

	//-------------------------------------------------------
	//FBXデータを外部に送る用の変数
	//-------------------------------------------------------
	std::vector<Vertex>	vertexDatas;	//頂点データ
	std::vector<int>	indices;		//インデックスデータ
	int			vertexDataNum;			//頂点データの数
	int			indexDataNum;			//インデックスデータの数
	std::vector<ColorData>	colorDatas;	//色データ
};





//解説

//FBXManagerは、FBXを取り扱うための管理を行う

//FBXSceneは、FBXファイルに格納されているシーンの情報を保持する

//FBXSceneには、ノードがあり、階層構造で、頂点データ・ライト・アニメーション等の描画に必要な情報がある

//FBXファイルから頂点データを取得

//GetPolygonVertexCount() はインデックスデータの数を取得

//GetPolygonVertices()でインデックスデータそのものを取得



//------------------
//Node
//------------------
//Nodeの中にさらに、Meshがあり、その中に、頂点情報が含まれている
//Node1のMeshにはモデルの顔データ、Node2のMeshには服のデータ、のように複数のノードが格納される

//注意、インデックスを使用する際、1つの頂点にUV座標が2つ以上ある場合がある
//1: インデックスを使用しない
//2: UVに合わせてインデックスを作り直す color[1] = 1.0f - uvの色
//3: そのまま別のバッファとする


//------------------
//Material
//------------------
//Material、マテリアルの情報は複数ある
//1つのモデルのポリゴングループにマテリアル番号0、別のポリゴングループにマテリアル番号1

