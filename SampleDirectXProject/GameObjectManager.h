#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "GameObject.h"
#include "SimpleMath.h"
#include <reactphysics3d/reactphysics3d.h>
#include "ThreadLoading.h"
#include "IETSemaphore.h"

using namespace reactphysics3d;
using namespace DirectX;

class GameObject;
class GameObjectManager
{
private:
	static GameObjectManager* instance;

public:
	GameObjectManager();

public:
	static void Initialize();
	static GameObjectManager* Get();

public:
	void Update();

public:
	void CreateGameObject();
	GameObject* CreateCube();
	void CreateCubes(int amount);
	void CreatePhysicsCubes(int amount);
	GameObject* CreatePlane();
	void CreateTeapot();
	void CreateBunny();
	void CreateArmadillo();
	void CreateLucy();
	GameObject* CreateSphere();
	GameObject* CreateCapsule();
	GameObject* CreateCylinder();
	void CreateScene1();
	void CreateScene2();
	void CreateScene3();
	void CreateScene4();
	void CreateScene5();

	void unloadScene(int scene);

	void enableScene(int scene);
	void disableScene(int scene);



public:
	GameObject* FindObjectByName(std::string name);
	void ApplyEditorAction(class EditorAction* action);

public:
	void CreateObjectFromFile(std::string name, PrimitiveType type, SimpleMath::Vector3 position, SimpleMath::Vector3 rotation, SimpleMath::Vector3 scale, bool hasPhysics);

public:
	void SaveEditStates();
	void RestoreEditStates();

public:
	void SelectGameObject(GameObject* inObj);
	GameObject* GetSelectedGameObject() const;

public:
	const std::vector<GameObject*>& GetGameObjectList() const;
	const std::vector<GameObject*> GetRoots() const;

private:
	std::vector<GameObject*> gameObjectList;
	std::unordered_map<std::string, GameObject*> gameObjectMap;
	GameObject* selectedObj;

public:
	IETSemaphore* Mutex = new IETSemaphore(1);
	IETSemaphore* Mutex2 = new IETSemaphore(1);
	IETSemaphore* Mutex3 = new IETSemaphore(1);
	IETSemaphore* Mutex4 = new IETSemaphore(1);
	IETSemaphore* Mutex5 = new IETSemaphore(1);
	IETSemaphore* meshaphore = new IETSemaphore(1);
	IETSemaphore* meshaphore2 = new IETSemaphore(1);
	IETSemaphore* meshaphore3 = new IETSemaphore(1);
	IETSemaphore* meshaphore4 = new IETSemaphore(1);
	IETSemaphore* meshaphore5 = new IETSemaphore(1);

	std::vector<GameObject*> gameObjectListScene1;
	std::unordered_map<std::string, GameObject*> gameObjectMapScene1;

	std::vector<GameObject*> gameObjectListScene2;
	std::unordered_map<std::string, GameObject*> gameObjectMapScene2;

	std::vector<GameObject*> gameObjectListScene3;
	std::unordered_map<std::string, GameObject*> gameObjectMapScene3;

	std::vector<GameObject*> gameObjectListScene4;
	std::unordered_map<std::string, GameObject*> gameObjectMapScene4;

	std::vector<GameObject*> gameObjectListScene5;
	std::unordered_map<std::string, GameObject*> gameObjectMapScene5;

	float progressBar[5];


public:
	PhysicsWorld* GetPhysicsWorld();
	PhysicsCommon* GetPhysicsCommon();

public:
	const std::string NAME_CUBE = "Cube";
	const std::string NAME_PLANE = "Plane";
	const std::string NAME_SPHERE = "Sphere";
	const std::string NAME_CAPSULE = "Capsule";
	const std::string NAME_CYLINDER = "Cylinder";
	const std::string NAME_TEAPOT = "Teapot";
	const std::string NAME_BUNNY = "Bunny";
	const std::string NAME_ARMADILLO = "Armadillo";
	const std::string NAME_LUCY = "Lucy";
private:
	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;
};

