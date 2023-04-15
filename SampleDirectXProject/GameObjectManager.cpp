#include "GameObjectManager.h"
#include "GameObject.h"
#include "EngineTime.h"

#include "MeshComponent.h"

#include "GraphicsEngine.h"
#include "TextureManager.h"
#include "MeshManager.h"
#include "TransformComponent.h"
#include "PhysicsComponent.h"
#include "EngineBackend.h"
#include "EditorAction.h"
#include <random>

std::vector<ThreadLoading*> ThreadLoadingList;

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager::GameObjectManager()
{
    this->physicsCommon = new PhysicsCommon();
    PhysicsWorld::WorldSettings settings;
    settings.defaultVelocitySolverNbIterations = 50;
    settings.gravity = reactphysics3d::Vector3(0, -9.81, 0);
    this->physicsWorld = this->physicsCommon->createPhysicsWorld(settings);
}

void GameObjectManager::Initialize()
{
    instance = new GameObjectManager();
}

GameObjectManager* GameObjectManager::Get()
{
    return instance;
}

void GameObjectManager::Update()
{
    const float delta = EngineTime::getDeltaTime();

    if (delta > 0.0f)
    {
        if (EngineBackend::Get()->GetMode() == EditorMode::PLAY || 
            (EngineBackend::Get()->GetMode() == EditorMode::PAUSED && EngineBackend::Get()->InsideFrameStep()))
            physicsWorld->update(delta);
        for (const auto& gameObject : gameObjectList)
        {
            if(gameObject->IsEnable())
				gameObject->Update(delta);
        }
        for (const auto& gameObject : gameObjectListScene1)
        {
            if (gameObject->IsEnable())
                gameObject->Update(delta);
        }
        for (const auto& gameObject : gameObjectListScene2)
        {
            if (gameObject->IsEnable())
                gameObject->Update(delta);
        }
        for (const auto& gameObject : gameObjectListScene3)
        {
            if (gameObject->IsEnable())
                gameObject->Update(delta);
        }
        for (const auto& gameObject : gameObjectListScene4)
        {
            if (gameObject->IsEnable())
                gameObject->Update(delta);
        }
        for (const auto& gameObject : gameObjectListScene5)
        {
            if (gameObject->IsEnable())
                gameObject->Update(delta);
        }

    }
}

void GameObjectManager::CreateGameObject()
{
    GameObject* newObj = GameObject::Instantiate();
    gameObjectList.push_back(newObj);

    SelectGameObject(newObj);
}

GameObject* GameObjectManager::CreateCube()
{
    GameObject* cube = GameObject::Instantiate(NAME_CUBE);
    cube->SetObjectType(PrimitiveType::CUBE);

    if (TransformComponent* transform = cube->GetTransform())
    {
        float rand = std::rand() % 5;
        //transform->SetPosition({ rand, 5, rand });
    }

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\cube.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");
    
    if (mesh)
    {
        MeshComponent* meshComponent = new MeshComponent();
        cube->AttachComponent(meshComponent);
        meshComponent->SetMesh(mesh);
        //meshComponent->SetTexture(texture);
    }

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_CUBE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        cube->SetName(NAME_CUBE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(cube);
    gameObjectMap.emplace(cube->GetName(), cube);
    SelectGameObject(cube);

    return cube;
}

void GameObjectManager::CreateCubes(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        GameObject* obj = CreateCube();

        std::random_device rd; // obtain a random number from hardware
        std::mt19937 gen(rd()); // seed the generator
        std::uniform_int_distribution<> distr(-2.5f, 2.5f); // define the range

        obj->GetTransform()->SetPosition({ (float)distr(gen), 10.0f + (float)distr(gen), (float)distr(gen) });

        std::uniform_int_distribution<> distr2(-1.f, 1.f); // define the range

        obj->GetTransform()->SetEulerAngles({ (float)distr2(gen), (float)distr2(gen), (float)distr2(gen) });

        PhysicsComponent* physics = new PhysicsComponent();
        obj->AttachComponent(physics);
    }
}

