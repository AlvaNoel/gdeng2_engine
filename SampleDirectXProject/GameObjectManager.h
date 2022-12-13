#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "GameObject.h"
#include "SimpleMath.h"
#include <reactphysics3d/reactphysics3d.h>

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
	GameObject* CreatePlane();
	void CreateTeapot();
	void CreateBunny();
	void CreateArmadillo();
	GameObject* CreateSphere();
	GameObject* CreateCapsule();
	GameObject* CreateCylinder();

public:
	void CreateObjectFromFile(PrimitiveType type, SimpleMath::Vector3 position, SimpleMath::Vector3 rotation, SimpleMath::Vector3 scale, bool hasPhysics);

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
private:
	PhysicsCommon* physicsCommon;
	PhysicsWorld* physicsWorld;
};

