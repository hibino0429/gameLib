#include "GameMain.h"
#include "../../src/Utility/Utility.hpp"
#include "../../src/Engine/Engine.h"
#include "../../src/GLEngine/GLDevice/GLDevice.h"
#include "../../src/DXEngine/Input/KeyBoard/KeyBoard.h"



//�R���X�g���N�^
GameMain::GameMain()
{
	//GuiInitialize();
	gameController = new GameController();
	gameController->Initialize();
}

//�f�X�g���N�^
GameMain::~GameMain()
{
	Utility::SafeDelete(gameController);
	//GuiFinalize();
}

//�X�V����
void	GameMain::UpDate()
{
	//GuiUpDate();
	gameController->UpDate();
}


//�`�揈��
void	GameMain::Render()
{
	//GuiRender();
	gameController->Render2D();
	gameController->Render3D();

	/*ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());*/
	Engine<DXDevice>::GetDevice().GetSwapChain().Present(0, 0);
}






//!@brief	GUI�̏�����
void	GameMain::GuiInitialize()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	//GUI�̃V�X�e���̐���
	guiSystem = new GUISystem();

	//DirectX11��ImGui�̏�����
	ImGui_ImplWin32_Init(Engine<DXDevice>::GetDevice().GetScreen().GetHWND());
	ImGui_ImplDX11_Init(&Engine<DXDevice>::GetDevice().GetDevice3D(), &Engine<DXDevice>::GetDevice().GetDeviceContext3D());
}

//!@brief	GUI�̏I��
void	GameMain::GuiFinalize()
{
	Utility::SafeDelete(guiSystem);
	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

//!@brief	GUI�̍X�V
void	GameMain::GuiUpDate()
{
	//ImGui�̃t���[���̃X�^�[�g
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	guiSystem->GetImGuiIO().DisplaySize = ImVec2(1280, 720);
	guiSystem->GetImGuiIO().DeltaTime = 1.0f / 60.0f;
}

//!@brief	GUI�̕`��
void	GameMain::GuiRender()
{
	ImGui::Text("Hello,World");
	ImGui::ColorEdit3("clearColor", (float*)&clearColor);
	ImGui::Checkbox("DemoWindow", &showDemoWindow);
	if (ImGui::Button("Button"))
	{
		showAnotherWindow = true;
	}
	ImGui::SameLine();
	ImGui::Text("hazimaruyo");
	

	//show Window
	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}

	//GUI�v���O����
	{
		//�E�B���h�E���o��
		static float f = 0.0f;
		static int	count = 0;

		ImGui::Begin("Hello World");
		ImGui::Checkbox("Demo Window", &showDemoWindow);
		ImGui::Checkbox("Another Window", &showAnotherWindow);

		ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
		ImGui::ColorEdit3("Clear Color", (float*)&clearColor);


		if (ImGui::Button("Button"))
		{
			count++;
		}
		ImGui::SameLine();
		ImGui::Text("count = %d", count);
		ImGui::Text("Application : %.3f ms/frame", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);

		ImGui::End();

	}

	//���̃E�B���h�E���o��
	if (!showAnotherWindow)
	{
		ImGui::Begin("Another Window", &showAnotherWindow);
		ImGui::Text("Hello from another Window");
		if (ImGui::Button("Close Me"))
		{
			showAnotherWindow = false;
		}
		ImGui::End();
	}


	ImGui::Begin("FirstTool", &showAnotherWindow, ImGuiWindowFlags_MenuBar);
	if (ImGui::BeginMenu("File"))
	{
		if (ImGui::MenuItem("�I�[�v��", "Ctrl�L�[+O")) {}
		if (ImGui::MenuItem("�ۑ�", "Ctrl�L�[+S")) {}
		if (ImGui::MenuItem("����", "Ctrl�L�[+W")) {}
		ImGui::EndMenu();
	}
	//�F�G�f�B�^
	ImGui::ColorEdit4("Color", (float*)&clearColor);
	//�l�̃v���b�v
	const float value[] = { 0.2f,0.1f,1.0f,0.5f,0.9f,2.2f };
	ImGui::PlotLines("�t���[������", value, IM_ARRAYSIZE(value));

	//�X�N���[���̈�̕\�����e
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "�d�v");
	ImGui::BeginChild("�X�N���[��");
	for (int i = 0; i < 50; ++i)
	{
		ImGui::Text("%04d : Some Text", i);
	}
	ImGui::EndChild();
	ImGui::End();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}




