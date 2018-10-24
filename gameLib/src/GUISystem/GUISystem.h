///////////////////////////////////////////////////////////////
//include
#pragma once
#include "../../src/DXEngine/DXDevice/DXDevice.h"
#include "../../src/GUISystem/imguiDx11/imgui_impl_dx11.h"
#include "../../src/GUISystem/imguiWin32/imgui_impl_win32.h"
#include <Windows.h>


//-------------------------------------------------------------
//!@class		GUISystem
//!@brief	ImGui�𗘗p����GUI��񋟂��܂�
//-------------------------------------------------------------
class GUISystem
{
public:
	//!@brief	�R���X�g���N�^
	GUISystem();
	//!@brief	�f�X�g���N�^
	~GUISystem();
public:
	//!@brief	�X�V
	void	Run();
	//!@brief	ImGuiIO�̎Q�Ƃ̎擾
	//!@return	ImGuiIO&
	ImGuiIO&	GetImGuiIO() const;

private:
	//!@brief	�v���W�F�N�g�p
	void	ProjectView();
	//!@brief	�C���X�y�N�^�[�p
	void	InspectorView();
	//!@brief	�I�u�W�F�N�g�p
	void	ObjectsView();
private:
	ImGuiIO&	io;
};

