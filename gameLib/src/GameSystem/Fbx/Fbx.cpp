#include "Fbx.h"
#include "../../src/Utility/Utility.hpp"
#include <iostream>

FbxModel::FbxModel(const std::string& filePath)
	: fbxManager(nullptr)
	, scene(nullptr)
	, fbxImporter(nullptr)
	, animStackNumber(0)
{
	fbxManager = FbxManager::Create();
	scene = FbxScene::Create(fbxManager, "fbxScene");
	FbxString fileName(filePath.c_str());
	fbxImporter = FbxImporter::Create(fbxManager, "imp");
	fbxImporter->Initialize(fileName.Buffer(), -1, fbxManager->GetIOSettings());
	fbxImporter->Import(scene);
	fbxImporter->Destroy();

	//ノードタイプがメッシュなら
	if (SearchDesignationNode(FbxNodeAttribute::EType::eMesh))
	{
		//メッシュノードとメッシュを取り入れる
		meshNode = scene->GetRootNode()->GetChild(findNodeTypeNum);
		mesh = scene->GetRootNode()->GetChild(findNodeTypeNum)->GetMesh();
		LoadNodeForMeshNum();
		SetMeshData();
	}
	CreateAnimation();
	CreateAnimationTime();
}

FbxModel::~FbxModel()
{
	mesh->Destroy();
	meshNode->Destroy();
	scene->Destroy();
	fbxManager->Destroy();
	FbxArrayDelete(animStackNameArray);
}

void	FbxModel::LoadFile(const std::string& filePath)
{
	fbxManager = FbxManager::Create();
	scene = FbxScene::Create(fbxManager, "fbxScene");
	FbxString fileName(filePath.c_str());
	fbxImporter = FbxImporter::Create(fbxManager, "imp");
	fbxImporter->Initialize(fileName.Buffer(), -1, fbxManager->GetIOSettings());
	fbxImporter->Import(scene);
	fbxImporter->Destroy();

	//ノードタイプがメッシュなら
	if (SearchDesignationNode(FbxNodeAttribute::EType::eMesh))
	{
		//メッシュノードとメッシュを取り入れる
		meshNode = scene->GetRootNode()->GetChild(findNodeTypeNum);
		mesh = scene->GetRootNode()->GetChild(findNodeTypeNum)->GetMesh();
		LoadNodeForMeshNum();
		SetMeshData();
	}
}



//!@brief	ノードの探索
void	FbxModel::ProbeNode(FbxNode* fbxNode)
{
	if (fbxNode)
	{
		printf(fbxNode->GetName());
		for (int i = 0; fbxNode->GetChildCount() > i; ++i)
		{
			ProbeNode(fbxNode->GetChild(i));
		}
	}
}



//!@brief	頂点数の取得
int			FbxModel::GetVertexDatas()
{
	return this->vertexDataNum;
}
//!@brief	頂点のポリゴン数の取得
int				FbxModel::GetVertexCount()
{
	return this->indexDataNum;
}
//!@brief	頂点データの取得
std::vector<int>&		FbxModel::GetVertexPolygonVertices()
{
	return this->indices;
}



//!@brief	頂点データを渡す
std::vector<Vertex>&		FbxModel::GetVertexData()
{
	return vertexDatas;
}

//!@brief	指定したノードを探す
//!@param[in]	nodeType	探すノード
bool		FbxModel::SearchDesignationNode(const FbxNodeAttribute::EType& nodeType)
{
	//先頭のノードから順番に検索していく
	for (int i = 0; i < scene->GetRootNode()->GetChildCount(); ++i)
	{
		//頂点データが入っているノードを発見したら
		if (scene->GetRootNode()->GetChild(i)->GetNodeAttribute()->GetAttributeType() == nodeType)
		{
			findNodeTypeNum = i;
			return true;
		}
	}
	return false;
}

//!@brief	メッシュの数だけノードの読み込みを行う
void		FbxModel::LoadNodeForMeshNum()
{
	//メッシュの数だけ頂点データを作成する
	//頂点データにメッシュデータを渡す
	for (int meshCnt = 0; meshCnt < mesh->GetControlPointsCount(); ++meshCnt)
	{
		//メッシュの頂点を渡す
		vertexDatas.push_back(
			Vertex(static_cast<float>(mesh->GetControlPointAt(meshCnt)[0]),
				static_cast<float>(mesh->GetControlPointAt(meshCnt)[1]),
				static_cast<float>(mesh->GetControlPointAt(meshCnt)[2])
			)
		);
	}
}


//!@brief	メッシュのデータを受け取る
void		FbxModel::SetMeshData()
{
	vertexDataNum = mesh->GetControlPointsCount();	//頂点数
	indexDataNum = mesh->GetPolygonVertexCount();	//インデックス数
	//インデックスデータ
	for (int cnt = 0; cnt < indexDataNum; ++cnt)
	{
		indices.push_back(mesh->GetPolygonVertices()[cnt]);
	}
}


