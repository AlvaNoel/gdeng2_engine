#pragma once
#include "UIScreen.h"

class LoadingScreen:public UIScreen
{
public:
	LoadingScreen();
	~LoadingScreen();
	void DrawUI() override;
private:

};

