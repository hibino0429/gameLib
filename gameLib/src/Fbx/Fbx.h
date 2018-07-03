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
#include "../../src/Vertex/Vertex.h"

//-----------------------------------------------------------------------------
//!@brief FBXクラス
//-----------------------------------------------------------------------------
class FbxModel
{
public:
	FbxModel(const std::string& filePath);
	~FbxModel();
	void	LoadFile(const std::string& filePath);

private:
	//!@brief	ノードの探索
	void		ProbeNode(FbxNode* fbxNode);
public:
	//!@brief	頂点データのコントロールポイント数の取得
	int			GetVertexDatas();
	//!@brief	頂点データのポリゴン数の取得
	int			GetVertexCount();
	//!@brief	頂点データの取得
	std::vector<int>&		GetVertexPolygonVertices();
	
	//!@brief	頂点データを渡す
	std::vector<Vertex>&		GetVertexData();

private:
	//!@brief	指定したノードを探す
	//!@param[in]	nodeType	探すノード
	//!@return	見つかったら true 見つからなかったら　false
	bool		SearchDesignationNode(const FbxNodeAttribute::EType& nodeType);
	//!@brief	メッシュの数だけノードの読み込みを行う
	void		LoadNodeForMeshNum();
	//!@brief	メッシュのデータを受け取る
	void		SetMeshData();

private:
	//!@brief	アニメーションの生成
	void	CreateAnimation();
	//!@brief	アニメーションの時間の生成と設定
	void	CreateAnimationTime();
	//!@brief	アニメーションの行列計算
	void	AnimationMatrix();

private:
	//概要: SDK全体の管理(マネジャー)クラスを生成
	void	CreateManager();
	//概要: FBXのインポータを生成
	void	CreateImporter();
	//概要: FBXフォーマットのチェック
	//戻り値: 成功ならtrue
	bool	CheckFormat();
	//概要: FBXファイルの読み込み
	//戻り値: 成功ならtrue
	bool	LoadFbx(const std::string& fileName);
	//概要: オブジェクトの生成
	void	CreateObject();
	//概要: 情報を受け取る
	void	ReciveInfo();
	//概要: 日本語パスに対応するUTF8フォーマットの絶対パスを取得
	void	GetUTF8AbsFilePath(const std::string& filePath, char outAbsFilePath[512]);

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

	//概要: メッシュの法線の取得
	void	GetMeshNormal();

	//概要: 法線ベクトルの方式を取得
	void	GetNormalMethod();

	//概要: UV情報を取得する
	void	GetUVInfo();
	//概要: UV座標を取得する
	void	GetUVPos();

	//概要: マテリアルオブジェクトを取得
	void	GetMaterialObject();
	//概要: テクスチャ情報の取得
	void	GetTexture();

	//概要: モデルの位置を取得
	void	GetModelPos();

private:
	FbxManager*				fbxManager;		//SDKコアクラス
	FbxImporter*			fbxImporter;	//インポータ
	FbxIOPluginRegistry*	plugin;	//プラグイン
	FbxScene*				scene;		//シーン

	FbxNode*				rootNode;	//ルートノード
	FbxNode*				childNode;	//子ノード

	FbxNodeAttribute*		nodeAttribute;	//ノードタイプ
	FbxNodeAttribute::EType type;		//ノードの種類

	FbxMesh*			 mesh;		//メッシュ


private:
	int				controlNum;				//頂点数
	FbxVector4*		src;					//頂点座標配列 (fbx用)
private:
	FbxLayer*				normalLayer;		//レイヤー
	FbxLayerElementNormal*	normalElem;			//法線


private:
	int			childNodeNum;	//子ノードの数

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
	int			vertexDataNum;	//頂点データの数
	int			indexDataNum;	//インデックスデータの数
};





//解説

//FBXManagerは、FBXを取り扱うための管理を行う

//FBXSceneは、FBXファイルに格納されているシーンの情報を保持する

//FBXSceneには、ノードがあり、階層構造で、頂点データ・ライト・アニメーション等の描画に必要な情報がある

//FBXファイルから頂点データを取得

//GetPolygonVertexCount() はインデックスデータの数を取得

//GetPolygonVertices()でインデックスデータそのものを取得