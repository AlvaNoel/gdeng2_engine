#pragma once
#include "IETThread.h"
#include "GameObjectManager.h"

class ThreadLoading: public IETThread
{
private:
	typedef std::string String;
public:
	ThreadLoading(int id,int objCount, GameObject* obj, std::vector<GameObject*>* gameObjectListScene, std::unordered_map<std::string, GameObject*>* gameObjectMapScene);
	~ThreadLoading();
	void dismiss();
private:
	void run() override;

	int id;
	int objCount;
	GameObject* obj;

	std::vector<GameObject*>* gameObjectListScene;
	std::unordered_map<std::string, GameObject*>* gameObjectMapScene;
public:
	bool isRunning;
};

