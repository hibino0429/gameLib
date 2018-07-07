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

	//�m�[�h�^�C�v�����b�V���Ȃ�
	if (SearchDesignationNode(FbxNodeAttribute::EType::eMesh))
	{
		//���b�V���m�[�h�ƃ��b�V�����������
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

	//�m�[�h�^�C�v�����b�V���Ȃ�
	if (SearchDesignationNode(FbxNodeAttribute::EType::eMesh))
	{
		//���b�V���m�[�h�ƃ��b�V�����������
		meshNode = scene->GetRootNode()->GetChild(findNodeTypeNum);
		mesh = scene->GetRootNode()->GetChild(findNodeTypeNum)->GetMesh();
		LoadNodeForMeshNum();
		SetMeshData();
	}
}



//!@brief	�m�[�h�̒T��
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


//!@brief	���݂̃A�j���[�V�����ԍ��̎擾
const int&	FbxModel::GetNowAnimationNumber() const
{
	return animStackNumber;
}
//!@brief	���݂̃A�j���[�V�������̎擾
const char*	FbxModel::GetNowAnimationName() const
{
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

	////////////////////////////////////////////////////////////////
	//�e�t���[�����̌v�Z�ɕK�v�ȃp�����[�^�̎擾���s��
	FbxMatrix globalPosition = meshNode->EvaluateGlobalTransform(timeCount);
	
	//�s��̍쐬(�ړ��E��]�E�g��)
	FbxVector4	translation = meshNode->GetGeometricTranslation(FbxNode::eSourcePivot);
	FbxVector4	rotation = meshNode->GetGeometricRotation(FbxNode::eSourcePivot);
	FbxVector4	scale = meshNode->GetGeometricScaling(FbxNode::eSourcePivot);
	//�s��̃I�t�Z�b�g�����߂�
	FbxAMatrix	geometryOffset = FbxAMatrix(translation, rotation, scale);


	//////////////////////////////////////////////////////////////
	//�S�Ă̒��_�ɂ������킹�邽�߂̌v�Z
	FbxMatrix*	clusterDeformation = new FbxMatrix[mesh->GetControlPointsCount()];
	//0�N���A
	std::memset(clusterDeformation, 0, sizeof(FbxMatrix) * mesh->GetControlPointsCount());
	
	//�S�ẴN���X�^���̎擾
	FbxSkin*	skinDeformer = (FbxSkin*)mesh->GetDeformer(0, FbxDeformer::eSkin);
	int clusterCount = skinDeformer->GetClusterCount();

	//�N���X�^����1�����o���āA�N���X�^�Ǝ��Ɏ��s��̌v�Z���s��
	for (int clusterIndex = 0; clusterIndex < clusterCount; ++clusterIndex)
	{
		//�P�̃N���X�^���̎擾
		FbxCluster*	cluster = skinDeformer->GetCluster(clusterIndex);
		FbxMatrix	vertexTransformMatrix;
		
		//--------------------------------�v�Z-------------------------------//
		FbxAMatrix	referenceGlobalInitPostion;				//�O���[�o����Ԃ̏����ʒu�Q��
		FbxAMatrix	clusterGlobalInitPostion;				//�O���[�o����Ԃł̏����ʒu
		FbxMatrix	clusterGlobalCurrentPosition;			//�O���[�o����Ԃł̃N���X�^�̌��݂̈ʒu
		FbxMatrix	clusterRelativeInitPosition;			//Child�̃N���X�^�̏����ʒu
		FbxMatrix	clusterRelativeCurrentPositionInverse;	//Child�̌��݂̈ʒu�̋t�s��

		cluster->GetTransformMatrix(referenceGlobalInitPostion);
		referenceGlobalInitPostion *= geometryOffset;

		cluster->GetTransformLinkMatrix(clusterGlobalInitPostion);
		clusterGlobalCurrentPosition = cluster->GetLink()->EvaluateGlobalTransform(timeCount);
		clusterRelativeInitPosition = clusterGlobalInitPostion.Inverse() * referenceGlobalInitPostion;
		clusterRelativeCurrentPositionInverse = globalPosition.Inverse() * clusterGlobalCurrentPosition;
		vertexTransformMatrix = clusterRelativeCurrentPositionInverse * clusterRelativeInitPosition;

		//��L�ō쐬�����s��Ɋe���_���Ƃ̉e���x(�d��)�������Ă��ꂼ��ɉ��Z����
		for(int i = 0; i < cluster->GetControlPointIndicesCount(); ++i)
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
	}

	//�S�Ă̒��_�ƁA���̊e���_�ɉe����^����s����|�����킹�A�ŏI�I�ȍ��W�l�����߂�
	for (int i = 0; i < mesh->GetControlPointsCount(); ++i)
	{
		FbxVector4	outVertex = clusterDeformation[i].MultNormalize(mesh->GetControlPointAt(i));
		vertexDatas[i].x = static_cast<float>(outVertex[0]);
		vertexDatas[i].y = static_cast<float>(outVertex[1]);
		vertexDatas[i].z = static_cast<float>(outVertex[2]);
	}

	//�N���X�^�̍폜
	Utility::SafeDeleteArray(clusterDeformation);
}






//�T�v: SDK�S�̂̊Ǘ�(�}�l�W���[)�N���X�𐶐�
void	FbxModel::CreateManager()
{
	fbxManager = FbxManager::Create();
}
//�T�v: FBX�̃C���|�[�^�𐶐�
void	FbxModel::CreateImporter()
{
	fbxImporter = FbxImporter::Create(fbxManager, "");
}

//�T�v: FBX�t�H�[�}�b�g�̃`�F�b�N
//�߂�l: �����Ȃ�true
bool	FbxModel::CheckFormat()
{
	const char* fileName = "sample.fbx";
	int fileFormat = -1;
	if (!plugin->DetectReaderFileFormat(fileName, fileFormat))
	{
		//�擾���s
		return false;
	}
	if (!plugin->DetectWriterFileFormat(fileName, fileFormat))
	{
		return false;
	}

	fbxImporter->Initialize(fileName);
	return true;
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


//�T�v: �I�u�W�F�N�g�̐���
void	FbxModel::CreateObject()
{
	scene = FbxScene::Create(fbxManager, "");	
}
//�T�v: �����󂯎��
void	FbxModel::ReciveInfo()
{
	fbxImporter->Import(scene);	//�V�[���̍쐬
	fbxImporter->Destroy();
}

//�T�v: ���{��p�X�ɑΉ�����UTF8�t�H�[�}�b�g�̐�΃p�X���擾
void	FbxModel::GetUTF8AbsFilePath(const std::string& filePath, char outAbsFilePath[512])
{
	char fullPath[512];
	_fullpath(fullPath, filePath.c_str(), 512);
	//FBX_ANSI_to_UTF8()�}�N��
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





//�T�v: UV�����擾����
void	FbxModel::GetUVInfo()
{
	
}

//�T�v: UV���W���擾����
void	FbxModel::GetUVPos()
{
	
}



//�T�v: �}�e���A���I�u�W�F�N�g���擾
void	FbxModel::GetMaterialObject()
{
	
}


//�T�v: �e�N�X�`�����̎擾
void	FbxModel::GetTexture()
{
	
}

//�T�v: ���f���̈ʒu���擾
void	FbxModel::GetModelPos()
{
	
}