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
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 1"))
	{
		GameObjectManager::Get()->CreateScene1();
	}
	ImGui::SameLine();
	if(ImGui::Button("Delete 1"))
	{
		//do delete here noel
	}


	ImGui::Text("Scene 2");
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 2"))
	{
		std::cout << "button 2";
		GameObjectManager::Get()->CreateScene2();
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete 2"))
	{
		//do delete here noel
	}

	ImGui::Text("Scene 3");
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 3"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete 3"))
	{
		//do delete here noel
	}

	ImGui::Text("Scene 4");
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 4"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete 4"))
	{
		//do delete here noel
	}

	ImGui::Text("Scene 5");
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load 5"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete 5"))
	{
		//do delete here noel
	}

	if (ImGui::Button("Load All"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete All"))
	{
		//do delete here noel
	}

	ImGui::End();
}