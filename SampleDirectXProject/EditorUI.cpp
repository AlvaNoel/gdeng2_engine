#include "EditorUI.h"

EditorUI::EditorUI() : name("")
{
}

EditorUI::EditorUI(std::string _name) : name(_name)
{
}

std::string EditorUI::GetName() const
{
    return name;
}
