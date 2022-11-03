#pragma once
#include <string>

class EditorUI
{
public:
	EditorUI();
	EditorUI(std::string _name);

public:
	std::string GetName() const;

public:
	virtual void Draw() = 0;

private:
	std::string name;
};

