#include "LoadingScreen.h"
#include "GameObjectManager.h"

LoadingScreen::LoadingScreen() : UIScreen("LoadingScreen", true)
{
}

LoadingScreen::~LoadingScreen()
{
}

void LoadingScreen::DrawUI()
{
	ImGui::Begin("Loading");

	ImGui::Text("Scene 1");
	ImGui::ProgressBar(GameObjectManager::Get()->progressBar[0] /5.0f, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 1"))
	{
		GameObjectManager::Get()->enableScene(1);
		GameObjectManager::Get()->disableScene(2);
		GameObjectManager::Get()->disableScene(3);
		GameObjectManager::Get()->disableScene(4);
		GameObjectManager::Get()->disableScene(5);
	}
	ImGui::SameLine();
	if(ImGui::Button("Delete 1"))
	{
		GameObjectManager::Get()->unloadScene(1);
	}
	ImGui::SameLine();
	if (ImGui::Button("Create 1"))
	{
		GameObjectManager::Get()->CreateScene1();
	}


	ImGui::Text("Scene 2");
	ImGui::ProgressBar(GameObjectManager::Get()->progressBar[1] / 5.0f, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 2"))
	{
		GameObjectManager::Get()->disableScene(1);
		GameObjectManager::Get()->enableScene(2);
		GameObjectManager::Get()->disableScene(3);
		GameObjectManager::Get()->disableScene(4);
		GameObjectManager::Get()->disableScene(5);
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete 2"))
	{
		GameObjectManager::Get()->unloadScene(2);
	}
	ImGui::SameLine();
	if (ImGui::Button("Create 2"))
	{
		GameObjectManager::Get()->CreateScene2();
	}

	ImGui::Text("Scene 3");
	ImGui::ProgressBar(GameObjectManager::Get()->progressBar[2] / 5.0f, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 3"))
	{
		GameObjectManager::Get()->disableScene(1);
		GameObjectManager::Get()->disableScene(2);
		GameObjectManager::Get()->enableScene(3);
		GameObjectManager::Get()->disableScene(4);
		GameObjectManager::Get()->disableScene(5);
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete 3"))
	{
		GameObjectManager::Get()->unloadScene(3);
	}
	ImGui::SameLine();
	if (ImGui::Button("Create 3"))
	{
		GameObjectManager::Get()->CreateScene3();
	}

	ImGui::Text("Scene 4");
	ImGui::ProgressBar(GameObjectManager::Get()->progressBar[3] / 5.0f, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 4"))
	{
		GameObjectManager::Get()->disableScene(1);
		GameObjectManager::Get()->disableScene(2);
		GameObjectManager::Get()->disableScene(3);
		GameObjectManager::Get()->enableScene(4);
		GameObjectManager::Get()->disableScene(5);
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete 4"))
	{
		GameObjectManager::Get()->unloadScene(4);
	}
	ImGui::SameLine();
	if (ImGui::Button("Create 4"))
	{
		GameObjectManager::Get()->CreateScene4();
	}


	ImGui::Text("Scene 5");
	ImGui::ProgressBar(GameObjectManager::Get()->progressBar[4] / 5.0f, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 5"))
	{
		GameObjectManager::Get()->disableScene(1);
		GameObjectManager::Get()->disableScene(2);
		GameObjectManager::Get()->disableScene(3);
		GameObjectManager::Get()->disableScene(4);
		GameObjectManager::Get()->enableScene(5);
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete 5"))
	{
		GameObjectManager::Get()->unloadScene(5);
	}
	ImGui::SameLine();
	if (ImGui::Button("Create 5"))
	{
		GameObjectManager::Get()->CreateScene5();
	}

	if (ImGui::Button("Load All"))
	{
		GameObjectManager::Get()->enableScene(1);
		GameObjectManager::Get()->enableScene(2);
		GameObjectManager::Get()->enableScene(3);
		GameObjectManager::Get()->enableScene(4);
		GameObjectManager::Get()->enableScene(5);
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete All"))
	{
		GameObjectManager::Get()->unloadScene(1);
		GameObjectManager::Get()->unloadScene(2);
		GameObjectManager::Get()->unloadScene(3);
		GameObjectManager::Get()->unloadScene(4);
		GameObjectManager::Get()->unloadScene(5);
	}

	ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
	ImGui::End();
}