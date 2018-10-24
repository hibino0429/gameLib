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

	//�O�p�|���S����
	FbxGeometryConverter	geometryConverter(fbxManager);
	geometryConverter.Triangulate(scene, true);

	//�m�[�h�^�C�v�����b�V���Ȃ�
	if (SearchDesignationNode(FbxNodeAttribute::EType::eMesh))
	{
		//���b�V���m�[�h�ƃ��b�V�����������
		meshNode = scene->GetRootNode()->GetChild(findNodeTypeNum);
		mesh = scene->GetRootNode()->GetChild(findNodeTypeNum)->GetMesh();
		LoadMeshData();
		//LoadNodeForMeshNum();
		//SetMeshData();
	}
	CreateAnimation();
	CreateAnimationTime();
}



//!@brief	���_���̎擾
int			FbxModel::GetVertexDatas()
{
	return this->vertexDataNum;
}
//!@brief	���_�̃|���S�����̎擾
int				FbxModel::GetVertexCount()
{
	return this->indexDataNum;
}
//!@brief	���_�f�[�^�̎擾
std::vector<int>&		FbxModel::GetVertexPolygonVertices()
{
	return this->indices;
}



//!@brief	���_�f�[�^��n��
std::vector<Vertex>&		FbxModel::GetVertexData()
{
	return vertexDatas;
}

//!@brief	�w�肵���m�[�h��T��
//!@param[in]	nodeType	�T���m�[�h
bool		FbxModel::SearchDesignationNode(const FbxNodeAttribute::EType& nodeType)
{
	//�擪�̃m�[�h���珇�ԂɌ������Ă���
	for (int i = 0; i < scene->GetRootNode()->GetChildCount(); ++i)
	{
		if (scene->GetRootNode()->GetChild(i)->GetNodeAttribute() == nullptr)
		{
			std::cout << "NULL Node Attribute" << std::endl;
			return false;
		}
		//���_�f�[�^�������Ă���m�[�h�𔭌�������
		if (scene->GetRootNode()->GetChild(i)->GetNodeAttribute()->GetAttributeType() == nodeType)
		{
			findNodeTypeNum = i;
			return true;
		}
	}
	return false;
}

//!@brief	���b�V���̐������m�[�h�̓ǂݍ��݂��s��
void		FbxModel::LoadNodeForMeshNum()
{
	//���b�V���̐��������_�f�[�^���쐬����
	//���_�f�[�^�Ƀ��b�V���f�[�^��n��
	for (int meshCnt = 0; meshCnt < mesh->GetControlPointsCount(); ++meshCnt)
	{
		//���b�V���̒��_��n��
		vertexDatas.push_back(
			Vertex(static_cast<float>(mesh->GetControlPointAt(meshCnt)[0]),
				static_cast<float>(mesh->GetControlPointAt(meshCnt)[1]),
				static_cast<float>(mesh->GetControlPointAt(meshCnt)[2])
			)
		);
	}
}


