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

	IETThread::sleep(1000);

	const wchar_t* path = L"";

	

	switch(id)
	{
	case 1:	
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\monitor.obj"; break;
		case 1:path = L"Assets\\Meshes\\bunny.obj"; break;
		case 2:path = L"Assets\\Meshes\\box.obj"; break;
		case 3:path = L"Assets\\Meshes\\capsule.obj"; break;
		case 4:path = L"Assets\\Meshes\\teapot.obj"; break;

		}break;
	case 2:
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\armadillo.obj"; break;
		case 1:path = L"Assets\\Meshes\\asteroid.obj"; break;
		case 2:path = L"Assets\\Meshes\\karanbit.obj"; break;
		case 3:path = L"Assets\\Meshes\\spaceship.obj"; break;
		case 4:path = L"Assets\\Meshes\\torus.obj"; break;

		}break;
	case 3:
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\statue.obj"; break;
		case 1:path = L"Assets\\Meshes\\bunny.obj"; break;
		case 2:path = L"Assets\\Meshes\\box.obj"; break;
		case 3:path = L"Assets\\Meshes\\capsule.obj"; break;
		case 4:path = L"Assets\\Meshes\\teapot.obj"; break;

		}break;
	case 4:
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\plane.obj"; break;
		case 1:path = L"Assets\\Meshes\\bunny.obj"; break;
		case 2:path = L"Assets\\Meshes\\box.obj"; break;
		case 3:path = L"Assets\\Meshes\\capsule.obj"; break;
		case 4:path = L"Assets\\Meshes\\teapot.obj"; break;

		}break;
	case 5:
		switch (objCount)
		{
		case 0:path = L"Assets\\Meshes\\plane.obj"; break;
		case 1:path = L"Assets\\Meshes\\bunny.obj"; break;
		case 2:path = L"Assets\\Meshes\\box.obj"; break;
		case 3:path = L"Assets\\Meshes\\capsule.obj"; break;
		case 4:path = L"Assets\\Meshes\\teapot.obj"; break;

		}break;
	}

	
	Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(path); 

	MeshComponent* meshComponent = new MeshComponent();
	obj->AttachComponent(meshComponent);
	meshComponent->SetMesh(mesh);

	

	

	GameObjectManager::Get()->Semaphore->acquire();
	gameObjectListScene->push_back(obj);
	//gameObjectMapScene->emplace(obj->GetName(), obj);
	GameObjectManager::Get()->Semaphore->release();

	isRunning = false;
}