//!@brief	現在のアニメーション番号の取得
const int&	FbxModel::GetNowAnimationNumber() const
{
	return animStackNumber;
}
//!@brief	現在のアニメーション名の取得
const char*	FbxModel::GetNowAnimationName() const
{
	return animStackNameArray[animStackNumber]->Buffer();
}

////////////////////////////////////////////////////////////
//設定処理
////////////////////////////////////////////////////////////
//!@brief	アニメーション番号の更新
void	FbxModel::SetAnimationNumber(const int& animationNumber)
{
	this->animStackNumber = animationNumber;
}



//!@brief	アニメーションの生成
void	FbxModel::CreateAnimation()
{
	////////////////////////////////////////////////////////
	//利用するアニメーションの選択
	////////////////////////////////////////////////////////
	//FBXファイル内のアニメーション名一覧の取得
	scene->FillAnimStackNameArray(animStackNameArray);
	//選んだアニメーション名を使用して、そのアニメーション情報を探す
	FbxAnimStack*	animationStack = scene->FindMember<FbxAnimStack>(animStackNameArray[animStackNumber]->Buffer());
	//選んだアニメーションを設定する
	scene->SetCurrentAnimationStack(animationStack);
}


//!@brief	アニメーションの時間の生成と設定
void	FbxModel::CreateAnimationTime()
{
	///////////////////////////////////////////////////////
	//アニメーションの実行に必要な時間を扱う設定
	///////////////////////////////////////////////////////
	//FBXから時間情報の取得
	FbxTakeInfo*	takeInfo = scene->GetTakeInfo(*(animStackNameArray[animStackNumber]));
	//開始時間の取得
	start = takeInfo->mLocalTimeSpan.GetStart();
	//終了時間の取得
	stop = takeInfo->mLocalTimeSpan.GetStop();
	//アニメーション(1コマ)が実行される時間情報
	frameTime.SetTime(0, 0, 0, 1, 0, scene->GetGlobalSettings().GetTimeMode());
	//開始からの経過時間
	timeCount = start;
}


//!@brief	アニメーションの行列計算
void	FbxModel::AnimationMatrix()
{
	//アニメーションの時間の更新
	timeCount += frameTime;
	if (timeCount > stop)
	{
		timeCount = start;
	}

	////////////////////////////////////////////////////////////////
	//各フレーム毎の計算に必要なパラメータの取得を行う
	FbxMatrix globalPosition = meshNode->EvaluateGlobalTransform(timeCount);
	
	//行列の作成(移動・回転・拡大)
	FbxVector4	translation = meshNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4	rotation = meshNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4	scale = meshNode->GetGeometricScaling(FbxNode::eSourcePivot);
	//行列のオフセットを求める
	FbxAMatrix	geometryOffset = FbxAMatrix(translation, rotation, scale);


	//////////////////////////////////////////////////////////////
	//全ての頂点にかけ合わせるための計算
	FbxMatrix*	clusterDeformation = new FbxMatrix[mesh->GetControlPointsCount()];
	//0クリア
	std::memset(clusterDeformation, 0, sizeof(FbxMatrix) * mesh->GetControlPointsCount());
	
	//全てのクラスタ情報の取得
	FbxSkin*	skinDeformer = (FbxSkin*)mesh->GetDeformer(0, FbxDeformer::eSkin);
	int clusterCount = skinDeformer->GetClusterCount();

	//クラスタ情報を1つずつ取り出して、クラスタ独自に持つ行列の計算を行う
	for (int clusterIndex = 0; clusterIndex < clusterCount; ++clusterIndex)
	{
		//１つのクラスタ情報の取得
		FbxCluster*	cluster = skinDeformer->GetCluster(clusterIndex);
		FbxMatrix	vertexTransformMatrix;
		
		//--------------------------------計算-------------------------------//
		FbxAMatrix	referenceGlobalInitPostion;				//グローバル空間の初期位置参照
		FbxAMatrix	clusterGlobalInitPostion;				//グローバル空間での初期位置
		FbxMatrix	clusterGlobalCurrentPosition;			//グローバル空間でのクラスタの現在の位置
		FbxMatrix	clusterRelativeInitPosition;			//Childのクラスタの初期位置
		FbxMatrix	clusterRelativeCurrentPositionInverse;	//Childの現在の位置の逆行列

		cluster->GetTransformMatrix(referenceGlobalInitPostion);
		referenceGlobalInitPostion *= geometryOffset;

		cluster->GetTransformLinkMatrix(clusterGlobalInitPostion);
		clusterGlobalCurrentPosition = cluster->GetLink()->EvaluateGlobalTransform(timeCount);
		clusterRelativeInitPosition = clusterGlobalInitPostion.Inverse() * referenceGlobalInitPostion;
		clusterRelativeCurrentPositionInverse = globalPosition.Inverse() * clusterGlobalCurrentPosition;
		vertexTransformMatrix = clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;

		//上記で作成した行列に各頂点ごとの影響度(重み)をかけてそれぞれに加算する
		for(int i = 0; i < cluster->GetControlPointIndicesCount(); ++i)
		{
			//影響を与える頂点番号(インデックス)の取得
			int index = cluster->GetControlPointIndices()[i];
			//頂点(index変数)に与える影響度の数値の取得
			double weight = cluster->GetControlPointWeights()[i];
			//頂点(index変数)に影響を与えるための行列の計算 (クラスタが頂点Ani影響を与える行列 = クラスタが持つ独自行列 * 頂点Aの影響度)
			FbxMatrix influence = vertexTransformMatrix * weight;
			//頂点(index変数)に影響を与えるための行列へ加算 (頂点Aに影響を与える行列 = クラスタ1が頂点Aに影響を与える行列 + クラスタ2が頂点Aに影響を当てる行列 + ...n個)
			clusterDeformation[index] += influence;
		}
	}

	//全ての頂点と、その各頂点に影響を与える行列を掛け合わせ、最終的な座標値を求める
	for (int i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		FbxVector4	outVertex = clusterDeformation[i].MultNormalize(mesh->GetControlPointAt(i));
		vertexDatas[i].x = static_cast<float>(outVertex[0]);
		vertexDatas[i].y = static_cast<float>(outVertex[1]);
		vertexDatas[i].z = static_cast<float>(outVertex[2]);
	}

	//クラスタの削除
	Utility::SafeDeleteArray(clusterDeformation);
}






