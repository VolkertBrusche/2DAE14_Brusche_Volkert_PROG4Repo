#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "Commands.h"

//Game Components ================
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
#include "ImGuiComponent.h"
#include "PeterPepperComponent.h"
#include "HealthComponent.h"
#include "PointsComponent.h"
//================================

//Observers ======================
#include "Achievements.h"
#include "DisplayObserver.h"
//================================

#include "GameObject.h"
#include "Scene.h"
#include <chrono>
#include <ratio>

//#include <steam_api.h>

using namespace std;

void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void dae::Minigin::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		640,
		480,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void dae::Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	std::shared_ptr<GameObject> backgroundObject = std::make_shared<GameObject>();
	std::shared_ptr<TextureComponent> textureComponent = std::make_shared<TextureComponent>(backgroundObject);
	textureComponent->SetTexture("background.jpg");
	backgroundObject->AddComponent(textureComponent);
	std::shared_ptr<TransformComponent> transformComponent = std::make_shared<TransformComponent>(backgroundObject);
	backgroundObject->AddComponent(transformComponent);

	std::shared_ptr<GameObject> logoObject = std::make_shared<GameObject>();
	textureComponent = std::make_shared<TextureComponent>(logoObject);
	textureComponent->SetTexture("logo.png");
	logoObject->AddComponent(textureComponent);
	transformComponent = std::make_shared<TransformComponent>(logoObject);
	transformComponent->SetPosition(216, 180);
	logoObject->AddComponent(transformComponent);
	scene.Add(logoObject);

	std::shared_ptr<GameObject> titleObject = std::make_shared<GameObject>();
	auto titleFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	std::shared_ptr<TextComponent> textComponent = std::make_shared<TextComponent>("Programming 4 Assignment", titleFont, titleObject);
	titleObject->AddComponent(textComponent);
	transformComponent = std::make_shared<TransformComponent>(titleObject);
	transformComponent->SetPosition(80, 20);
	titleObject->AddComponent(transformComponent);
	scene.Add(titleObject);

	std::shared_ptr<GameObject> FPSObject = std::make_shared<GameObject>();
	auto FPSFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	textComponent = std::make_shared<TextComponent>("00 FPS", FPSFont, FPSObject);
	textComponent->SetColor({ 255, 255, 0 });
	FPSObject->AddComponent(textComponent);
	transformComponent = std::make_shared<TransformComponent>(FPSObject);
	transformComponent->SetPosition(10, 10); 
	FPSObject->AddComponent(transformComponent);
	std::shared_ptr<FPSComponent> fpsComponent = std::make_shared<FPSComponent>(FPSObject);
	FPSObject->AddComponent(fpsComponent);
	scene.Add(FPSObject);

	//InputManager
	auto& input = InputManager::GetInstance();

	//Observers
	Achievements* pAchievements = new Achievements();
	DisplayObserver* pDisplayObserver = new DisplayObserver();

	//Observer & Event Queue test
	//PeterPepperObj 1 ======================================================================================================
	std::shared_ptr<GameObject> peterpepperObject = std::make_shared<GameObject>();
	std::shared_ptr<PeterPepperComponent> peterPepperComponent = std::make_shared<PeterPepperComponent>(peterpepperObject);
	peterpepperObject->AddComponent(peterPepperComponent);

	std::shared_ptr<GameObject> healthObject = std::make_shared<GameObject>();
	std::shared_ptr<HealthComponent> healthComponent = std::make_shared<HealthComponent>(healthObject, 3);
	healthComponent->AddObserver(pAchievements);
	healthComponent->AddObserver(pDisplayObserver);
	healthObject->AddComponent(healthComponent);
	textComponent = std::make_shared<TextComponent>("Lives: 0", FPSFont, healthObject);
	textComponent->SetText("Lives: " + std::to_string(healthComponent->GetLives()));
	textComponent->SetColor({ 255, 255, 0 });
	healthObject->AddComponent(textComponent);
	transformComponent = std::make_shared<TransformComponent>(healthObject);
	transformComponent->SetPosition(10, 200);
	healthObject->AddComponent(transformComponent);

	std::shared_ptr<GameObject> pointsObject = std::make_shared<GameObject>();
	std::shared_ptr<PointsComponent> pointsComponent = std::make_shared<PointsComponent>(pointsObject);
	pointsComponent->AddObserver(pDisplayObserver);
	pointsObject->AddComponent(pointsComponent);
	textComponent = std::make_shared<TextComponent>("Points: 0", FPSFont, pointsObject);
	textComponent->SetColor({ 255, 255, 0 });
	pointsObject->AddComponent(textComponent);
	transformComponent = std::make_shared<TransformComponent>(pointsObject);
	transformComponent->SetPosition(10, 220);
	pointsObject->AddComponent(transformComponent);
	
	peterpepperObject->AddChild(healthObject);
	peterpepperObject->AddChild(pointsObject);

	scene.Add(peterpepperObject);

	input.SetButtonCommand(0, XBox360Controller::ControllerButton::ButtonY, new KillPlayer(peterpepperObject), CommandState::Down);
	input.SetButtonCommand(0, XBox360Controller::ControllerButton::ButtonX, new AddPointsCommand(peterpepperObject), CommandState::Down);
	//========================================================================================================================

	//PeterPepperObj 2 ======================================================================================================
	peterpepperObject = std::make_shared<GameObject>();
	peterPepperComponent = std::make_shared<PeterPepperComponent>(peterpepperObject);
	peterpepperObject->AddComponent(peterPepperComponent);

	healthObject = std::make_shared<GameObject>();
	healthComponent = std::make_shared<HealthComponent>(healthObject, 3);
	healthComponent->AddObserver(pAchievements);
	healthComponent->AddObserver(pDisplayObserver);
	healthObject->AddComponent(healthComponent);
	textComponent = std::make_shared<TextComponent>("Lives: 0", FPSFont, healthObject);
	textComponent->SetText("Lives: " + std::to_string(healthComponent->GetLives()));
	textComponent->SetColor({ 0, 255, 0 });
	healthObject->AddComponent(textComponent);
	transformComponent = std::make_shared<TransformComponent>(healthObject);
	transformComponent->SetPosition(10, 300);
	healthObject->AddComponent(transformComponent);

	pointsObject = std::make_shared<GameObject>();
	pointsComponent = std::make_shared<PointsComponent>(pointsObject);
	pointsComponent->AddObserver(pDisplayObserver);
	pointsObject->AddComponent(pointsComponent);
	textComponent = std::make_shared<TextComponent>("Points: 0", FPSFont, pointsObject);
	textComponent->SetColor({ 0, 255, 0 });
	pointsObject->AddComponent(textComponent);
	transformComponent = std::make_shared<TransformComponent>(pointsObject);
	transformComponent->SetPosition(10, 320);
	pointsObject->AddComponent(transformComponent);

	peterpepperObject->AddChild(healthObject);
	peterpepperObject->AddChild(pointsObject);

	scene.Add(peterpepperObject);

	input.SetButtonCommand(0, XBox360Controller::ControllerButton::ButtonA, new KillPlayer(peterpepperObject), CommandState::Down);
	input.SetButtonCommand(0, XBox360Controller::ControllerButton::ButtonB, new AddPointsCommand(peterpepperObject), CommandState::Down);
	//========================================================================================================================
	auto htpFont = ResourceManager::GetInstance().LoadFont("Lingua.otf", 12);

	std::string htp1{ "How to play: Press Y to kill player one || Press X to increase points of player one" };
	std::shared_ptr<GameObject> htpObject = std::make_shared<GameObject>();
	textComponent = std::make_shared<TextComponent>(htp1, htpFont, htpObject);
	htpObject->AddComponent(textComponent);
	transformComponent = std::make_shared<TransformComponent>(htpObject);
	transformComponent->SetPosition(10, 100);
	htpObject->AddComponent(transformComponent);
	scene.Add(htpObject);

	htp1 = { "Press A to kill player two || Press B to increase points of player two" };
	htpObject = std::make_shared<GameObject>();
	textComponent = std::make_shared<TextComponent>(htp1, htpFont, htpObject);
	htpObject->AddComponent(textComponent);
	transformComponent = std::make_shared<TransformComponent>(htpObject);
	transformComponent->SetPosition(80, 115);
	htpObject->AddComponent(transformComponent);

	scene.Add(htpObject);
}

void dae::Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void dae::Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		// todo: this update loop could use some work.
		float fixedTimeStep = 0.02f;

		auto lastTime = chrono::high_resolution_clock::now();
		float deltaTime{};

		bool doContinue = true;
		float lag = 0.0f;
		while (doContinue)
		{
			const auto currentTime = chrono::high_resolution_clock::now();
			deltaTime = chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);

			//SteamAPI_RunCallbacks();
			
			while (lag >= fixedTimeStep)
			{
				sceneManager.FixedUpdate(fixedTimeStep);
				lag -= fixedTimeStep;
			}
			renderer.Render();

			auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(MsPerFrame) - std::chrono::high_resolution_clock::now());
			std::this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}
