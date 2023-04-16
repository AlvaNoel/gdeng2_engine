#include "sceneLoadingScreen.h"
#include "GameObjectManager.h"

sceneLoadingScreen::sceneLoadingScreen(int scene) : UIScreen("LoadingScreen", true)
{
	this->scene = scene;
}

sceneLoadingScreen::~sceneLoadingScreen()
{

}

void sceneLoadingScreen::DrawUI()
{
	ImGui::Begin("Scene");

	ImGui::ProgressBar(GameObjectManager::Get()->progressBar[scene] / 5.0f, ImVec2(0.0f, 0.0f));
	ImGui::End();
}