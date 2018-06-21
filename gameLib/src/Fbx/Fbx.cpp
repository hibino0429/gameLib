#include "Fbx.h"

void	FbxModel::LoadFile()
{
	fbxManager = FbxManager::Create();
	scene = FbxScene::Create(fbxManager, "fbxScene");
	FbxString fileName("humanoid.fbx");
	fbxImporter = FbxImporter::Create(fbxManager, "imp");
	fbxImporter->Initialize(fileName.Buffer(), -1, fbxManager->GetIOSettings());
	fbxImporter->Destroy();
}

void	FbxModel::LoadVertexData()
{
	for (int i = 0; i < scene->GetRootNode()->GetChildCount(); ++i)
	{
		if (scene->GetRootNode()->GetChild(i)->GetNodeAttribute()->GetAttributeType() == FbxNodeAttribute::eMesh)
		{
			mesh = scene->GetRootNode()->GetChild(i)->GetMesh();
			break;
		}
	}
	//頂点データが保持されているノードを読み込み取得する
	Vec3*	vec3 = new Vec3[mesh->GetControlPointsCount()];
	for (int i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		vec3[i].x = (float)mesh->GetControlPointAt(i)[0];
		vec3[i].y = (float)mesh->GetControlPointAt(i)[1];
		vec3[i].z = (float)mesh->GetControlPointAt(i)[2];
	}
}

