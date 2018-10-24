#include "Fbx.h"
#include "../../src/Utility/Utility.hpp"
#include <iostream>

FbxModel::FbxModel(const std::string& filePath)
	: fbxManager(nullptr)
	, scene(nullptr)
	, fbxImporter(nullptr)
	, animStackNumber(0)
{
	LoadFile(filePath);
}

FbxModel::~FbxModel()
{
	if (mesh != nullptr)
	{
		mesh->Destroy();
	}
	if (meshNode != nullptr)
	{
		meshNode->Destroy();
	}
	if (scene != nullptr)
	{
		scene->Destroy();
	}
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

	animStackNameArray.Clear();

	//三角ポリゴン化
	FbxGeometryConverter	geometryConverter(fbxManager);
	geometryConverter.Triangulate(scene, true);

	//ノードタイプがメッシュなら
	if (SearchDesignationNode(FbxNodeAttribute::EType::eMesh))
	{
		//メッシュノードとメッシュを取り入れる
		meshNode = scene->GetRootNode()->GetChild(findNodeTypeNum);
		mesh = scene->GetRootNode()->GetChild(findNodeTypeNum)->GetMesh();
		LoadMeshData();
		//LoadNodeForMeshNum();
		//SetMeshData();
	}
	CreateAnimation();
	CreateAnimationTime();
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
		if (scene->GetRootNode()->GetChild(i)->GetNodeAttribute() == nullptr)
		{
			std::cout << "NULL Node Attribute" << std::endl;
			return false;
		}
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

void FbxModel::SetVertexColor(const float red, const float green, const float blue, const float alpha)
{
	for (int i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		vertexDatas[i].diffuse.x = red;
		vertexDatas[i].diffuse.y = green;
		vertexDatas[i].diffuse.z = blue;
		vertexDatas[i].diffuse.w = alpha;
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
	if (animStackNameArray.Size() == 0) { return ""; }
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
	if (animStackNameArray.Size() == 0) { return; }
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
	if (animStackNameArray.Size() == 0) { return; }
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
	SaveCluster();
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



bool FbxModel::IsAnimation()
{
	if (animStackNameArray.Size() == 0) { return false; }
	if (*animStackNameArray.GetFirst() == FbxString("Default Take"))
	{
		return false;
	}
	return true;
}

bool FbxModel::StoreMeshNormal()
{
	if (mesh->GetElementNormal() == nullptr) { return false; }
	if (mesh->GetElementNormal()->GetMappingMode() != FbxLayerElement::EMappingMode::eByControlPoint)
	{
		return false;
	}
	return true;
}

bool FbxModel::StoreMeshUV()
{
	if (mesh->GetElementUV() == nullptr) { return false; }
	if (mesh->GetElementUV()->GetMappingMode() != FbxLayerElement::EMappingMode::eByControlPoint)
	{
		return false;
	}
	return true;
}

bool FbxModel::StoreMeshMaterial()
{
	if (mesh->GetElementMaterial() == nullptr) { return false; }
	if (mesh->GetElementMaterial()->GetMappingMode() != FbxLayerElement::EMappingMode::eByControlPoint)
	{
		return false;
	}
	return true;
}

void FbxModel::PassMeshData()
{
	for (int i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		SaveMeshNormal(i);
		SaveMeshUV(i);
		SaveMeshMaterial(i);
		
		for (unsigned int num = 0; num < colorDatas.size(); ++num)
		{
			//アンビエント
			for (int j = 0; j < 3; ++j)
			{
				//vertexDatas[i].colorData.lambert.ambient[j] = colorDatas[num].lambert.ambient[j];
			}
			//ディフューズ
			for (int j = 0; j < 3; ++j)
			{
				//vertexDatas[i].colorData.lambert.diffuse[j] = colorDatas[num].lambert.diffuse[j];
			}
			////エミッシブ
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.lambert.emissive[j] = colorDatas[num].lambert.emissive[j];
			//}
			////バンプ
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.lambert.bump[j] = colorDatas[num].lambert.bump[j];
			//}
			////透過度
			//vertexDatas[i].colorData.lambert.diffuse[3] = colorDatas[num].lambert.diffuse[3];
			////スペキュラ
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.phong.specular[j] = colorDatas[num].phong.specular[j];
			//}
			////光沢
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.phong.shininess = colorDatas[num].phong.shininess;
			//}
			////反射
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.phong.reflective[j] = colorDatas[num].phong.reflective[j];
			//}
		}
	}
}

void FbxModel::SaveMeshUV(const int num)
{
	//UVセット数の取得
	int uvLayerCount = mesh->GetElementUVCount();
	for (int i = 0; i < uvLayerCount; ++i)
	{
		//UVバッファの取得
		FbxGeometryElementUV* uvElement = mesh->GetElementUV(i);
		//--- マッピングモードの取得
		FbxGeometryElement::EMappingMode mapping = uvElement->GetMappingMode();
		//--- リファレンスモードの取得 ---//
		FbxGeometryElement::EReferenceMode reference = uvElement->GetReferenceMode();
		//uv数を取得
		int uvCount = uvElement->GetDirectArray().GetCount();

		//--- マッピングモードの判別 ---//
		switch (mapping) {
		case FbxGeometryElement::eByControlPoint:
			break;

		case FbxGeometryElement::eByPolygonVertex:
			//--- リファレンスモードの判別 ---//
			switch (reference) {
			case FbxGeometryElement::eDirect:
				break;
			case FbxGeometryElement::eIndexToDirect:
			{
				FbxLayerElementArrayTemplate<int>* uvIndex = &uvElement->GetIndexArray();
				//--- UVを保持 ---// 
				for (int indexCnt = 0; indexCnt < uvIndex->GetCount(); ++indexCnt)
				{
					vertexDatas[i].uv.x = static_cast<float>(uvElement->GetDirectArray().GetAt(uvIndex->GetAt(indexCnt))[0]);
					vertexDatas[i].uv.y = 1.0f - static_cast<float>(uvElement->GetDirectArray().GetAt(uvIndex->GetAt(indexCnt))[1]);
				}
			}
			break;
			default:
				break;
			}
			break;
		case FbxGeometryElement::eByEdge:
			break;
		case FbxGeometryElement::eByPolygon:
			break;
		default:
			break;
		}
	}
}

void FbxModel::SaveMeshMaterial(const int num)
{
	//マテリアルオブジェクトの取得
	FbxNode*	node = mesh->GetNode();
	if (node == nullptr) { return; }
	//マテリアルの数の取得
	int materialNum = node->GetMaterialCount();
	if (materialNum < 0) { return; }
	//カラーデータのサイズ決定
	colorDatas.resize(materialNum);
	//マテリアル情報の取得
	for (int i = 0; i < materialNum; ++i)
	{
		//i番目のマテリアル情報
		FbxSurfaceMaterial*	material = node->GetMaterial(i);
		if (Utility::CheckNull(material)) { return; }
		//マテリアルの解析
		SaveMaterialData(material,i);
		SaveTextureData(material,i);
	}
}

void FbxModel::SaveMeshNormal(const int num)
{
	const FbxGeometryElementNormal*	normalElement = mesh->GetElementNormal();
	if (normalElement == nullptr) { return; }
	//法線のセット
	FbxVector4	normal = normalElement->GetDirectArray().GetAt(num);
	vertexDatas[num].normal.x = static_cast<float>(normal.mData[0]);
	vertexDatas[num].normal.y = static_cast<float>(normal.mData[1]);
	vertexDatas[num].normal.z = static_cast<float>(normal.mData[2]);
}

void FbxModel::SaveTextureNames()
{
	//ノードの取得
	FbxNode*	node = mesh->GetNode();
	//マテリアルの数の取得
	int materialCount = node->GetMaterialCount();
	//マテリアルの数だけ取得
	for (int i = 0; i < materialCount; ++i)
	{
		FbxSurfaceMaterial* material = node->GetMaterial(i);
		//属性を検索する
		FbxProperty		materialProp = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		//属性にアタッチされたテクスチャの種類を判別
		int layerTextureCnt = materialProp.GetSrcObjectCount<FbxLayeredTexture>();
		if (layerTextureCnt > 0)
		{
			//アタッチされたテクスチャが1つの場合
			for (int texCnt = 0; texCnt < layerTextureCnt; ++texCnt)
			{
				//テクスチャを取得
				FbxLayeredTexture*	layerTexture = materialProp.GetSrcObject<FbxLayeredTexture>(texCnt);
				//レイヤー数の取得
				int layerCnt = layerTexture->GetSrcObjectCount<FbxFileTexture>();
				//レイヤー数だけ繰り返す
				for (int lCnt = 0; lCnt < layerCnt; ++lCnt)
				{
					//テクスチャの取得
					FbxFileTexture*	texture = materialProp.GetSrcObject<FbxFileTexture>(lCnt);
					//UVSet名の取得
					std::string	uvSetName = texture->UVSet.Get().Buffer();
					//UVSet名を比較して対応しているテクスチャなら保持
					//if (this->uvNames[texCnt] == uvSetName)
					{
						
					}
				}
			}
		}
		else
		{
			//テクスチャ数の取得
			int fileTextureCount = materialProp.GetSrcObjectCount<FbxFileTexture>();
			if (fileTextureCount > 0)
			{
				//テクスチャの数だけ繰り返す
				for (int texCnt = 0; texCnt < fileTextureCount; ++texCnt)
				{
					//テクスチャの取得
					FbxFileTexture*	texture = materialProp.GetSrcObject<FbxFileTexture>();
					if (texture)
					{
						//テクスチャ名の取得
						std::string	texName = texture->GetRelativeFileName();
						//UVSet名の取得
						std::string	uvSetName = texture->UVSet.Get().Buffer();
						//UVSet名の比較し対応しているテクスチャなら保持
						//if (uvNames[texCnt] == uvSetName)
						{
							//
						}
					}
				}
			}
		}
	}
}

void FbxModel::SaveCluster()
{
	////////////////////////////////////////////////////////////////
	//各フレーム毎の計算に必要なパラメータの取得を行う
	FbxMatrix globalPosition = meshNode->EvaluateGlobalTransform(timeCount);

	//行列の作成(移動・回転・拡大)
	FbxVector4	translation = meshNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4	rotation = meshNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4	scale = meshNode->GetGeometricScaling(FbxNode::eSourcePivot);
	//行列のオフセットを求める
	FbxAMatrix	geometryOffset = FbxAMatrix(translation, rotation, scale);
	/////////////////////////////////////////////
	//全ての頂点にかけ合わせるための計算
	FbxMatrix*	clusterDeformation = new FbxMatrix[mesh->GetControlPointsCount()];
	//0クリア
	std::memset(clusterDeformation, 0, sizeof(FbxMatrix) * mesh->GetControlPointsCount());

	//スキンの数の取得
	int skinCnt = mesh->GetDeformerCount(FbxDeformer::eSkin);
	for (int i = 0; i < skinCnt; ++i)
	{
		//i番目のスキンの取得
		FbxSkin*	skin = static_cast<FbxSkin*>(mesh->GetDeformer(i, FbxDeformer::eSkin));
		//クラスターの数の取得
		int		clusterNum = skin->GetClusterCount();
		for (int j = 0; j < clusterNum; ++j)
		{
			//j番目のクラスターの取得
			FbxCluster*	cluster = skin->GetCluster(j);
			//頂点ボーンの取得
			SaveBoneVertexData(cluster,&globalPosition,&geometryOffset,clusterDeformation);
		}
	}
	//クラスタの削除
	Utility::SafeDeleteArray(clusterDeformation);
}

void FbxModel::SaveBoneVertexData(FbxCluster* cluster,FbxMatrix* globalPosition, FbxAMatrix* geometryOffset,FbxMatrix* clusterDeformation)
{
	FbxMatrix	vertexTransformMatrix;
	//計算
	FbxAMatrix	referenceGlobalInitPostion;				//グローバル空間の初期位置参照
	FbxAMatrix	clusterGlobalInitPostion;				//グローバル空間での初期位置
	FbxMatrix	clusterGlobalCurrentPosition;			//グローバル空間でのクラスタの現在の位置
	FbxMatrix	clusterRelativeInitPosition;			//Childのクラスタの初期位置
	FbxMatrix	clusterRelativeCurrentPositionInverse;	//Childの現在の位置の逆行列

	cluster->GetTransformMatrix(referenceGlobalInitPostion);
	referenceGlobalInitPostion *= *geometryOffset;

	cluster->GetTransformLinkMatrix(clusterGlobalInitPostion);
	clusterGlobalCurrentPosition = cluster->GetLink()->EvaluateGlobalTransform(timeCount);
	clusterRelativeInitPosition = clusterGlobalInitPostion.Inverse() * referenceGlobalInitPostion;
	clusterRelativeCurrentPositionInverse = globalPosition->Inverse() * clusterGlobalCurrentPosition;
	vertexTransformMatrix = clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;

	int pointNum = cluster->GetControlPointIndicesCount();
	for (int i = 0; i < pointNum; ++i)
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

	//全ての頂点と、その各頂点に影響を与える行列を掛け合わせ、最終的な座標値を求める
	for (int i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		FbxVector4	outVertex = clusterDeformation[i].MultNormalize(mesh->GetControlPointAt(i));
		vertexDatas[i].pos.x = static_cast<float>(outVertex[0]);
		vertexDatas[i].pos.y = static_cast<float>(outVertex[1]);
		vertexDatas[i].pos.z = static_cast<float>(outVertex[2]);
	}
}



void FbxModel::SaveMaterialData(FbxSurfaceMaterial* material, const int materialNum)
{
	//LambertかPhongか
	if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
	{
		FbxSurfaceLambert*	lambert = static_cast<FbxSurfaceLambert*>(material);
		SaveLambertData(lambert,materialNum);
	}
	else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
	{
		FbxSurfacePhong*	phong = static_cast<FbxSurfacePhong*>(material);
		SavePhongData(phong,materialNum);
	}
}

void FbxModel::SaveLambertData(FbxSurfaceLambert* lambert, const int materialNum)
{
	//アンビエント
	for (int i = 0; i < 3; ++i)
	{
		//RGBの順で格納
		colorDatas[materialNum].lambert.ambient[i] = static_cast<float>(lambert->Ambient.Get().mData[i]);
	}
	//ディフューズ
	for (int i = 0; i < 3; ++i)
	{
		//RGBの順
		colorDatas[materialNum].lambert.diffuse[i] = static_cast<float>(lambert->Diffuse.Get().mData[i]);
	}
	//エミッシブ
	for (int i = 0; i < 3; ++i)
	{
		//RGB
		colorDatas[materialNum].lambert.emissive[i] = static_cast<float>(lambert->Emissive.Get().mData[i]);
	}
	//バンプ
	for (int i = 0; i < 3; ++i)
	{
		//XYZの順
		colorDatas[materialNum].lambert.bump[i] = static_cast<float>(lambert->Bump.Get().mData[i]);
	}
	//透過度
	colorDatas[materialNum].lambert.diffuse[3] = static_cast<float>(lambert->TransparencyFactor.Get());
}

void FbxModel::SavePhongData(FbxSurfacePhong * phong, const int materialNum)
{
	//スペキュラ
	for (int i = 0; i < 3; ++i)
	{
		colorDatas[materialNum].phong.specular[i] = static_cast<float>(phong->Specular.Get().mData[i]);
	}
	//光沢
	colorDatas[materialNum].phong.shininess = static_cast<float>(phong->Shininess.Get());
	//反射
	for (int i = 0; i < 3; ++i)
	{
		colorDatas[materialNum].phong.reflective[i] = static_cast<float>(phong->Reflection.Get().mData[i]);
	}
}

void FbxModel::SaveTextureData(FbxSurfaceMaterial * material, const int materialNum)
{
	//ディフューズプロパティの検索
	FbxProperty	prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
	//プロパティが持っているレイヤードテクスチャの枚数の取得
	int		layerNum = prop.GetSrcObjectCount();
	//レイヤードテクスチャがなければ通常のテクスチャ
	if (layerNum == 0)
	{
		//通常テクスチャの枚数の取得
		int		normalTexNum = prop.GetSrcObjectCount();
		//各テクスチャの情報の取得
		for (int i = 0; i < normalTexNum; ++i)
		{
			//i番目のテクスチャ情報
			FbxFileTexture*	texture = prop.GetSrcObject<FbxFileTexture>(i);
			if (Utility::CheckNull(texture)) { continue; }
			//テクスチャのファイルパスの取得
			colorDatas[materialNum].texture.filePath = texture->GetRelativeFileName();
			break;
		}
	}

}

bool FbxModel::GetOption()
{
	//法線
	if (mesh->GetElementNormal() != nullptr)
	{
		if (mesh->GetElementNormal()->GetMappingMode() != FbxLayerElement::EMappingMode::eByControlPoint)
		{
			return false;
		}
	}
	//UV
	if (mesh->GetElementUV() != nullptr)
	{
		if (mesh->GetElementUV()->GetMappingMode() != FbxLayerElement::EMappingMode::eByControlPoint)
		{
			return false;
		}
	}
	return true;
}

void FbxModel::SaveVertexData()
{
	//頂点数だけ用意
	vertexDatas.resize(mesh->GetControlPointsCount());

	for (int i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		//座標
		FbxVector4	position = mesh->GetControlPointAt(i);
		vertexDatas[i].pos.x = static_cast<float>(position.mData[0]);
		vertexDatas[i].pos.y = static_cast<float>(position.mData[1]);
		vertexDatas[i].pos.z = static_cast<float>(position.mData[2]);
		//法線
		FbxGeometryElementNormal*	normalElement = mesh->GetElementNormal();
		if (!Utility::CheckNull(normalElement))
		{
			FbxVector4	normal = normalElement->GetDirectArray().GetAt(i);
			vertexDatas[i].normal.x = static_cast<float>(normal.mData[0]);
			vertexDatas[i].normal.y = static_cast<float>(normal.mData[1]);
			vertexDatas[i].normal.z = static_cast<float>(normal.mData[2]);
		}
		//UV
		FbxGeometryElementUV*	uvElement = mesh->GetElementUV();
		if (!Utility::CheckNull(uvElement))
		{
			FbxVector2	uv = uvElement->GetDirectArray().GetAt(i);
			vertexDatas[i].uv.x = static_cast<float>(uvElement->GetDirectArray().GetAt(uvElement->GetIndexArray().GetAt(i))[0]);
			vertexDatas[i].uv.y = 1.0f - static_cast<float>(uvElement->GetDirectArray().GetAt(uvElement->GetIndexArray().GetAt(i))[1]);
			std::string uvSetName = uvElement->GetName();
		}
		//SaveMeshUV(i);
	}

	indices.resize(mesh->GetPolygonVertexCount());
	SetMeshData();
}

void FbxModel::SavePolygonData()
{
	FbxStringList	uvSetName;
	mesh->GetUVSetNames(uvSetName);

	for (int i = 0; i < mesh->GetPolygonCount(); ++i)
	{
		for (int j = 0; j < mesh->GetPolygonSize(i); ++j)
		{
			Vertex	vertex;
			//位置
			int	v = mesh->GetPolygonVertex(i, j);
			FbxVector4	position = mesh->GetControlPoints()[v];
			vertex.pos.x = static_cast<float>(position.mData[0]);
			vertex.pos.y = static_cast<float>(position.mData[1]);
			vertex.pos.z = static_cast<float>(position.mData[2]);
			//法線
			FbxVector4	normal;
			mesh->GetPolygonVertexNormal(i, j, normal);
			vertex.normal.x = static_cast<float>(normal.mData[0]);
			vertex.normal.y = static_cast<float>(normal.mData[1]);
			vertex.normal.z = static_cast<float>(normal.mData[2]);
			//UV
			FbxVector2	uv;
			bool	isMapping;
			if (mesh->GetElementUVCount() > 0)
			{
				mesh->GetPolygonVertexUV(i, j, uvSetName[0], uv, isMapping);
			}
			vertex.uv.x = static_cast<float>(uv.mData[0]);
			vertex.uv.y = 1.0f - static_cast<float>(uv.mData[1]);

			vertexDatas.push_back(vertex);
		}
	}
}

void FbxModel::LoadMeshData()
{
	vertexDatas.clear();
	indices.clear();

	if (GetOption())
	{
		SaveVertexData();
	}
	else
	{
		SavePolygonData();
	}
}

