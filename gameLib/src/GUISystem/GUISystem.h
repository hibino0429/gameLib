///////////////////////////////////////////////////////////////
//include
#pragma once
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/GUISystem/imguiDx11/imgui_impl_dx11.h"
#include "../../src/GUISystem/imguiWin32/imgui_impl_win32.h"
#include <Windows.h>


//-------------------------------------------------------------
//!@class		GUISystem
//!@brief	ImGuiを利用したGUIを提供します
//-------------------------------------------------------------
class GUISystem
{
public:
	//!@brief	コンストラクタ
	GUISystem();
	//!@brief	デストラクタ
	~GUISystem();
public:
	//!@brief	更新
	void	Run();
	//!@brief	ImGuiIOの参照の取得
	//!@return	ImGuiIO&
	ImGuiIO&	GetImGuiIO() const;

private:
	//!@brief	プロジェクト用
	void	ProjectView();
	//!@brief	インスペクター用
	void	InspectorView();
	//!@brief	オブジェクト用
	void	ObjectsView();
private:
	ImGuiIO&	io;
};

