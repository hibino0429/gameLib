// meshdata cone
D3D11_INPUT_ELEMENT_DESC mesh_layout[3] = {
	{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
};

UINT layout_num = 3;
UINT vertex_stride = 32;
UINT vertex_num = 50;
UINT index_num = 96;
FLOAT diffuse[4] = {1.0f, 1.0f, 1.0f, 1.0f};

FLOAT mesh_vertex[400] = {	
	-0.707107f, -1.0f, -0.707107f, -0.632455f, 0.447214f, -0.632456f, 0.875f, 1.0f, 
	-0.707107f, -1.0f, -0.707107f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-0.923879f, -1.0f, -0.382684f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-0.923879f, -1.0f, -0.382684f, -0.826343f, 0.447214f, -0.342283f, 0.8125f, 1.0f, 
	-0.382683f, -1.0f, -0.92388f, -0.342282f, 0.447214f, -0.826343f, 0.9375f, 1.0f, 
	-0.382683f, -1.0f, -0.92388f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, -1.0f, -1.0f, 2.58255e-07f, 0.447214f, -0.894427f, 0.0f, 1.0f, 
	-1.0f, -1.0f, -0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-1.0f, -1.0f, -0.0f, -0.894427f, 0.447214f, -5.28249e-08f, 0.75f, 1.0f, 
	0.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, -1.0f, -1.0f, 2.58255e-07f, 0.447214f, -0.894427f, 1.0f, 1.0f, 
	0.382683f, -1.0f, -0.92388f, 0.342282f, 0.447214f, -0.826343f, 0.0625f, 1.0f, 
	0.382683f, -1.0f, -0.92388f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-0.92388f, -1.0f, 0.382684f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-0.92388f, -1.0f, 0.382684f, -0.826343f, 0.447214f, 0.342283f, 0.6875f, 1.0f, 
	0.0f, -1.0f, -0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	0.707107f, -1.0f, -0.707107f, 0.632456f, 0.447214f, -0.632456f, 0.125f, 1.0f, 
	0.707107f, -1.0f, -0.707107f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-0.707107f, -1.0f, 0.707107f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-0.707107f, -1.0f, 0.707107f, -0.632455f, 0.447214f, 0.632456f, 0.625f, 1.0f, 
	0.92388f, -1.0f, -0.382683f, 0.826343f, 0.447214f, -0.342282f, 0.1875f, 1.0f, 
	0.92388f, -1.0f, -0.382683f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-0.382683f, -1.0f, 0.92388f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	-0.382683f, -1.0f, 0.92388f, -0.342282f, 0.447214f, 0.826343f, 0.5625f, 1.0f, 
	1.0f, -1.0f, -0.0f, 0.894427f, 0.447214f, 0.0f, 0.25f, 1.0f, 
	1.0f, -1.0f, -0.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, -1.0f, 1.0f, 1.23258e-07f, 0.447214f, 0.894427f, 0.5f, 1.0f, 
	0.0f, -1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	0.92388f, -1.0f, 0.382684f, 0.826343f, 0.447214f, 0.342282f, 0.3125f, 1.0f, 
	0.382683f, -1.0f, 0.92388f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	0.92388f, -1.0f, 0.382684f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	0.382683f, -1.0f, 0.92388f, 0.342282f, 0.447214f, 0.826343f, 0.4375f, 1.0f, 
	0.707107f, -1.0f, 0.707107f, 0.632455f, 0.447214f, 0.632456f, 0.375f, 1.0f, 
	0.707107f, -1.0f, 0.707107f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f, 
	0.0f, 1.0f, -0.0f, 0.481563f, 0.498674f, -0.720709f, 0.0625f, 0.0f, 
	0.0f, 1.0f, -0.0f, 0.720709f, 0.498674f, -0.481562f, 0.09375f, 0.0f, 
	0.0f, 1.0f, -0.0f, 0.850134f, 0.498674f, -0.169103f, 0.125f, 0.0f, 
	0.0f, 1.0f, -0.0f, 0.850134f, 0.498674f, 0.169102f, 0.15625f, 0.0f, 
	0.0f, 1.0f, -0.0f, 0.720709f, 0.498674f, 0.481562f, 0.1875f, 0.0f, 
	0.0f, 1.0f, -0.0f, 0.169103f, 0.498674f, -0.850134f, 0.03125f, 0.0f, 
	0.0f, 1.0f, -0.0f, 0.481563f, 0.498674f, 0.720709f, 0.21875f, 0.0f, 
	0.0f, 1.0f, -0.0f, -0.169102f, 0.498674f, -0.850134f, 0.5f, 0.0f, 
	0.0f, 1.0f, -0.0f, -0.850134f, 0.498674f, 0.169102f, 0.375f, 0.0f, 
	0.0f, 1.0f, -0.0f, -0.850134f, 0.498674f, -0.169102f, 0.40625f, 0.0f, 
	0.0f, 1.0f, -0.0f, -0.720709f, 0.498674f, 0.481562f, 0.34375f, 0.0f, 
	0.0f, 1.0f, -0.0f, 0.169102f, 0.498674f, 0.850134f, 0.25f, 0.0f, 
	0.0f, 1.0f, -0.0f, -0.720709f, 0.498674f, -0.481562f, 0.4375f, 0.0f, 
	0.0f, 1.0f, -0.0f, -0.481563f, 0.498674f, 0.720709f, 0.3125f, 0.0f, 
	0.0f, 1.0f, -0.0f, -0.169102f, 0.498674f, 0.850134f, 0.28125f, 0.0f, 
	0.0f, 1.0f, -0.0f, -0.481563f, 0.498674f, -0.720709f, 0.46875f, 0.0f, 
};

UINT mesh_index[96] = {
	6, 39, 11, 11, 34, 16, 16, 35, 20, 20, 36, 24, 24, 37, 28, 28, 38, 
	32, 32, 40, 31, 31, 45, 26, 26, 48, 23, 23, 47, 19, 19, 44, 14, 14, 
	42, 8, 8, 43, 3, 3, 46, 0, 0, 49, 4, 4, 41, 10, 15, 9, 12, 
	15, 12, 17, 15, 17, 21, 15, 21, 25, 15, 25, 30, 15, 30, 33, 15, 33, 
	29, 15, 29, 27, 15, 27, 22, 15, 22, 18, 15, 18, 13, 15, 13, 7, 15, 
	7, 2, 15, 2, 1, 15, 1, 5, 15, 5, 9, 
};

