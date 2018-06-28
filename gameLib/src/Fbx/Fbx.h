#pragma once
#pragma warning(disable : 4005)
#include <fbxsdk.h>

#if defined(_DLL)
#pragma comment(lib,"libfbxsdk-md.lib")
#else 
#pragma comment(lib,"libfbxsdk-mt.lib")
#endif

#include <string>
#include "../../src/Engine/DXEngine/DXEngine.h"
#include "../../src/Math/Math.h"


//-----------------------------------------------------------------------------
//!@brief FBXクラス
//-----------------------------------------------------------------------------
class FbxModel
{
public:
	class Vec3
	{
	public:
		Vec3() {}
		Vec3(float x, float y, float z)
			: x(x), y(y), z(z)
		{}

	public:
		float x;
		float y;
		float z;
	};
public:
	void	LoadFile(const std::string& filePath);
	void	LoadVertexData();
	void	LoadIndexData();

	//!@brief	ノードの探索
	void	ProbeNode(FbxNode* fbxNode);
	//!@brief	指定したノードタイプかのチェック
	bool	CheckNodeType(const FbxNodeAttribute::EType& nodeType);

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

	//概要: 頂点の情報を取得
	void	GetVertexInfo();
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
	Math::Vector4*	vertexPosArray;			//頂点座標 (DirectX用)

private:
	FbxLayer*				normalLayer;		//レイヤー
	FbxLayerElementNormal*	normalElem;			//法線

private:
	FbxLayer*				uvLayer;			//レイヤー
	FbxLayerElementUV*		uvElem;				//UV情報

private:
	FbxNode*				materialNode;	//マテリアルオブジェクト
	FbxSurfaceMaterial*		material;		//マテリアル

private:
	FbxProperty				texProperty;	//ディフューズプロパティ
	FbxTexture*				fbxTexture;		//テクスチャ
	
private:
	FbxNode*				modelNode;		//モデルのノード
	FbxMatrix				modelPos;		//モデルの位置
private:
	int			childNodeNum;	//子ノードの数

	int			polygonNum;			//ポリゴン数
	int			polygonVertexNum;	//ポリゴン頂点インデックス数
	int*		polygonIndexArray;	//ポリゴン頂点インデックス配列
};


//モデルクラス
class Model
{
public:
	Model();
	~Model();

public:
	void	CreateVertex();
	void	CreateIndex();

private:

};



//解説

//FBXManagerは、FBXを取り扱うための管理を行う

//FBXSceneは、FBXファイルに格納されているシーンの情報を保持する

//FBXSceneには、ノードがあり、階層構造で、頂点データ・ライト・アニメーション等の描画に必要な情報がある

//FBXファイルから頂点データを取得

//GetPolygonVertexCount() はインデックスデータの数を取得

//GetPolygonVertices()でインデックスデータそのものを取得