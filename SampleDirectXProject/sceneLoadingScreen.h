#pragma once
#include "UIScreen.h"

class sceneLoadingScreen :public UIScreen
{
public:
	sceneLoadingScreen(int scene);
	~sceneLoadingScreen();
	void DrawUI() override;
private:
	int scene;
	bool isActive = false;
};

