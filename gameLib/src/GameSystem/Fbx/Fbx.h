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
//!@brief FBX�N���X
//-----------------------------------------------------------------------------
class FbxModel
{
public:
	FbxModel(const std::string& filePath);
	~FbxModel();
private:
	void	LoadFile(const std::string& filePath);
public:
	//!@brief	���_�̐��̎擾
	int			GetVertexDatas();
	//!@brief	���_�f�[�^�̃|���S�����̎擾
	int			GetVertexCount();
	//!@brief	�|���S�����̎擾
	int			GetPolygonCount();
	//!@brief	���_�f�[�^�̎擾
	std::vector<int>&		GetVertexPolygonVertices();
	//!@brief	���_�f�[�^��n��
	std::vector<Vertex>&		GetVertexData();

public:
	////////////////////////////////////////////////////////////
	//�擾����
	////////////////////////////////////////////////////////////
	//!@brief	���݂̃A�j���[�V�����ԍ��̎擾
	const int&	GetNowAnimationNumber() const;
	//!@brief	���݂̃A�j���[�V�������̎擾
	const char*	GetNowAnimationName() const;

	////////////////////////////////////////////////////////////
	//�ݒ菈��
	////////////////////////////////////////////////////////////
	//!@brief	�A�j���[�V�����ԍ��̐ݒ�
	void	SetAnimationNumber(const int& animationNumber);

private:
	//!@brief	�w�肵���m�[�h��T��
	//!@param[in]	nodeType	�T���m�[�h
	//!@return	���������� true ������Ȃ�������@false
	bool		SearchDesignationNode(const FbxNodeAttribute::EType& nodeType);
	//!@brief	���b�V���̐������m�[�h�̓ǂݍ��݂��s��
	void		LoadNodeForMeshNum();
	//!@brief	���b�V���̃f�[�^���󂯎��
	void		SetMeshData();
	//!@brief	���f���̐F���Z�b�g����
public:
	void		SetVertexColor(const float red, const float green, const float blue, const float alpha);
public:
	//!@brief	�A�j���[�V�����̐���
	void	CreateAnimation();
	//!@brief	�A�j���[�V�����̎��Ԃ̐����Ɛݒ�
	void	CreateAnimationTime();
	//!@brief	�A�j���[�V�����̍s��v�Z
	void	AnimationMatrix();

private:
	//�T�v: FBX�t�@�C���̓ǂݍ���
	//�߂�l: �����Ȃ�true
	bool	LoadFbx(const std::string& fileName);

	//�T�v: �q�m�[�h�̐��̎擾
	void	GetChildNodeNum();
	//�T�v: �q�m�[�h�̎擾
	void	GetChildNode();

	//�T�v: �m�[�h�̃^�C�v�̎擾
	void	GetNodeAttribute();

