
#include "AppWindow.h"

#include "EngineTime.h"
#include "InputSystem.h"
#include "RenderSystem.h"

#include "GameObject.h"
#include "Cube.h"
#include "Plane.h"
#include "MeshComponent.h"
#include "TransformComponent.h"
#include "RotationMovementComponent.h"

#include "CameraManager.h"
#include "CameraComponent.h"

#include "SceneCamera.h"

#include "imgui.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx11.h"


#include <Windows.h>
#include <tchar.h>

AppWindow::AppWindow()
{
}

AppWindow::~AppWindow()
{
}

AppWindow* AppWindow::sharedInstance = nullptr;

AppWindow* AppWindow::Get()
{
	return sharedInstance;
}

void AppWindow::Initialize()
{
	sharedInstance = new AppWindow();
}

void AppWindow::update()
{
}

void AppWindow::onCreate()
{
	Window::onCreate();
	srand(time(NULL));
	
	sceneCamera = new SceneCamera();
	InputSystem::get()->addListener(sceneCamera);
	sceneCamera->GetTransform()->SetPosition(Vector3D(0.0f, 1.0f, -2.5f));

	GraphicsEngine::get()->init();
	RECT rc = this->getClientWindowRect();
	m_swap_chain=GraphicsEngine::get()->getRenderSystem()->createSwapChain(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setRenderTargets(this->m_swap_chain);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setRenderState(this->m_swap_chain);

	Cube* cube = new Cube();
	Plane* plane = new Plane();

	/*auto* rot_1 = new RotationMovementComponent();
	rot_1->SetRotationRate(90.0f);
	auto* rot_2 = new RotationMovementComponent();
	rot_2->SetRotationRate(360.0f);*/

	gameObject_0 = GameObject::Instantiate();
	
	MeshComponent* mesh_0 = new MeshComponent();
	mesh_0->SetMesh(plane);
	gameObject_0->AttachComponent(mesh_0);

	gameObject_1 = GameObject::Instantiate();

	MeshComponent* mesh_1 = new MeshComponent();
	mesh_1->SetMesh(cube);
	gameObject_1->AttachComponent(mesh_1);

	gameObject_0->AttachChild(gameObject_1);

	/*RotationMovementComponent* rot_0 = new RotationMovementComponent();
	rot_0->SetRotationRate(1.0f);
	rot_0->SetAxis(Vector3D::upVector);
	gameObject_0->AttachComponent(rot_0);*/

	gameObjects.push_back(gameObject_0);
	gameObjects.push_back(gameObject_1);

	/*gameObject_1 = GameObject::Instantiate();
	gameObject_1->GetTransform()->SetPosition({ 1, 0, 1 });
	gameObject_1->GetTransform()->SetScale({ 0.5f, 0.5f, 0.5f });
	gameObject_1->AttachComponent(rot_1);
	gameObject_1->GetComponent<MeshComponent>()->SetMesh(cube);

	gameObject_2 = GameObject::Instantiate();
	gameObject_2->GetTransform()->SetPosition({ -1, 0, 0 });
	gameObject_2->GetTransform()->SetScale({ 0.3f, 0.3f, 0.3f });
	gameObject_2->AttachComponent(rot_2);
	gameObject_2->GetComponent<MeshComponent>()->SetMesh(cube);

	gameObject_0->AttachChild(gameObject_1);
	gameObject_1->AttachChild(gameObject_2);*/

	// LOW_VALUE - std::rand() / (RAND_MAX / HIGH_VALUE - LOW_VALUE);
	// 1 - std::rand() / (RAND_MAX / 2 - 1);


	/*GameObject* cameraObject = GameObject::Instantiate();
	CameraComponent* cameraComponent = new CameraComponent();

	cameraObject->AttachComponent(cameraComponent);
	cameraObject->GetTransform()->SetPosition(Vector3D::zeroVector);

	gameObjects.push_back(cameraObject);*/

	/*gameObject_0 = GameObject::Instantiate();
	gameObject_0->transform->SetPosition(Vector3D(0, 0, 0));
	gameObject_0->GetComponent<MeshComponent>()->SetMesh(plane);

	gameObject_1 = GameObject::Instantiate();
	gameObject_1->transform->SetPosition(Vector3D(0, 0, 0));
	gameObject_1->GetComponent<MeshComponent>()->SetMesh(cube);*/

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();

	auto* rs = GraphicsEngine::get()->getRenderSystem();

	ImGui_ImplWin32_Init(m_hwnd);
	ImGui_ImplDX11_Init(rs->m_d3d_device, rs->m_imm_context);
}

void AppWindow::onUpdate()
{
	Window::onUpdate();

	InputSystem::get()->update();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (show_demo_window)
		ImGui::ShowDemoWindow(&show_demo_window);

	ImGui::Begin("Hello, world!");
	ImGui::Text("This is some useful text.");
	ImGui::Checkbox("Demo Window", &show_demo_window);
	ImGui::End();

	ImGui::Render();

	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearRenderTargetColor(this->m_swap_chain, 0.5f, 0.5f, 0.5f, 1.0f);
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->clearDepthStencilView(this->m_swap_chain);

	RECT rc = this->getClientWindowRect();
	GraphicsEngine::get()->getRenderSystem()->getImmediateDeviceContext()->setViewportSize(rc.right - rc.left, rc.bottom - rc.top);

	const float deltaTime = (float)EngineTime::getDeltaTime();

	// Update scene camera
	sceneCamera->Update(deltaTime);

	for (GameObject* gameObject : gameObjects)
	{
		gameObject->Update(deltaTime);
	}

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	m_swap_chain->present(true);
}

void AppWindow::onDestroy()
{
	Window::onDestroy();

	GraphicsEngine::get()->release();
	InputSystem::get()->removeListener(sceneCamera);

	for (GameObject* gameObject : gameObjects)
	{
		delete gameObject;
	}

	gameObjects.clear();

	delete sceneCamera;

	ImGui_ImplDX11_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void AppWindow::onFocus()
{
	InputSystem::get()->addListener(sceneCamera);
}

void AppWindow::onKillFocus()
{
	InputSystem::get()->removeListener(sceneCamera);
}
