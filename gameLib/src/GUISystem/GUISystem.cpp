// ImGui Renderer for: DirectX11
// This needs to be used along with a Platform Binding (e.g. Win32)

// Implemented features:
//  [X] Renderer: User texture binding. Use 'ID3D11ShaderResourceView*' as ImTextureID. Read the FAQ about ImTextureID in imgui.cpp.

// You can copy and use unmodified imgui_impl_* files in your project. See main.cpp for an example of using this.
// If you are new to dear imgui, read examples/README.txt and read the documentation at the top of imgui.cpp
// https://github.com/ocornut/imgui

// CHANGELOG
// (minor and older changes stripped away, please see git history for details)
//  2018-06-08: Misc: Extracted imgui_impl_dx11.cpp/.h away from the old combined DX11+Win32 example.
//  2018-06-08: DirectX11: Use draw_data->DisplayPos and draw_data->DisplaySize to setup projection matrix and clipping rectangle.
//  2018-02-16: Misc: Obsoleted the io.RenderDrawListsFn callback and exposed ImGui_ImplDX11_RenderDrawData() in the .h file so you can call it yourself.
//  2018-02-06: Misc: Removed call to ImGui::Shutdown() which is not available from 1.60 WIP, user needs to call CreateContext/DestroyContext themselves.
//  2016-05-07: DirectX11: Disabling depth-write.

#include "GUISystem.h"


//!@brief	コンストラクタ
GUISystem::GUISystem()
	: io(ImGui::GetIO())
{
	
}
//!@brief	デストラクタ
GUISystem::~GUISystem()
{

}


//!@brief	更新
void	GUISystem::Run()
{
	
}

//!@brief	ImGuiIOの参照の取得
//!@return	ImGuiIO&
ImGuiIO&	GUISystem::GetImGuiIO() const
{
	return io;
}


//!@brief	プロジェクト用
void	GUISystem::ProjectView()
{

}
//!@brief	インスペクター用
void	GUISystem::InspectorView()
{

}
//!@brief	オブジェクト用
void	GUISystem::ObjectsView()
{

}