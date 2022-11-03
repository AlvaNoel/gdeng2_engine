#include "EditorUIManager.h"

EditorUIManager::EditorUIManager() = default;

EditorUIManager* EditorUIManager::Get()
{
	return instance;
}