	//�T�v: ���b�V���I�u�W�F�N�g�̎擾
	void	GetMeshObject();
	//�T�v: �|���S���̊�{���̎擾
	void	GetPolygonInfo();

public:
	//!@brief	���f���̃A�j���[�V���������邩�`�F�b�N
	//!@return	true: ���� false: �Ȃ�
	bool	IsAnimation();

private:
	//!@brief	FBX����@�����̊i�[
	bool	StoreMeshNormal();
	//!@brief	FBX����UV���̊i�[
	bool	StoreMeshUV();
	//!@brief	FBX����}�e���A�����̊i�[
	bool	StoreMeshMaterial();
	//!@brief	�擾����Mesh�f�[�^��Vertex�ɓn��
	void	PassMeshData();
	//!@brief	�擾����Mesh��UV����ۑ�
	void	SaveMeshUV(const int num);
	//!@brief	�擾����Mesh�̃}�e���A������ۑ�
	void	SaveMeshMaterial(const int num);
	//!@brief	�擾����Mesh�̖@������ۑ�
	void	SaveMeshNormal(const int num);
	//!@brief	�e�N�X�`�����̎擾
	void	SaveTextureNames();
	//!@brief	�N���X�^�̊i�[
	void	SaveCluster();
	//!@brief	�{�[�����e����^���钸�_���̊i�[
	void	SaveBoneVertexData(FbxCluster* cluster, FbxMatrix* globalPosition, FbxAMatrix* geometryOffset, FbxMatrix* clusterDeformation);

private:
	//�}�e���A��
	//!@brief	�}�e���A�����̊i�[
	void	SaveMaterialData(FbxSurfaceMaterial* material, const int materialNum);
	//!@brief	Lmbert���̊i�[
	void	SaveLambertData(FbxSurfaceLambert* lambert,const int materialNum);
	//!@brief	Phong���̊i�[
	void	SavePhongData(FbxSurfacePhong* phong,const int materialNum);
	//!@brief	Texture���̊i�[
	void	SaveTextureData(FbxSurfaceMaterial* material,const int materialNum);
private:
	//���̎擾
	//!@brief	���擾�̃I�v�V����
	//!@return	true: ���_�P�� false: �|���S���P��
	bool	GetOption();
	//!@brief	���_�P�ʂŏ����擾����
	void	SaveVertexData();
	//!@brief	�|���S���T�m�ŏ����擾����
	void	SavePolygonData();
	//!@brief	���b�V���f�[�^�̎擾
	void	LoadMeshData();
private:
	FbxManager*				fbxManager;		//SDK�R�A�N���X
	FbxImporter*			fbxImporter;	//�C���|�[�^
	FbxIOPluginRegistry*	plugin;			//�v���O�C��
	FbxScene*				scene;			//�V�[��
	FbxNode*				rootNode;		//���[�g�m�[�h
	FbxNode*				childNode;		//�q�m�[�h
	FbxNodeAttribute*		nodeAttribute;	//�m�[�h�^�C�v
	FbxNodeAttribute::EType type;			//�m�[�h�̎��
	FbxMesh*				mesh;			//���b�V��

private:
	int			childNodeNum;		//�q�m�[�h�̐�

	int			polygonNum;			//�|���S����
	int			polygonVertexNum;	//�|���S�����_�C���f�b�N�X��
	int*		polygonIndexArray;	//�|���S�����_�C���f�b�N�X�z��

	int			findNodeTypeNum;	//�m�[�h�^�C�v�������������̔ԍ�

	FbxNode*	meshNode;
	FbxArray<FbxString*>	animStackNameArray;
	int			animStackNumber;
	FbxTime		frameTime;
	FbxTime		timeCount;
	FbxTime		start;
	FbxTime		stop;

	//-------------------------------------------------------
	//FBX�f�[�^���O���ɑ���p�̕ϐ�
	//-------------------------------------------------------
	std::vector<Vertex>	vertexDatas;	//���_�f�[�^
	std::vector<int>	indices;		//�C���f�b�N�X�f�[�^
	int			vertexDataNum;			//���_�f�[�^�̐�
	int			indexDataNum;			//�C���f�b�N�X�f�[�^�̐�
	std::vector<ColorData>	colorDatas;	//�F�f�[�^
};





//���

//FBXManager�́AFBX����舵�����߂̊Ǘ����s��

//FBXScene�́AFBX�t�@�C���Ɋi�[����Ă���V�[���̏���ێ�����

//FBXScene�ɂ́A�m�[�h������A�K�w�\���ŁA���_�f�[�^�E���C�g�E�A�j���[�V�������̕`��ɕK�v�ȏ�񂪂���

//FBX�t�@�C�����璸�_�f�[�^���擾

//GetPolygonVertexCount() �̓C���f�b�N�X�f�[�^�̐����擾

//GetPolygonVertices()�ŃC���f�b�N�X�f�[�^���̂��̂��擾



//------------------
//Node
//------------------
//Node�̒��ɂ���ɁAMesh������A���̒��ɁA���_��񂪊܂܂�Ă���
//Node1��Mesh�ɂ̓��f���̊�f�[�^�ANode2��Mesh�ɂ͕��̃f�[�^�A�̂悤�ɕ����̃m�[�h���i�[�����

//���ӁA�C���f�b�N�X���g�p����ہA1�̒��_��UV���W��2�ȏ゠��ꍇ������
//1: �C���f�b�N�X���g�p���Ȃ�
//2: UV�ɍ��킹�ăC���f�b�N�X����蒼�� color[1] = 1.0f - uv�̐F
//3: ���̂܂ܕʂ̃o�b�t�@�Ƃ���


//------------------
//Material
//------------------
//Material�A�}�e���A���̏��͕�������
//1�̃��f���̃|���S���O���[�v�Ƀ}�e���A���ԍ�0�A�ʂ̃|���S���O���[�v�Ƀ}�e���A���ԍ�1