//概要: SDK全体の管理(マネジャー)クラスを生成
void	FbxModel::CreateManager()
{
	fbxManager = FbxManager::Create();
}
//概要: FBXのインポータを生成
void	FbxModel::CreateImporter()
{
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

//概要: FBXフォーマットのチェック
//戻り値: 成功ならtrue
bool	FbxModel::CheckFormat()
{
	const char* fileName = "sample.fbx";
	int fileFormat = -1;
	if (!plugin->DetectReaderFileFormat(fileName, fileFormat))
	{
		//取得失敗
		return false;
	}
	if (!plugin->DetectWriterFileFormat(fileName, fileFormat))
	{
		return false;
	}

	fbxImporter->Initialize(fileName);
	return true;
}

//概要: FBXファイルの読み込み
//戻り値: 成功ならtrue
bool	FbxModel::LoadFbx(const std::string& fileName)
{
	if(fbxImporter->Initialize(fileName.c_str()))
	{
		return false;
	}
	return true;
}


//概要: オブジェクトの生成
void	FbxModel::CreateObject()
{
	scene = FbxScene::Create(fbxManager, "");	
}
//概要: 情報を受け取る
void	FbxModel::ReciveInfo()
{
	fbxImporter->Import(scene);	//シーンの作成
	fbxImporter->Destroy();
}

//概要: 日本語パスに対応するUTF8フォーマットの絶対パスを取得
void	FbxModel::GetUTF8AbsFilePath(const std::string& filePath, char outAbsFilePath[512])
{
	char fullPath[512];
	_fullpath(fullPath, filePath.c_str(), 512);
	//FBX_ANSI_to_UTF8()マクロ
}




//概要: 子ノードの数の取得
void	FbxModel::GetChildNodeNum()
{
	childNodeNum = rootNode->GetChildCount();
}

//概要: 子ノードの取得
void	FbxModel::GetChildNode()
{
	for (int i = 0; i < childNodeNum; ++i)
	{
		childNode = rootNode->GetChild(i);	//子ノードを取得
	}
}


//概要: ノードのタイプの取得
void	FbxModel::GetNodeAttribute()
{
	nodeAttribute = rootNode->GetNodeAttribute();
	if (nodeAttribute)
	{
		type =  nodeAttribute->GetAttributeType();
		GetMeshObject();
	}
}

//概要: メッシュオブジェクトの取得
void	FbxModel::GetMeshObject()
{
	if (type == FbxNodeAttribute::eMesh)
	{
		//メッシュにダウンキャスト
		mesh = (FbxMesh*)nodeAttribute;
	}
}

//概要: ポリゴンの基本情報の取得
void	FbxModel::GetPolygonInfo()
{
	polygonNum = mesh->GetPolygonCount();
	polygonVertexNum = mesh->GetPolygonVertexCount();
	polygonIndexArray = mesh->GetPolygonVertices();

	for (int p = 0; p < polygonNum; ++p) {
		int indexNumInPolygon = mesh->GetPolygonSize(p);	//p番目のポリゴン頂点数
		for (int n = 0; n < indexNumInPolygon; ++n) {
			//ポリゴンpを構成するn番目の頂点インデックス番号
			int indexNum = mesh->GetPolygonVertex(p, n);
		}
	}
}





//概要: UV情報を取得する
void	FbxModel::GetUVInfo()
{
	
}

//概要: UV座標を取得する
void	FbxModel::GetUVPos()
{
	
}



//概要: マテリアルオブジェクトを取得
void	FbxModel::GetMaterialObject()
{
	
}


//概要: テクスチャ情報の取得
void	FbxModel::GetTexture()
{
	
}

//概要: モデルの位置を取得
void	FbxModel::GetModelPos()
{
	
}