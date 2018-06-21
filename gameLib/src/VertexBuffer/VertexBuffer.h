#pragma once
#include <vector>
#include "../../src/Device/DXDevice/DXDevice.h"



//---------------------------------------------------------------------
//!@brief 頂点バッファ
//---------------------------------------------------------------------
class VertexBuffer
{
public:

	//!@brief	ベクトル
	class Vec3
	{
	public:
		Vec3() { x = 0; y = 0; z = 0; }
		Vec3(float x, float y, float z)
			: x(x),y(y),z(z)
		{

		}
		float x, y, z;
	};

	//!@brief	頂点1つの情報
	struct Vertex
	{
		Vec3		position;	//座標
	};

public:
	//!@brief	コンストラクタ
	VertexBuffer(const int& vertexNum);
	~VertexBuffer();

	//!@brief	 頂点バッファの描画
	void	Render();


public:
	//!@brief		頂点データの作成
	void	Create();

	//!@brief		インプットレイアウトの取得
	D3D11_INPUT_ELEMENT_DESC* GetInputLayout();

	
private:
	int					vertexNum;
	ID3D11Buffer*		vertexBuf;

	UINT	stride;		//ストライド
	UINT	offset;		//オフセット

	D3D11_INPUT_ELEMENT_DESC	layout[7];
};