void GameObjectManager::CreatePhysicsCubes(int amount)
{
    for (int i = 0; i < amount; i++)
    {
        GameObject* cube = CreateCube();
        PhysicsComponent* component = new PhysicsComponent();
        cube->AttachComponent(component);

        if (TransformComponent* transform = cube->GetTransform())
        {
            SimpleMath::Vector3 rand_position = SimpleMath::Vector3(((rand() % 200) - 100) / 150.0f, ((rand() % 200) - 100) / 150.0f, ((rand() % 200) - 100) / 150.0f);
            transform->SetPosition(rand_position);
        }
    }
}

GameObject* GameObjectManager::CreatePlane()
{
    GameObject* plane = GameObject::Instantiate(NAME_PLANE);
    plane->SetObjectType(PrimitiveType::PLANE);
    if (TransformComponent* transform = plane->GetTransform())
    {
        //transform->SetScale({ 5, 0.1f, 5 });
    }

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\plane.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");
    

    if (mesh)
    {
        MeshComponent* meshComponent = new MeshComponent();
        plane->AttachComponent(meshComponent);
        meshComponent->SetMesh(mesh);
        //meshComponent->SetTexture(texture);

        /*PhysicsComponent* physics = new PhysicsComponent();
        plane->AttachComponent(physics);
        physics->GetRigidbody()->setType(BodyType::KINEMATIC);*/
    }

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_PLANE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        plane->SetName(NAME_PLANE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(plane);
    gameObjectMap.emplace(plane->GetName(), plane);
    SelectGameObject(plane);

    return plane;
}

GameObject* GameObjectManager::CreateSphere()
{
    GameObject* obj = GameObject::Instantiate(NAME_SPHERE);
    obj->SetObjectType(PrimitiveType::SPHERE);
    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\sphere.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_SPHERE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_SPHERE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);

    return obj;
}

GameObject* GameObjectManager::CreateCapsule()
{
    GameObject* obj = GameObject::Instantiate(NAME_CAPSULE);
    obj->SetObjectType(PrimitiveType::CAPSULE);
    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\capsule.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_CAPSULE) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_CAPSULE + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);

    return obj;
}

GameObject* GameObjectManager::CreateCylinder()
{
    GameObject* obj = GameObject::Instantiate(NAME_CYLINDER);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\cylinder.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_CYLINDER) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_CYLINDER + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);

    return obj;
}

void GameObjectManager::CreateScene1()
{
    
    //GameObject* Scene1 = GameObject::Instantiate("NAME_OBJECT_SCENE_1");
    //GameObject* obj2 = GameObject::Instantiate("NAME_OBJECT_2");
    //GameObject* obj3 = GameObject::Instantiate("NAME_OBJECT_3");
    //GameObject* obj4 = GameObject::Instantiate("NAME_OBJECT_4");
    //GameObject* obj5 = GameObject::Instantiate("NAME_OBJECT_5");

    //thread
    for (int i = 0; i < 5; i++)
    {
        GameObject* obj = GameObject::Instantiate("NAME_OBJECT_" + std::to_string(i));

        int randZ = (rand() % 20);
        float randX = (rand() % 20);
        obj->GetTransform()->SetPosition(SimpleMath::Vector3(randX, 1, randZ));
        obj->SetEnable(false);

        ThreadLoading* threadLoading = new ThreadLoading(1, i,obj, &gameObjectListScene1, &gameObjectMapScene1);
        ThreadLoadingList.push_back(threadLoading);
        threadLoading->start();
    }
	/*Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\DMC.obj");

    MeshComponent* meshComponent = new MeshComponent();
    obj1->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);*/

    //mutex
    //gameObjectListScene1.push_back(obj1);
	//gameObjectMapScene1.emplace(obj1->GetName(), obj1);
}

void GameObjectManager::CreateScene2()
{
    for (int i = 0; i < 5; i++)
    {
        GameObject* obj = GameObject::Instantiate("NAME_OBJECT_" + std::to_string(i));

        int randZ = (rand() % 20);
        float randX = (rand() % 20);
        obj->GetTransform()->SetPosition(SimpleMath::Vector3(randX, 1, randZ));
        obj->SetEnable(false);

        ThreadLoading* threadLoading = new ThreadLoading(2, i, obj, &gameObjectListScene2, &gameObjectMapScene2);
        ThreadLoadingList.push_back(threadLoading);
        threadLoading->start();
    }
}

