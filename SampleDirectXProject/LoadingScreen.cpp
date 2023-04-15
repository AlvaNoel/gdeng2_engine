#include "LoadingScreen.h"

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
	if (ImGui::Button("Load"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if(ImGui::Button("Delete"))
	{
		//do delete here noel
	}


	ImGui::Text("Scene 2");
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete"))
	{
		//do delete here noel
	}

	ImGui::Text("Scene 3");
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete"))
	{
		//do delete here noel
	}

	ImGui::Text("Scene 4");
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete"))
	{
		//do delete here noel
	}

	ImGui::Text("Scene 5");
	ImGui::ProgressBar(0, ImVec2(0.0f, 0.0f));
	if (ImGui::Button("Load"))
	{
		//do load here noel
	}
	ImGui::SameLine();
	if (ImGui::Button("Delete"))
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