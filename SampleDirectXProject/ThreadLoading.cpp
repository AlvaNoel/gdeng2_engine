#include "ThreadLoading.h"
#include <iostream>
#include <string>

#include "GraphicsEngine.h"
#include "Mesh.h"
#include "MeshComponent.h"
#include "TransformComponent.h"


ThreadLoading::ThreadLoading(int id, int objCount ,GameObject* obj, std::vector<GameObject*>* gameObjectListScene, std::unordered_map<std::string, GameObject*>* gameObjectMapScene)
{
	this->id = id;
	this->objCount = objCount;
	this->obj = obj;

	this->gameObjectListScene = gameObjectListScene;
	this->gameObjectMapScene = gameObjectMapScene;
	std::string str = "Creating thread: " + std::to_string(objCount) + "\n";
	std::cout << str;

	
}

ThreadLoading::~ThreadLoading()
{
	std::string str = "Destroying thread: " + std::to_string(objCount) + "\n";
	std::cout << str;
}

void ThreadLoading::dismiss()
{
	delete this;
}

void ThreadLoading::run()
{
	isRunning = true;

	

	const wchar_t* path = L"";

	

	switch(id)
	{
	case 1:	
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\cube.obj"; obj->GetTransform()->SetScale(SimpleMath::Vector3(1, 1, 1)); break;
		case 1:path = L"Assets\\Meshes\\cube.obj"; obj->GetTransform()->SetScale(SimpleMath::Vector3(1, 1, 1)); break;
		case 2:path = L"Assets\\Meshes\\cube.obj"; break;
		case 3:path = L"Assets\\Meshes\\cube.obj"; break;
		case 4:path = L"Assets\\Meshes\\cube.obj"; break;

		}break;
	case 2:
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\cube.obj"; break;
		case 1:path = L"Assets\\Meshes\\cube.obj"; break;
		case 2:path = L"Assets\\Meshes\\cube.obj"; break;
		case 3:path = L"Assets\\Meshes\\cube.obj"; break;
		case 4:path = L"Assets\\Meshes\\cube.obj"; break;

		}break;
	case 3:
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\cube.obj"; break;
		case 1:path = L"Assets\\Meshes\\cube.obj"; break;
		case 2:path = L"Assets\\Meshes\\cube.obj"; break;
		case 3:path = L"Assets\\Meshes\\cube.obj"; break;
		case 4:path = L"Assets\\Meshes\\cube.obj"; break;

		}break;
	case 4:
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\cube.obj"; break;
		case 1:path = L"Assets\\Meshes\\cube.obj"; break;
		case 2:path = L"Assets\\Meshes\\cube.obj"; break;
		case 3:path = L"Assets\\Meshes\\cube.obj"; break;
		case 4:path = L"Assets\\Meshes\\cube.obj"; break;

		}break;
	case 5:
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\cube.obj"; break;
		case 1:path = L"Assets\\Meshes\\cube.obj"; break;
		case 2:path = L"Assets\\Meshes\\cube.obj"; break;
		case 3:path = L"Assets\\Meshes\\cube.obj"; break;
		case 4:path = L"Assets\\Meshes\\cube.obj"; break;

		}break;
	}

	IETThread::sleep(1000);

	GameObjectManager::Get()->Mutex->acquire();

	/*if (id = 1)
		GameObjectManager::Get()->meshaphore->acquire();
	if (id = 2)
		GameObjectManager::Get()->meshaphore2->acquire();
	if (id = 3)
		GameObjectManager::Get()->meshaphore3->acquire();
	if (id = 4)
		GameObjectManager::Get()->meshaphore4->acquire();
	if (id = 5)
		GameObjectManager::Get()->meshaphore5->acquire();*/

	IETThread::sleep(100);
	
	Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(path); 

	obj->GetComponent<MeshComponent>()->SetMesh(mesh);

	/*if (id = 1)
		GameObjectManager::Get()->meshaphore->release();
	if (id = 2)
		GameObjectManager::Get()->meshaphore2->release();
	if (id = 3)
		GameObjectManager::Get()->meshaphore3->release();
	if (id = 4)
		GameObjectManager::Get()->meshaphore4->release();
	if (id = 5)
		GameObjectManager::Get()->meshaphore5->release();*/
	GameObjectManager::Get()->Mutex->release();
	
	GameObjectManager::Get()->progressBar[id - 1]++;
	std::cout << " progressBar: " << id <<GameObjectManager::Get()->progressBar[id] << std::endl;
	
	
	/*if(id = 1)
	 *
		GameObjectManager::Get()->Mutex->acquire();
	else if (id = 2)
		GameObjectManager::Get()->Mutex2->acquire();
	else if (id = 3)
		GameObjectManager::Get()->Mutex3->acquire();
	else if (id = 4)
		GameObjectManager::Get()->Mutex4->acquire();
	else if (id = 5)
		GameObjectManager::Get()->Mutex5->acquire();*/

	
	
	//gameObjectMapScene->emplace(obj->GetName(), obj);

	/*if (id = 1)
		GameObjectManager::Get()->Mutex->release();
	else if (id = 2)
		GameObjectManager::Get()->Mutex2->release();
	else if (id = 3)
		GameObjectManager::Get()->Mutex3->release();
	else if (id = 4)
		GameObjectManager::Get()->Mutex4->release();
	else if (id = 5)
		GameObjectManager::Get()->Mutex5->release();*/

	isRunning = false;
}