void GameObjectManager::CreateScene3()
{
    for (int i = 0; i < 5; i++)
    {
        GameObject* obj = GameObject::Instantiate("NAME_OBJECT_" + std::to_string(i));

        int randZ = (rand() % 20);
        float randX = (rand() % 20);
        obj->GetTransform()->SetPosition(SimpleMath::Vector3(randX, 1, randZ));
        obj->SetEnable(false);

        ThreadLoading* threadLoading = new ThreadLoading(3, i, obj, &gameObjectListScene3, &gameObjectMapScene3);
        ThreadLoadingList.push_back(threadLoading);
        threadLoading->start();
    }
}

void GameObjectManager::CreateScene4()
{
    for (int i = 0; i < 5; i++)
    {
        GameObject* obj = GameObject::Instantiate("NAME_OBJECT_" + std::to_string(i));

        int randZ = (rand() % 20);
        float randX = (rand() % 20);
        obj->GetTransform()->SetPosition(SimpleMath::Vector3(randX, 1, randZ));
        obj->SetEnable(false);

        ThreadLoading* threadLoading = new ThreadLoading(4, i, obj, &gameObjectListScene4, &gameObjectMapScene4);
        ThreadLoadingList.push_back(threadLoading);
        threadLoading->start();
    }
}

void GameObjectManager::CreateScene5()
{
    for (int i = 0; i < 5; i++)
    {
        GameObject* obj = GameObject::Instantiate("NAME_OBJECT_" + std::to_string(i));

        int randZ = (rand() % 20);
        float randX = (rand() % 20);
        obj->GetTransform()->SetPosition(SimpleMath::Vector3(randX, 1, randZ));
        obj->SetEnable(false);

        ThreadLoading* threadLoading = new ThreadLoading(5, i, obj, &gameObjectListScene5, &gameObjectMapScene5);
        ThreadLoadingList.push_back(threadLoading);
        threadLoading->start();
    }
}

void GameObjectManager::unloadScene(int scene)
{
    switch(scene)
    {
    case 1: for (int i = 4; i >= 0; i--)
        {
            gameObjectListScene1[i]->SetEnable(false);
            delete gameObjectListScene1[i];
        }
              gameObjectListScene1.clear();
    	break;
    case 2: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene2[i]->SetEnable(false);
        delete gameObjectListScene2[i];
    }
          gameObjectListScene2.clear();
          break;
    case 3: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene3[i]->SetEnable(false);
        delete gameObjectListScene3[i];
    }
          gameObjectListScene3.clear();
          break;
    case 4: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene4[i]->SetEnable(false);
        delete gameObjectListScene4[i];
    }
          gameObjectListScene4.clear();
          break;
    case 5: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene5[i]->SetEnable(false);
        delete gameObjectListScene5[i];
    }
          gameObjectListScene5.clear();
          break;
    }

	
}

void GameObjectManager::enableScene(int scene)
{
    switch (scene)
    {
    case 1: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene1[i]->SetEnable(true);
    }
          break;
    case 2: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene2[i]->SetEnable(true);
    }
          break;
    case 3: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene3[i]->SetEnable(true);
    }
          break;
    case 4: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene4[i]->SetEnable(true);
    }
          break;
    case 5: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene5[i]->SetEnable(true);
    }
          break;
    }
}

void GameObjectManager::disableScene(int scene)
{
    switch (scene)
    {
    case 1: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene1[i]->SetEnable(false);
    }
          break;
    case 2: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene2[i]->SetEnable(false);
    }
          break;
    case 3: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene3[i]->SetEnable(false);
    }
          break;
    case 4: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene4[i]->SetEnable(false);
    }
          break;
    case 5: for (int i = 4; i >= 0; i--)
    {
        gameObjectListScene5[i]->SetEnable(false);
    }
          break;
    }
}


GameObject* GameObjectManager::FindObjectByName(std::string name)
{
    if (this->gameObjectMap[name] != NULL) {
        return this->gameObjectMap[name];
    }
    else {
        std::cout << "Object " << name << " not found!";
        return nullptr;
    }
}

