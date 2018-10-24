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


//ファイル読み込み
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
		//!@brief	コンストラクタ
		BulletDebugDraw();
		//!@brief	デストラクタ
		virtual ~BulletDebugDraw();

		//!@brief	描画モード
		enum class DrawMode
		{
			NoDebug = 0,
			DrawWireFrame = 1,
			DrawAABB = 2,
		};

	public:
		//!@brief	デバッグの描画
		void	Draw();
		//!@brief	カメラ行列のセット
		//!@param[in]	camera	カメラ(view * proj)
		//void	SetCameraMatrix(Camera& camera);
	public:
		//!@brief	直方体の作成
		void	CreateBox();
		//!@brief	球の作成
		void	CreateSphere();
		//!@brief	円柱の作成
		void	CreateCylinder();
		//!@brief	円錐の作成
		void	CreteCone();
		//!@brief	カプセルの作成
		void	CreateCapsule();
	private:
		//!@brief	DirectX11に必要なリソースの構築
		virtual void	Setup();
	public:
		//!@brief	デバッグ描画モードの設定
		//!@param[in]	drawMode	描画モード
		virtual void	setDebugMode(int drawMode) override;
		//!@brief	デバッグ描画モードの取得
		//!@return	mode番号
		virtual int		getDebugMode() const override;
		//!@brief	ラインの描画
		//!@param[in]	from	始点
		//!@param[in]	to	終点
		//!@param[in]	color	色
		virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
		//!@brief	ラインの描画
		//!@param[in]	from	始点
		//!@param[in]	to	終点
		//!@param[in]	fromColor	始点の色
		//!@param[in]	toColor	終わりの色
		virtual void	drawLine(const btVector3& from, const btVector3& to, const btVector3& fromColor, const btVector3& toColor) override;
		//!@brief	ラインの描画実行
		virtual void	flushLines() override;

		//!@brief	プロジェクション変換行列の設定
		//!@param[in]	projMatrix	プロジェクション変換行列
		void	SetProjMatrix(const DirectX::XMMATRIX& projMatrix);
		//!@brief	ビュー変換行列の設定
		//!@param[in]	viewMatrix	ビュー変換行列
		void	SetViewMatrix(const DirectX::XMMATRIX& viewMatrix);
	private:
		virtual void	drawContactPoint(const btVector3& point, const btVector3& normal, btScalar distance, int lifeTime, const btVector3& color) override;
		virtual void	reportErrorWarning(const char* warningString) override;
		virtual void	draw3dText(const btVector3& location, const char* textString) override;
	private:
		//!@brief	描画時のシーン空間
		struct RenderScene
		{
			DirectX::XMMATRIX	projMatrix;
			DirectX::XMMATRIX	viewMatrix;
		};
		//!@brief	頂点データ
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
		//!@brief	ラインデータ
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


	
	//メッシュモデル
	class MeshModel
	{
		//メッシュデータ
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

		//メッシュ用の定数バッファ
		struct MeshCBuffer
		{
			DirectX::XMMATRIX	world;
			DirectX::XMFLOAT4	diffuse;
			int					texture;
		};

		//メッシュのシェーダデータ
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
		//!@brief	コンストラクタ
		MeshModel();
		//!@brief	デストラクタ
		~MeshModel();
	public:
		bool	Create(const MeshData& meshInfo);
		void	Draw(const DirectX::XMMATRIX& transform);

		//!@brief	メッシュデータのロード
		bool	LoadMeshData();
		//!@brief	球の作成
		void	CreateSphere();
		//!@brief	直方体の作成
		void	CreateBox();
		//!@brief	円柱の作成
		void	CreateCylinder();
		//!@brief	カプセルの作成
		void	CreateCapsule();
		//!@brief	円錐の作成
		void	CreateCone();

		//!@brief	カメラ行列の取得
		//!@param[in]	camera	カメラ(view * proj)
		//void	SetCameraMatrix(Camera& camera);
	};
}