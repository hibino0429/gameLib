#pragma once

#if defined(_DEBUG)
#pragma comment(lib,"BulletCollision_vs2010_debug.lib")
#pragma comment(lib,"BulletDynamics_vs2010_debug.lib")
#pragma comment(lib,"BulletSoftBody_vs2010_debug.lib")
#pragma comment(lib,"LinearMath_vs2010_debug.lib")
#else
#pragma comment(lib,"BulletCollision_vs2010.lib")
#pragma comment(lib,"BulletDynamics_vs2010.lib")
#pragma comment(lib,"BulletSoftBody_vs2010.lib")
#pragma comment(lib,"LinearMath_vs2010.lib")
#endif

#include <../Bullet/LinearMath/btIDebugDraw.h>
#include <d3d11.h>
#include <directxmath.h>
#include <vector>
#include <wrl/client.h>
#include "../../src/DXEngine/Math/Math.h"
#include <fstream>
#include <array>
#include <btBulletDynamicsCommon.h>
#include <memory>
#include "../../src/DXEngine/PrimitiveData/PrimitiveData.h"
#include "../../src/Component/Material/Material.h"


using Microsoft::WRL::ComPtr;


//�t�@�C���ǂݍ���
class FileRead
{
public:
	FileRead() {}
	FileRead(const char* filePath)
	{
		Load(filePath);
	}
public:
	bool	Load(const char* filePath)
	{
		if (filePath == nullptr) { return false; }
		std::ifstream	binFile(filePath, std::ios::in | std::ios::binary);
		if (binFile.is_open())
		{
			int fileSize = static_cast<int>(binFile.seekg(0, std::ios::end).tellg());
			binFile.seekg(0, std::ios::beg);
			std::unique_ptr<char> code(new char[fileSize]);
			binFile.read(code.get(), fileSize);
			size = fileSize;
			binary = std::move(code);
		}
		return true;
	}
	const char* Get() const { return binary.get(); }
	const int Size() const { return size; }
private:
	int		size = 0;
	std::unique_ptr<char>	binary;
};




namespace Physics
{
	class MeshModel;
	class MeshData;

	class BulletDebugDraw : public btIDebugDraw
	{
	public:
		//!@brief	�R���X�g���N�^
		BulletDebugDraw();
		//!@brief	�f�X�g���N�^
		virtual ~BulletDebugDraw();

		//!@brief	�`�惂�[�h
		enum class DrawMode
		{
			NoDebug = 0,
			DrawWireFrame = 1,
			DrawAABB = 2,
		};

	public:
		//!@brief	�f�o�b�O�̕`��
		void	Draw();
		//!@brief	�J�����s��̃Z�b�g
		//!@param[in]	camera	�J����(view * proj)
		//void	SetCameraMatrix(Camera& camera);
	public:
		//!@brief	�����̂̍쐬
		void	CreateBox();
		//!@brief	���̍쐬
		void	CreateSphere();
		//!@brief	�~���̍쐬
		void	CreateCylinder();
		//!@brief	�~���̍쐬
		void	CreteCone();
		//!@brief	�J�v�Z���̍쐬
		void	CreateCapsule();
	private:
		//!@brief	DirectX11�ɕK�v�ȃ��\�[�X�̍\�z
		virtual void	Setup();
	public:
		//!@brief	�f�o�b�O�`�惂�[�h�̐ݒ�
		//!@param[in]	drawMode	�`�惂�[�h
		virtual void	setDebugMode(int drawMode) override;
		//!@brief	�f�o�b�O�`�惂�[�h�̎擾
		//!@return	mode�ԍ�
		virtual int		getDebugMode() const override;
		//!@brief	���C���̕`��
		//!@param[in]	from	�n�_
		//!@param[in]	to	�I�_
		//!@param[in]	color	�F
		virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
		//!@brief	���C���̕`��
		//!@param[in]	from	�n�_
		//!@param[in]	to	�I�_
		//!@param[in]	fromColor	�n�_�̐F
		//!@param[in]	toColor	�I���̐F
		virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) override;
		//!@brief	���C���̕`����s
		virtual void	flushLines() override;