void	FbxModel::LoadIndexData()
{
	D3D11_BUFFER_DESC	indexDesc;
	indexDesc.ByteWidth = sizeof(int) * mesh->GetPolygonVertexCount();
	indexDesc.Usage = D3D11_USAGE_DEFAULT;
	indexDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexDesc.CPUAccessFlags = 0;
	indexDesc.MiscFlags = 0;
	indexDesc.StructureByteStride = 0;

	ID3D11Buffer*	indexBuffer;
	D3D11_SUBRESOURCE_DATA	indexData;
	indexData.pSysMem = mesh->GetPolygonVertices();
	DXEngine::GetDevice3D().CreateBuffer(&indexDesc, &indexData, &indexBuffer);
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


//概要: 頂点の情報を取得
void	FbxModel::GetVertexInfo()
{
	controlNum = mesh->GetControlPointsCount();	//頂点数取得
	src = mesh->GetControlPoints();				//頂点座標配列
	
	//コピー
	Math::Vector4*	controlArray = new Math::Vector4[controlNum];
	for (int i = 0; i < controlNum; ++i)
	{
		controlArray[i].x = src[i][0];
		controlArray[i].y = src[i][1];
		controlArray[i].z = src[i][2];
		controlArray[i].w = src[i][3];

	}
	
}


//概要: メッシュの法線の取得
void	FbxModel::GetMeshNormal()
{
	//レイヤーオブジェクトを取得
	int layerNum = mesh->GetLayerCount();
	for (int i = 0; i < layerNum; ++i)
	{
		normalLayer = mesh->GetLayer(i);
		//法線をチェック
		normalElem = normalLayer->GetNormals();
		if (normalElem == 0)
		{
			continue;
		}
		//法線あった
	}
}

//概要: 法線ベクトルの方式を取得
void	FbxModel::GetNormalMethod()
{
	//マッピングモード・リファレンスモードの取得
	FbxLayerElement::EMappingMode	mappingMode = normalElem->GetMappingMode();
	FbxLayerElement::EReferenceMode	refMode = normalElem->GetReferenceMode();

	int	normalNum = normalElem->GetDirectArray().GetCount();
	int	indexNum = normalElem->GetIndexArray().GetCount();
	Math::Vector4*	normalBuf = new Math::Vector4[normalNum];

	if (mappingMode == FbxLayerElement::eByPolygonVertex)
	{
		if (refMode == FbxLayerElement::eDirect)
		{
			//直接取得
			for(int i = 0; i < normalNum; ++i)
			{
				normalBuf[i].x = (float)normalElem->GetDirectArray().GetAt(i)[0];
				normalBuf[i].y = (float)normalElem->GetDirectArray().GetAt(i)[1];
				normalBuf[i].z = (float)normalElem->GetDirectArray().GetAt(i)[2];
			}
		}
	}
	else if (mappingMode == FbxLayerElement::eByControlPoint)
	{
		if (refMode == FbxLayerElement::eDirect)
		{
			//直接取得
			for (int i = 0; i < normalNum; ++i)
			{
				normalBuf[i].x = (float)normalElem->GetDirectArray().GetAt(i)[0];
				normalBuf[i].y = (float)normalElem->GetDirectArray().GetAt(i)[1];
				normalBuf[i].z = (float)normalElem->GetDirectArray().GetAt(i)[2];
			}
		}
	}
}


//概要: UV情報を取得する
void	FbxModel::GetUVInfo()
{
	int layerCount = mesh->GetLayerCount();	//meshから取得
	for (int i = 0; i < layerCount; ++i)
	{
		uvLayer = mesh->GetLayer(i);
		uvElem = uvLayer->GetUVs();
		if (uvElem == 0)
		{
			continue;
		}
		//UV情報を取得する
	}
}

//概要: UV座標を取得する
void	FbxModel::GetUVPos()
{
	int uvNum = uvElem->GetDirectArray().GetCount();
	int indexNum = uvElem->GetIndexArray().GetCount();
	int size = uvNum > indexNum ? uvNum : indexNum;
	Math::Vector4*	buffer = new Math::Vector4[size];

	//マッピングモード・リファレンスモード別に取得
	FbxLayerElement::EMappingMode	mappingMode = uvElem->GetMappingMode();
	FbxLayerElement::EReferenceMode	refMode = uvElem->GetReferenceMode();


	if (mappingMode == FbxLayerElement::eByPolygonVertex) {
		if (refMode == FbxLayerElement::eDirect) {
			// 直接取得
			for (int i = 0; i < size; ++i) {
				buffer[i].x = (float)uvElem->GetDirectArray().GetAt(i)[0];
				buffer[i].y = (float)uvElem->GetDirectArray().GetAt(i)[1];
			}
		}
		else
			if (refMode == FbxLayerElement::eIndexToDirect) {
				// インデックスから取得
				for (int i = 0; i < size; ++i) {
					int index = uvElem->GetIndexArray().GetAt(i);
					buffer[i].x = (float)uvElem->GetDirectArray().GetAt(index)[0];
					buffer[i].y = (float)uvElem->GetDirectArray().GetAt(index)[1];
				}
			}
	}
}



//概要: マテリアルオブジェクトを取得
void	FbxModel::GetMaterialObject()
{
	materialNode = mesh->GetNode();
	if (materialNode == 0) { return; }

	//マテリアル数
	int materialNum = materialNode->GetMaterialCount();
	if (materialNum == 0) { return; }

	//マテリアル情報を取得
	for (int i = 0; i < materialNum; ++i)
	{
		material = materialNode->GetMaterial(i);
		if (material != 0)
		{
			//マテリアル解析

			//LambertかPhongか
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				//lambertにダウンキャスト
				FbxSurfaceLambert*	lambert = (FbxSurfaceLambert*)material;
				DirectX::XMVECTOR	ambient_;
				DirectX::XMVECTOR	diffuse_;
				DirectX::XMVECTOR	emissive_;
				DirectX::XMFLOAT3	bump_;
				DirectX::XMVECTOR	transparency_;
				
				//// アンビエント
				//ambient_.r = (float)lambert->Ambient.Get()[0];
				//ambient_.r = (float)lambert->Ambient.Get()[1];
				//ambient_.g = (float)lambert->Ambient.Get()[2];

				//// ディフューズ
				//diffuse_.r = (float)lambert->Diffuse.Get()[0];
				//diffuse_.g = (float)lambert->Diffuse.Get()[1];
				//diffuse_.b = (float)lambert->Diffuse.Get()[2];

				//// エミッシブ
				//emissive_.r = (float)lambert->Emissive.Get()[0];
				//emissive_.g = (float)lambert->Emissive.Get()[1];
				//emissive_.b = (float)lambert->Emissive.Get()[2];

				//// バンプ
				//bump_.x = (float)lambert->Bump.Get()[0];
				//bump_.y = (float)lambert->Bump.Get()[1];
				//bump_.z = (float)lambert->Bump.Get()[2];

				//// 透過度
				//transparency_ = (float)lambert->TransparencyFactor.Get();


			}
			else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
			{
				FbxSurfacePhong*	phong = (FbxSurfacePhong*)material;

				//ランパード情報を取得
				
				//情報
				DirectX::XMVECTOR	specular;
				float	shininess;
				float	reflectivity;
				//スペキュラ
				/*specular.r = (float)phong->Specular.Get()[0];
				specular.g = (float)phong->Specular.Get()[1];
				specular.b = (float)phong->Specular.Get()[2];*/

				//光沢
				shininess = (float)phong->Shininess.Get();

				//反射
				reflectivity = (float)phong->ReflectionFactor.Get();
			}
		}
	}
}


//概要: テクスチャ情報の取得
void	FbxModel::GetTexture()
{
	//ディフューズプロパティの検索
	texProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
	//プロパティが持っているレイヤードテクスチャの枚数をチェック
	int layerNum = texProperty.GetSrcObjectCount();
	
	//レイヤードテクスチャがなければ通常のテクスチャ
	if (layerNum == 0)
	{
		//通常のテクスチャの枚数をチェック
		int numNormalTexture = texProperty.GetSrcObjectCount();
		//書くテクスチャについてテクスチャ情報をゲット
		for (int i = 0; i < numNormalTexture; ++i)
		{
			fbxTexture = FbxCast<FbxTexture>(texProperty.GetSrcObject());

			//テクスチャファイルパスの取得
			const char* fileName = fbxTexture->GetName();
			char outTexName[100] = "";
			size_t size = strlen(fileName);
			memcpy(outTexName, fileName, size);
			outTexName[size] = '\0';

			break;
		}
	}
}

//概要: モデルの位置を取得
void	FbxModel::GetModelPos()
{
	int time = 0;
	modelNode = mesh->GetNode();

	//タイムモードの取得
	//1フレーム単位で位置を取得できる
	FbxGlobalSettings&	gloabalTime = scene->GetGlobalSettings();
	time = gloabalTime.GetTimeMode();


}