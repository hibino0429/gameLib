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
//!@brief FBX�N���X
//-----------------------------------------------------------------------------
class FbxModel
{
public:
	FbxModel(const std::string& filePath);
	~FbxModel();
	void	LoadFile(const std::string& filePath);

private:
	//!@brief	�m�[�h�̒T��
	void		ProbeNode(FbxNode* fbxNode);
public:
	//!@brief	���_�f�[�^�̃R���g���[���|�C���g���̎擾
	int			GetVertexDatas();
	//!@brief	���_�f�[�^�̃|���S�����̎擾
	int			GetVertexCount();
	//!@brief	���_�f�[�^�̎擾
	std::vector<int>&		GetVertexPolygonVertices();
	
	//!@brief	���_�f�[�^��n��
	std::vector<Vertex>&		GetVertexData();

private:
	//!@brief	�w�肵���m�[�h��T��
	//!@param[in]	nodeType	�T���m�[�h
	//!@return	���������� true ������Ȃ�������@false
	bool		SearchDesignationNode(const FbxNodeAttribute::EType& nodeType);
	//!@brief	���b�V���̐������m�[�h�̓ǂݍ��݂��s��
	void		LoadNodeForMeshNum();
	//!@brief	���b�V���̃f�[�^���󂯎��
	void		SetMeshData();

private:
	//!@brief	�A�j���[�V�����̐���
	void	CreateAnimation();
	//!@brief	�A�j���[�V�����̎��Ԃ̐����Ɛݒ�
	void	CreateAnimationTime();
	//!@brief	�A�j���[�V�����̍s��v�Z
	void	AnimationMatrix();

private:
	//�T�v: SDK�S�̂̊Ǘ�(�}�l�W���[)�N���X�𐶐�
	void	CreateManager();
	//�T�v: FBX�̃C���|�[�^�𐶐�
	void	CreateImporter();
	//�T�v: FBX�t�H�[�}�b�g�̃`�F�b�N
	//�߂�l: �����Ȃ�true
	bool	CheckFormat();
	//�T�v: FBX�t�@�C���̓ǂݍ���
	//�߂�l: �����Ȃ�true
	bool	LoadFbx(const std::string& fileName);
	//�T�v: �I�u�W�F�N�g�̐���
	void	CreateObject();
	//�T�v: �����󂯎��
	void	ReciveInfo();
	//�T�v: ���{��p�X�ɑΉ�����UTF8�t�H�[�}�b�g�̐�΃p�X���擾
	void	GetUTF8AbsFilePath(const std::string& filePath, char outAbsFilePath[512]);

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

	//�T�v: ���b�V���̖@���̎擾
	void	GetMeshNormal();

	//�T�v: �@���x�N�g���̕������擾
	void	GetNormalMethod();

	//�T�v: UV�����擾����
	void	GetUVInfo();
	//�T�v: UV���W���擾����
	void	GetUVPos();

	//�T�v: �}�e���A���I�u�W�F�N�g���擾
	void	GetMaterialObject();
	//�T�v: �e�N�X�`�����̎擾
	void	GetTexture();

	//�T�v: ���f���̈ʒu���擾
	void	GetModelPos();

private:
	FbxManager*				fbxManager;		//SDK�R�A�N���X
	FbxImporter*			fbxImporter;	//�C���|�[�^
	FbxIOPluginRegistry*	plugin;	//�v���O�C��
	FbxScene*				scene;		//�V�[��

	FbxNode*				rootNode;	//���[�g�m�[�h
	FbxNode*				childNode;	//�q�m�[�h

	FbxNodeAttribute*		nodeAttribute;	//�m�[�h�^�C�v
	FbxNodeAttribute::EType type;		//�m�[�h�̎��

	FbxMesh*			 mesh;		//���b�V��


private:
	int				controlNum;				//���_��
	FbxVector4*		src;					//���_���W�z�� (fbx�p)
private:
	FbxLayer*				normalLayer;		//���C���[
	FbxLayerElementNormal*	normalElem;			//�@��


private:
	int			childNodeNum;	//�q�m�[�h�̐�

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
	int			vertexDataNum;	//���_�f�[�^�̐�
	int			indexDataNum;	//�C���f�b�N�X�f�[�^�̐�
};





//���

//FBXManager�́AFBX����舵�����߂̊Ǘ����s��

//FBXScene�́AFBX�t�@�C���Ɋi�[����Ă���V�[���̏���ێ�����

//FBXScene�ɂ́A�m�[�h������A�K�w�\���ŁA���_�f�[�^�E���C�g�E�A�j���[�V�������̕`��ɕK�v�ȏ�񂪂���

//FBX�t�@�C�����璸�_�f�[�^���擾

//GetPolygonVertexCount() �̓C���f�b�N�X�f�[�^�̐����擾

//GetPolygonVertices()�ŃC���f�b�N�X�f�[�^���̂��̂��擾