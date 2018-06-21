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
	//���_�f�[�^���ێ�����Ă���m�[�h��ǂݍ��ݎ擾����
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


//�T�v: ���_�̏����擾
void	FbxModel::GetVertexInfo()
{
	controlNum = mesh->GetControlPointsCount();	//���_���擾
	src = mesh->GetControlPoints();				//���_���W�z��
	
	//�R�s�[
	Math::Vector4*	controlArray = new Math::Vector4[controlNum];
	for (int i = 0; i < controlNum; ++i)
	{
		controlArray[i].x = src[i][0];
		controlArray[i].y = src[i][1];
		controlArray[i].z = src[i][2];
		controlArray[i].w = src[i][3];

	}
	
}


//�T�v: ���b�V���̖@���̎擾
void	FbxModel::GetMeshNormal()
{
	//���C���[�I�u�W�F�N�g���擾
	int layerNum = mesh->GetLayerCount();
	for (int i = 0; i < layerNum; ++i)
	{
		normalLayer = mesh->GetLayer(i);
		//�@�����`�F�b�N
		normalElem = normalLayer->GetNormals();
		if (normalElem == 0)
		{
			continue;
		}
		//�@��������
	}
}

//�T�v: �@���x�N�g���̕������擾
void	FbxModel::GetNormalMethod()
{
	//�}�b�s���O���[�h�E���t�@�����X���[�h�̎擾
	FbxLayerElement::EMappingMode	mappingMode = normalElem->GetMappingMode();
	FbxLayerElement::EReferenceMode	refMode = normalElem->GetReferenceMode();

	int	normalNum = normalElem->GetDirectArray().GetCount();
	int	indexNum = normalElem->GetIndexArray().GetCount();
	Math::Vector4*	normalBuf = new Math::Vector4[normalNum];

	if (mappingMode == FbxLayerElement::eByPolygonVertex)
	{
		if (refMode == FbxLayerElement::eDirect)
		{
			//���ڎ擾
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
			//���ڎ擾
			for (int i = 0; i < normalNum; ++i)
			{
				normalBuf[i].x = (float)normalElem->GetDirectArray().GetAt(i)[0];
				normalBuf[i].y = (float)normalElem->GetDirectArray().GetAt(i)[1];
				normalBuf[i].z = (float)normalElem->GetDirectArray().GetAt(i)[2];
			}
		}
	}
}


//�T�v: UV�����擾����
void	FbxModel::GetUVInfo()
{
	int layerCount = mesh->GetLayerCount();	//mesh����擾
	for (int i = 0; i < layerCount; ++i)
	{
		uvLayer = mesh->GetLayer(i);
		uvElem = uvLayer->GetUVs();
		if (uvElem == 0)
		{
			continue;
		}
		//UV�����擾����
	}
}

//�T�v: UV���W���擾����
void	FbxModel::GetUVPos()
{
	int uvNum = uvElem->GetDirectArray().GetCount();
	int indexNum = uvElem->GetIndexArray().GetCount();
	int size = uvNum > indexNum ? uvNum : indexNum;
	Math::Vector4*	buffer = new Math::Vector4[size];

	//�}�b�s���O���[�h�E���t�@�����X���[�h�ʂɎ擾
	FbxLayerElement::EMappingMode	mappingMode = uvElem->GetMappingMode();
	FbxLayerElement::EReferenceMode	refMode = uvElem->GetReferenceMode();


	if (mappingMode == FbxLayerElement::eByPolygonVertex) {
		if (refMode == FbxLayerElement::eDirect) {
			// ���ڎ擾
			for (int i = 0; i < size; ++i) {
				buffer[i].x = (float)uvElem->GetDirectArray().GetAt(i)[0];
				buffer[i].y = (float)uvElem->GetDirectArray().GetAt(i)[1];
			}
		}
		else
			if (refMode == FbxLayerElement::eIndexToDirect) {
				// �C���f�b�N�X����擾
				for (int i = 0; i < size; ++i) {
					int index = uvElem->GetIndexArray().GetAt(i);
					buffer[i].x = (float)uvElem->GetDirectArray().GetAt(index)[0];
					buffer[i].y = (float)uvElem->GetDirectArray().GetAt(index)[1];
				}
			}
	}
}