void GameObjectManager::ApplyEditorAction(EditorAction* action)
{
    GameObject* object = FindObjectByName(action->GetOwnerName());
    if (object != nullptr) {
        //re-apply state
        /*object->recomputeMatrix(action->getStoredMatrix().getMatrix());
        object->setPosition(action->getStorePos());
        object->setRotation(action->getStoredOrientation().x, action->getStoredOrientation().y, action->getStoredOrientation().z);
        object->setScale(action->getStoredScale());*/
        if (TransformComponent* transform = object->GetTransform())
        {
            transform->SetPosition(action->GetStorePos());
            transform->SetRotation(action->GetStoredOrientation());
            transform->SetScale(action->GetStoredScale());
        }
    }
}

void GameObjectManager::CreateTeapot()
{
    GameObject* obj = GameObject::Instantiate(NAME_TEAPOT);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\teapot.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\brick.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_TEAPOT) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_TEAPOT + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateBunny()
{
    GameObject* obj = GameObject::Instantiate(NAME_BUNNY);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\bunny.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\ground.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_BUNNY) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_BUNNY + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateArmadillo()
{
    GameObject* obj = GameObject::Instantiate(NAME_ARMADILLO);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\armadillo.obj");
    //Texture* texture = GraphicsEngine::get()->getTextureManager()->CreateTextureFromFile(L"Assets\\Textures\\grass.png");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);
    //meshComponent->SetTexture(texture);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_ARMADILLO) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_ARMADILLO + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateLucy()
{
    GameObject* obj = GameObject::Instantiate(NAME_LUCY);

    Mesh* mesh = GraphicsEngine::get()->getMeshManager()->CreateMeshFromFile(L"Assets\\Meshes\\statue.obj");

    MeshComponent* meshComponent = new MeshComponent();
    obj->AttachComponent(meshComponent);
    meshComponent->SetMesh(mesh);

    int i = 0;

    for (const auto& pair : gameObjectMap)
    {
        if (pair.first.find(NAME_LUCY) != std::string::npos)
        {
            i++;
        }
    }

    if (i > 0)
        obj->SetName(NAME_LUCY + " (" + std::to_string(i) + ')');

    gameObjectList.push_back(obj);
    gameObjectMap.emplace(obj->GetName(), obj);
    SelectGameObject(obj);
}

void GameObjectManager::CreateObjectFromFile(std::string name, PrimitiveType type, SimpleMath::Vector3 position, SimpleMath::Vector3 rotation, SimpleMath::Vector3 scale, bool hasPhysics)
{
    GameObject* obj = nullptr;

    switch (type)
    {
    case PrimitiveType::CUBE:
        obj = CreateCube();
        break;
    case PrimitiveType::SPHERE:
        obj = CreateSphere();
        break;
    case PrimitiveType::PLANE:
        obj = CreatePlane();
        break;
    case PrimitiveType::CAPSULE:
        obj = CreateCapsule();
        break;
    }

    obj->GetTransform()->SetPosition(position);
    obj->GetTransform()->SetEulerAngles(rotation);
    obj->GetTransform()->SetScale(scale);

    if (hasPhysics)
    {
        PhysicsComponent* physics = new PhysicsComponent();
        obj->AttachComponent(physics);
    }
}

void GameObjectManager::SaveEditStates()
{
    for (auto* obj : gameObjectList)
    {
        obj->SaveEditState();
    }
}

void GameObjectManager::RestoreEditStates()
{
    for (auto* obj : gameObjectList)
    {
        obj->RestoreEditState();
    }
}

void GameObjectManager::SelectGameObject(GameObject* inObj)
{
    selectedObj = inObj;

    if (MeshComponent* mesh = selectedObj->GetComponent<MeshComponent>())
        mesh->SetOutlined(true);
}

GameObject* GameObjectManager::GetSelectedGameObject() const
{
    return selectedObj;
}

const std::vector<GameObject*>& GameObjectManager::GetGameObjectList() const
{
    return gameObjectList;
}

const std::vector<GameObject*> GameObjectManager::GetRoots() const
{
    std::vector<GameObject*> roots;

    for (const auto& gameObject : gameObjectList)
    {
        if (gameObject->IsRoot())
            roots.push_back(gameObject);
    }

    return roots;
}

PhysicsWorld* GameObjectManager::GetPhysicsWorld()
{
    return physicsWorld;
}

PhysicsCommon* GameObjectManager::GetPhysicsCommon()
{
    return physicsCommon;
}