		//!@brief	�v���W�F�N�V�����ϊ��s��̐ݒ�
		//!@param[in]	projMatrix	�v���W�F�N�V�����ϊ��s��
		void	SetProjMatrix(const DirectX::XMMATRIX& projMatrix);
		//!@brief	�r���[�ϊ��s��̐ݒ�
		//!@param[in]	viewMatrix	�r���[�ϊ��s��
		void	SetViewMatrix(const DirectX::XMMATRIX& viewMatrix);
	private:
		virtual void	drawContactPoint(const btVector3& point, const btVector3& normal, btScalar distance, int lifeTime, const btVector3& color) override;
		virtual void	reportErrorWarning(const char* warningString) override;
		virtual void	draw3dText(const btVector3& location, const char* textString) override;
	private:
		//!@brief	�`�掞�̃V�[�����
		struct RenderScene
		{
			DirectX::XMMATRIX	projMatrix;
			DirectX::XMMATRIX	viewMatrix;
		};
		//!@brief	���_�f�[�^
		struct Vertex
		{
			Vertex() {}
			Vertex(const btVector3& pos, const btVector3& color)
			{
				this->pos[0] = pos[0];	this->pos[1] = pos[1];	this->pos[2] = pos[2];
				this->color[0] = color[0];	this->color[1] = pos[1];	this->color[2] = color[2];
			}
			float	pos[3];
			float	color[3];
		};
		//!@brief	���C���f�[�^
		struct	Line
		{
			Line() {}
			Line(const Vertex& from, const Vertex& to) : from(from), to(to) {}
			Line(const btVector3& from, const btVector3& to, const btVector3& fromc, const btVector3& toc)
				: from(from, fromc), to(to, toc) {}
			Vertex	from;
			Vertex	to;
		};
	private:
		ComPtr<ID3D11Buffer>			constantBuf;
		ComPtr<ID3D11VertexShader>		vertexShader;
		ComPtr<ID3D11PixelShader>		pixelShader;
		ComPtr<ID3D11InputLayout>		inputLayout;
		ComPtr<ID3D11RasterizerState>	rasterizeState;
		ComPtr<ID3D11DepthStencilState>	depthStencilStateOn;
		ComPtr<ID3D11DepthStencilState>	depthStencilStateOff;
		ComPtr<ID3D11BlendState>		blendState;
		
		RenderScene*		renderScene;
		static const size_t	MaxLine = 100000;
		std::vector<Line>	line;
		DrawMode			mode;
		std::vector<MeshModel*>	meshModels;
	};


	
	//���b�V�����f��
	class MeshModel
	{
		//���b�V���f�[�^
		struct MeshData
		{
			ComPtr<ID3D11Buffer>	cBuffer;
			ComPtr<ID3D11ShaderResourceView>	texSRV;
			ComPtr<ID3D11VertexShader>	vertexShader;
			ComPtr<ID3D11PixelShader>	pixelShader;
			const void* inVS = nullptr;
			const UINT sizeVS = 0;
			UINT	numLayout = 0;
			D3D11_INPUT_ELEMENT_DESC*	layout = nullptr;
			const void* pVertex = nullptr;
			UINT sizeVertex = 0;
			UINT stride = 0;
			const void*	pIndex = nullptr;
			UINT sizeIndex = 0;
			UINT numIndex = 0;
			Math::Vector4		diffuse;
			DirectX::XMMATRIX	transform;
		};

		//���b�V���p�̒萔�o�b�t�@
		struct MeshCBuffer
		{
			DirectX::XMMATRIX	world;
			DirectX::XMFLOAT4	diffuse;
			int					texture;
		};

		//���b�V���̃V�F�[�_�f�[�^
		struct MeshConstant
		{
			ComPtr<ID3D11Buffer>		constantBuf;
			ComPtr<ID3D11VertexShader>	meshVS;
			ComPtr<ID3D11PixelShader>	meshPS;
			FileRead					vsCode;
			FileRead					psCode;
		};

		ComPtr<ID3D11ShaderResourceView>	texSRV;
		std::array<ComPtr<ID3D11Buffer>, 2>	cBuffer;
		ComPtr<ID3D11Buffer>			vertexBuf;
		ComPtr<ID3D11Buffer>			indexBuf;
		ComPtr<ID3D11VertexShader>		vertexShader;
		ComPtr<ID3D11PixelShader>		pixelShader;
		ComPtr<ID3D11InputLayout>		layout;
		ComPtr<ID3D11RasterizerState>	rsState;
		ComPtr<ID3D11BlendState>		blendState;
		ComPtr<ID3D11DepthStencilState>	depthState;
		ComPtr<ID3D11SamplerState>		samplerState;
		UINT							stride;
		UINT							numIndex = 0;
		MeshCBuffer						meshBuf;
		MeshConstant					meshConstant;

	public:
		//!@brief	�R���X�g���N�^
		MeshModel();
		//!@brief	�f�X�g���N�^
		~MeshModel();
	public:
		bool	Create(const MeshData& meshInfo);
		void	Draw(const DirectX::XMMATRIX& transform);

		//!@brief	���b�V���f�[�^�̃��[�h
		bool	LoadMeshData();
		//!@brief	���̍쐬
		void	CreateSphere();
		//!@brief	�����̂̍쐬
		void	CreateBox();
		//!@brief	�~���̍쐬
		void	CreateCylinder();
		//!@brief	�J�v�Z���̍쐬
		void	CreateCapsule();
		//!@brief	�~���̍쐬
		void	CreateCone();

		//!@brief	�J�����s��̎擾
		//!@param[in]	camera	�J����(view * proj)
		//void	SetCameraMatrix(Camera& camera);
	};
}