//�T�v: �}�e���A���I�u�W�F�N�g���擾
void	FbxModel::GetMaterialObject()
{
	materialNode = mesh->GetNode();
	if (materialNode == 0) { return; }

	//�}�e���A����
	int materialNum = materialNode->GetMaterialCount();
	if (materialNum == 0) { return; }

	//�}�e���A�������擾
	for (int i = 0; i < materialNum; ++i)
	{
		material = materialNode->GetMaterial(i);
		if (material != 0)
		{
			//�}�e���A�����

			//Lambert��Phong��
			if (material->GetClassId().Is(FbxSurfaceLambert::ClassId))
			{
				//lambert�Ƀ_�E���L���X�g
				FbxSurfaceLambert*	lambert = (FbxSurfaceLambert*)material;
				DirectX::XMVECTOR	ambient_;
				DirectX::XMVECTOR	diffuse_;
				DirectX::XMVECTOR	emissive_;
				DirectX::XMFLOAT3	bump_;
				DirectX::XMVECTOR	transparency_;
				
				//// �A���r�G���g
				//ambient_.r = (float)lambert->Ambient.Get()[0];
				//ambient_.r = (float)lambert->Ambient.Get()[1];
				//ambient_.g = (float)lambert->Ambient.Get()[2];

				//// �f�B�t���[�Y
				//diffuse_.r = (float)lambert->Diffuse.Get()[0];
				//diffuse_.g = (float)lambert->Diffuse.Get()[1];
				//diffuse_.b = (float)lambert->Diffuse.Get()[2];

				//// �G�~�b�V�u
				//emissive_.r = (float)lambert->Emissive.Get()[0];
				//emissive_.g = (float)lambert->Emissive.Get()[1];
				//emissive_.b = (float)lambert->Emissive.Get()[2];

				//// �o���v
				//bump_.x = (float)lambert->Bump.Get()[0];
				//bump_.y = (float)lambert->Bump.Get()[1];
				//bump_.z = (float)lambert->Bump.Get()[2];

				//// ���ߓx
				//transparency_ = (float)lambert->TransparencyFactor.Get();


			}
			else if (material->GetClassId().Is(FbxSurfacePhong::ClassId))
			{
				FbxSurfacePhong*	phong = (FbxSurfacePhong*)material;

				//�����p�[�h�����擾
				
				//���
				DirectX::XMVECTOR	specular;
				float	shininess;
				float	reflectivity;
				//�X�y�L����
				/*specular.r = (float)phong->Specular.Get()[0];
				specular.g = (float)phong->Specular.Get()[1];
				specular.b = (float)phong->Specular.Get()[2];*/

				//����
				shininess = (float)phong->Shininess.Get();

				//����
				reflectivity = (float)phong->ReflectionFactor.Get();
			}
		}
	}
}


//�T�v: �e�N�X�`�����̎擾
void	FbxModel::GetTexture()
{
	//�f�B�t���[�Y�v���p�e�B�̌���
	texProperty = material->FindProperty(FbxSurfaceMaterial::sDiffuse);
	//�v���p�e�B�������Ă��郌�C���[�h�e�N�X�`���̖������`�F�b�N
	int layerNum = texProperty.GetSrcObjectCount();
	
	//���C���[�h�e�N�X�`�����Ȃ���Βʏ�̃e�N�X�`��
	if (layerNum == 0)
	{
		//�ʏ�̃e�N�X�`���̖������`�F�b�N
		int numNormalTexture = texProperty.GetSrcObjectCount();
		//�����e�N�X�`���ɂ��ăe�N�X�`�������Q�b�g
		for (int i = 0; i < numNormalTexture; ++i)
		{
			fbxTexture = FbxCast<FbxTexture>(texProperty.GetSrcObject());

			//�e�N�X�`���t�@�C���p�X�̎擾
			const char* fileName = fbxTexture->GetName();
			char outTexName[100] = "";
			size_t size = strlen(fileName);
			memcpy(outTexName, fileName, size);
			outTexName[size] = '\0';

			break;
		}
	}
}

//�T�v: ���f���̈ʒu���擾
void	FbxModel::GetModelPos()
{
	int time = 0;
	modelNode = mesh->GetNode();

	//�^�C�����[�h�̎擾
	//1�t���[���P�ʂňʒu���擾�ł���
	FbxGlobalSettings&	gloabalTime = scene->GetGlobalSettings();
	time = gloabalTime.GetTimeMode();


}