//!@brief	���b�V���̃f�[�^���󂯎��
void		FbxModel::SetMeshData()
{
	vertexDataNum = mesh->GetControlPointsCount();	//���_��
	indexDataNum = mesh->GetPolygonVertexCount();	//�C���f�b�N�X��
	//�C���f�b�N�X�f�[�^
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


//!@brief	���݂̃A�j���[�V�����ԍ��̎擾
const int&	FbxModel::GetNowAnimationNumber() const
{
	return animStackNumber;
}
//!@brief	���݂̃A�j���[�V�������̎擾
const char*	FbxModel::GetNowAnimationName() const
{
	if (animStackNameArray.Size() == 0) { return ""; }
	return animStackNameArray[animStackNumber]->Buffer();
}

////////////////////////////////////////////////////////////
//�ݒ菈��
////////////////////////////////////////////////////////////
//!@brief	�A�j���[�V�����ԍ��̍X�V
void	FbxModel::SetAnimationNumber(const int& animationNumber)
{
	this->animStackNumber = animationNumber;
}



//!@brief	�A�j���[�V�����̐���
void	FbxModel::CreateAnimation()
{
	////////////////////////////////////////////////////////
	//���p����A�j���[�V�����̑I��
	////////////////////////////////////////////////////////
	//FBX�t�@�C�����̃A�j���[�V�������ꗗ�̎擾
	scene->FillAnimStackNameArray(animStackNameArray);
	if (animStackNameArray.Size() == 0) { return; }
	//�I�񂾃A�j���[�V���������g�p���āA���̃A�j���[�V��������T��
	FbxAnimStack*	animationStack = scene->FindMember<FbxAnimStack>(animStackNameArray[animStackNumber]->Buffer());
	//�I�񂾃A�j���[�V������ݒ肷��
	scene->SetCurrentAnimationStack(animationStack);
}


//!@brief	�A�j���[�V�����̎��Ԃ̐����Ɛݒ�
void	FbxModel::CreateAnimationTime()
{
	///////////////////////////////////////////////////////
	//�A�j���[�V�����̎��s�ɕK�v�Ȏ��Ԃ������ݒ�
	///////////////////////////////////////////////////////
	if (animStackNameArray.Size() == 0) { return; }
	//FBX���玞�ԏ��̎擾
	FbxTakeInfo*	takeInfo = scene->GetTakeInfo(*(animStackNameArray[animStackNumber]));
	//�J�n���Ԃ̎擾
	start = takeInfo->mLocalTimeSpan.GetStart();
	//�I�����Ԃ̎擾
	stop = takeInfo->mLocalTimeSpan.GetStop();
	//�A�j���[�V����(1�R�})�����s����鎞�ԏ��
	frameTime.SetTime(0, 0, 0, 1, 0, scene->GetGlobalSettings().GetTimeMode());
	//�J�n����̌o�ߎ���
	timeCount = start;
}


//!@brief	�A�j���[�V�����̍s��v�Z
void	FbxModel::AnimationMatrix()
{
	//�A�j���[�V�����̎��Ԃ̍X�V
	timeCount += frameTime;
	if (timeCount > stop)
	{
		timeCount = start;
	}
	SaveCluster();
}




//�T�v: FBX�t�@�C���̓ǂݍ���
//�߂�l: �����Ȃ�true
bool	FbxModel::LoadFbx(const std::string& fileName)
{
	if(fbxImporter->Initialize(fileName.c_str()))
	{
		return false;
	}
	return true;
}



//�T�v: �q�m�[�h�̐��̎擾
void	FbxModel::GetChildNodeNum()
{
	childNodeNum = rootNode->GetChildCount();
}

//�T�v: �q�m�[�h�̎擾
void	FbxModel::GetChildNode()
{
	for (int i = 0; i < childNodeNum; ++i)
	{
		childNode = rootNode->GetChild(i);	//�q�m�[�h���擾
	}
}


//�T�v: �m�[�h�̃^�C�v�̎擾
void	FbxModel::GetNodeAttribute()
{
	nodeAttribute = rootNode->GetNodeAttribute();
	if (nodeAttribute)
	{
		type =  nodeAttribute->GetAttributeType();
		GetMeshObject();
	}
}

//�T�v: ���b�V���I�u�W�F�N�g�̎擾
void	FbxModel::GetMeshObject()
{
	if (type == FbxNodeAttribute::eMesh)
	{
		//���b�V���Ƀ_�E���L���X�g
		mesh = (FbxMesh*)nodeAttribute;
	}
}

//�T�v: �|���S���̊�{���̎擾
void	FbxModel::GetPolygonInfo()
{
	polygonNum = mesh->GetPolygonCount();
	polygonVertexNum = mesh->GetPolygonVertexCount();
	polygonIndexArray = mesh->GetPolygonVertices();

	for (int p = 0; p < polygonNum; ++p) {
		int indexNumInPolygon = mesh->GetPolygonSize(p);	//p�Ԗڂ̃|���S�����_��
		for (int n = 0; n < indexNumInPolygon; ++n) {
			//�|���S��p���\������n�Ԗڂ̒��_�C���f�b�N�X�ԍ�
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
			//�A���r�G���g
			for (int j = 0; j < 3; ++j)
			{
				//vertexDatas[i].colorData.lambert.ambient[j] = colorDatas[num].lambert.ambient[j];
			}
			//�f�B�t���[�Y
			for (int j = 0; j < 3; ++j)
			{
				//vertexDatas[i].colorData.lambert.diffuse[j] = colorDatas[num].lambert.diffuse[j];
			}
			////�G�~�b�V�u
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.lambert.emissive[j] = colorDatas[num].lambert.emissive[j];
			//}
			////�o���v
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.lambert.bump[j] = colorDatas[num].lambert.bump[j];
			//}
			////���ߓx
			//vertexDatas[i].colorData.lambert.diffuse[3] = colorDatas[num].lambert.diffuse[3];
			////�X�y�L����
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.phong.specular[j] = colorDatas[num].phong.specular[j];
			//}
			////����
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.phong.shininess = colorDatas[num].phong.shininess;
			//}
			////����
			//for (int j = 0; j < 3; ++j)
			//{
			//	vertexDatas[i].colorData.phong.reflective[j] = colorDatas[num].phong.reflective[j];
			//}
		}
	}
}

void FbxModel::SaveMeshUV(const int num)
{
	//UV�Z�b�g���̎擾
	int uvLayerCount = mesh->GetElementUVCount();
	for (int i = 0; i < uvLayerCount; ++i)
	{
		//UV�o�b�t�@�̎擾
		FbxGeometryElementUV* uvElement = mesh->GetElementUV(i);
		//--- �}�b�s���O���[�h�̎擾
		FbxGeometryElement::EMappingMode mapping = uvElement->GetMappingMode();
		//--- ���t�@�����X���[�h�̎擾 ---//
		FbxGeometryElement::EReferenceMode reference = uvElement->GetReferenceMode();
		//uv�����擾
		int uvCount = uvElement->GetDirectArray().GetCount();

		//--- �}�b�s���O���[�h�̔��� ---//
		switch (mapping) {
		case FbxGeometryElement::eByControlPoint:
			break;

		case FbxGeometryElement::eByPolygonVertex:
			//--- ���t�@�����X���[�h�̔��� ---//
			switch (reference) {
			case FbxGeometryElement::eDirect:
				break;
			case FbxGeometryElement::eIndexToDirect:
			{
				FbxLayerElementArrayTemplate<int>* uvIndex = &uvElement->GetIndexArray();
				//--- UV��ێ� ---// 
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
	//�}�e���A���I�u�W�F�N�g�̎擾
	FbxNode*	node = mesh->GetNode();
	if (node == nullptr) { return; }
	//�}�e���A���̐��̎擾
	int materialNum = node->GetMaterialCount();
	if (materialNum < 0) { return; }
	//�J���[�f�[�^�̃T�C�Y����
	colorDatas.resize(materialNum);
	//�}�e���A�����̎擾
	for (int i = 0; i < materialNum; ++i)
	{
		//i�Ԗڂ̃}�e���A�����
		FbxSurfaceMaterial*	material = node->GetMaterial(i);
		if (Utility::CheckNull(material)) { return; }
		//�}�e���A���̉��
		SaveMaterialData(material,i);
		SaveTextureData(material,i);
	}
}

void FbxModel::SaveMeshNormal(const int num)
{
	const FbxGeometryElementNormal*	normalElement = mesh->GetElementNormal();
	if (normalElement == nullptr) { return; }
	//�@���̃Z�b�g
	FbxVector4	normal = normalElement->GetDirectArray().GetAt(num);
	vertexDatas[num].normal.x = static_cast<float>(normal.mData[0]);
	vertexDatas[num].normal.y = static_cast<float>(normal.mData[1]);
	vertexDatas[num].normal.z = static_cast<float>(normal.mData[2]);
}

void FbxModel::SaveTextureNames()
{
	//�m�[�h�̎擾
	FbxNode*	node = mesh->GetNode();
	//�}�e���A���̐��̎擾
	int materialCount = node->GetMaterialCount();
	//�}�e���A���̐������擾
	for (int i = 0; i < materialCount; ++i)
	{
		FbxSurfaceMaterial* material = node->GetMaterial(i);
		//��������������
		FbxProperty		materialProp = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
		//�����ɃA�^�b�`���ꂽ�e�N�X�`���̎�ނ𔻕�
		int layerTextureCnt = materialProp.GetSrcObjectCount<FbxLayeredTexture>();
		if (layerTextureCnt > 0)
		{
			//�A�^�b�`���ꂽ�e�N�X�`����1�̏ꍇ
			for (int texCnt = 0; texCnt < layerTextureCnt; ++texCnt)
			{
				//�e�N�X�`�����擾
				FbxLayeredTexture*	layerTexture = materialProp.GetSrcObject<FbxLayeredTexture>(texCnt);
				//���C���[���̎擾
				int layerCnt = layerTexture->GetSrcObjectCount<FbxFileTexture>();
				//���C���[�������J��Ԃ�
				for (int lCnt = 0; lCnt < layerCnt; ++lCnt)
				{
					//�e�N�X�`���̎擾
					FbxFileTexture*	texture = materialProp.GetSrcObject<FbxFileTexture>(lCnt);
					//UVSet���̎擾
					std::string	uvSetName = texture->UVSet.Get().Buffer();
					//UVSet�����r���đΉ����Ă���e�N�X�`���Ȃ�ێ�
					//if (this->uvNames[texCnt] == uvSetName)
					{
						
					}
				}
			}
		}
		else
		{
			//�e�N�X�`�����̎擾
			int fileTextureCount = materialProp.GetSrcObjectCount<FbxFileTexture>();
			if (fileTextureCount > 0)
			{
				//�e�N�X�`���̐������J��Ԃ�
				for (int texCnt = 0; texCnt < fileTextureCount; ++texCnt)
				{
					//�e�N�X�`���̎擾
					FbxFileTexture*	texture = materialProp.GetSrcObject<FbxFileTexture>();
					if (texture)
					{
						//�e�N�X�`�����̎擾
						std::string	texName = texture->GetRelativeFileName();
						//UVSet���̎擾
						std::string	uvSetName = texture->UVSet.Get().Buffer();
						//UVSet���̔�r���Ή����Ă���e�N�X�`���Ȃ�ێ�
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
	//�e�t���[�����̌v�Z�ɕK�v�ȃp�����[�^�̎擾���s��
	FbxMatrix globalPosition = meshNode->EvaluateGlobalTransform(timeCount);

	//�s��̍쐬(�ړ��E��]�E�g��)
	FbxVector4	translation = meshNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4	rotation = meshNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4	scale = meshNode->GetGeometricScaling(FbxNode::eSourcePivot);
	//�s��̃I�t�Z�b�g�����߂�
	FbxAMatrix	geometryOffset = FbxAMatrix(translation, rotation, scale);
	/////////////////////////////////////////////
	//�S�Ă̒��_�ɂ������킹�邽�߂̌v�Z
	FbxMatrix*	clusterDeformation = new FbxMatrix[mesh->GetControlPointsCount()];
	//0�N���A
	std::memset(clusterDeformation, 0, sizeof(FbxMatrix) * mesh->GetControlPointsCount());

	//�X�L���̐��̎擾
	int skinCnt = mesh->GetDeformerCount(FbxDeformer::eSkin);
	for (int i = 0; i < skinCnt; ++i)
	{
		//i�Ԗڂ̃X�L���̎擾
		FbxSkin*	skin = static_cast<FbxSkin*>(mesh->GetDeformer(i, FbxDeformer::eSkin));
		//�N���X�^�[�̐��̎擾
		int		clusterNum = skin->GetClusterCount();
		for (int j = 0; j < clusterNum; ++j)
		{
			//j�Ԗڂ̃N���X�^�[�̎擾
			FbxCluster*	cluster = skin->GetCluster(j);
			//���_�{�[���̎擾
			SaveBoneVertexData(cluster,&globalPosition,&geometryOffset,clusterDeformation);
		}
	}
	//�N���X�^�̍폜
	Utility::SafeDeleteArray(clusterDeformation);
}

void FbxModel::SaveBoneVertexData(FbxCluster* cluster,FbxMatrix* globalPosition, FbxAMatrix* geometryOffset,FbxMatrix* clusterDeformation)
{
	FbxMatrix	vertexTransformMatrix;
	//�v�Z
	FbxAMatrix	referenceGlobalInitPostion;				//�O���[�o����Ԃ̏����ʒu�Q��
	FbxAMatrix	clusterGlobalInitPostion;				//�O���[�o����Ԃł̏����ʒu
	FbxMatrix	clusterGlobalCurrentPosition;			//�O���[�o����Ԃł̃N���X�^�̌��݂̈ʒu
	FbxMatrix	clusterRelativeInitPosition;			//Child�̃N���X�^�̏����ʒu
	FbxMatrix	clusterRelativeCurrentPositionInverse;	//Child�̌��݂̈ʒu�̋t�s��

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
		//�e����^���钸�_�ԍ�(�C���f�b�N�X)�̎擾
		int index = cluster->GetControlPointIndices()[i];
		//���_(index�ϐ�)�ɗ^����e���x�̐��l�̎擾
		double weight = cluster->GetControlPointWeights()[i];
		//���_(index�ϐ�)�ɉe����^���邽�߂̍s��̌v�Z (�N���X�^�����_Ani�e����^����s�� = �N���X�^�����Ǝ��s�� * ���_A�̉e���x)
		FbxMatrix influence = vertexTransformMatrix * weight;
		//���_(index�ϐ�)�ɉe����^���邽�߂̍s��։��Z (���_A�ɉe����^����s�� = �N���X�^1�����_A�ɉe����^����s�� + �N���X�^2�����_A�ɉe���𓖂Ă�s�� + ...n��)
		clusterDeformation[index] += influence;
	}

	//�S�Ă̒��_�ƁA���̊e���_�ɉe����^����s����|�����킹�A�ŏI�I�ȍ��W�l�����߂�
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
	//Lambert��Phong��
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
	//�A���r�G���g
	for (int i = 0; i < 3; ++i)
	{
		//RGB�̏��Ŋi�[
		colorDatas[materialNum].lambert.ambient[i] = static_cast<float>(lambert->Ambient.Get().mData[i]);
	}
	//�f�B�t���[�Y
	for (int i = 0; i < 3; ++i)
	{
		//RGB�̏�
		colorDatas[materialNum].lambert.diffuse[i] = static_cast<float>(lambert->Diffuse.Get().mData[i]);
	}
	//�G�~�b�V�u
	for (int i = 0; i < 3; ++i)
	{
		//RGB
		colorDatas[materialNum].lambert.emissive[i] = static_cast<float>(lambert->Emissive.Get().mData[i]);
	}
	//�o���v
	for (int i = 0; i < 3; ++i)
	{
		//XYZ�̏�
		colorDatas[materialNum].lambert.bump[i] = static_cast<float>(lambert->Bump.Get().mData[i]);
	}
	//���ߓx
	colorDatas[materialNum].lambert.diffuse[3] = static_cast<float>(lambert->TransparencyFactor.Get());
}

void FbxModel::SavePhongData(FbxSurfacePhong * phong, const int materialNum)
{
	//�X�y�L����
	for (int i = 0; i < 3; ++i)
	{
		colorDatas[materialNum].phong.specular[i] = static_cast<float>(phong->Specular.Get().mData[i]);
	}
	//����
	colorDatas[materialNum].phong.shininess = static_cast<float>(phong->Shininess.Get());
	//����
	for (int i = 0; i < 3; ++i)
	{
		colorDatas[materialNum].phong.reflective[i] = static_cast<float>(phong->Reflection.Get().mData[i]);
	}
}

void FbxModel::SaveTextureData(FbxSurfaceMaterial * material, const int materialNum)
{
	//�f�B�t���[�Y�v���p�e�B�̌���
	FbxProperty	prop = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
	//�v���p�e�B�������Ă��郌�C���[�h�e�N�X�`���̖����̎擾
	int		layerNum = prop.GetSrcObjectCount();
	//���C���[�h�e�N�X�`�����Ȃ���Βʏ�̃e�N�X�`��
	if (layerNum == 0)
	{
		//�ʏ�e�N�X�`���̖����̎擾
		int		normalTexNum = prop.GetSrcObjectCount();
		//�e�e�N�X�`���̏��̎擾
		for (int i = 0; i < normalTexNum; ++i)
		{
			//i�Ԗڂ̃e�N�X�`�����
			FbxFileTexture*	texture = prop.GetSrcObject<FbxFileTexture>(i);
			if (Utility::CheckNull(texture)) { continue; }
			//�e�N�X�`���̃t�@�C���p�X�̎擾
			colorDatas[materialNum].texture.filePath = texture->GetRelativeFileName();
			break;
		}
	}

}

bool FbxModel::GetOption()
{
	//�@��
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
	//���_�������p��
	vertexDatas.resize(mesh->GetControlPointsCount());

	for (int i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		//���W
		FbxVector4	position = mesh->GetControlPointAt(i);
		vertexDatas[i].pos.x = static_cast<float>(position.mData[0]);
		vertexDatas[i].pos.y = static_cast<float>(position.mData[1]);
		vertexDatas[i].pos.z = static_cast<float>(position.mData[2]);
		//�@��
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
			//�ʒu
			int	v = mesh->GetPolygonVertex(i, j);
			FbxVector4	position = mesh->GetControlPoints()[v];
			vertex.pos.x = static_cast<float>(position.mData[0]);
			vertex.pos.y = static_cast<float>(position.mData[1]);
			vertex.pos.z = static_cast<float>(position.mData[2]);
			//�@��
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

