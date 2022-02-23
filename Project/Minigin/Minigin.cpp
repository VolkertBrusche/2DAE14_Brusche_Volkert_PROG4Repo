#include "MiniginPCH.h"
#include "Minigin.h"
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"

//Game Components ================
#include "TextComponent.h"
#include "TextureComponent.h"
#include "TransformComponent.h"
#include "FPSComponent.h"
//================================

#include "GameObject.h"
#include "Scene.h"
#include <chrono>

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

	//Testing RemoveComponent
	std::shared_ptr<FPSComponent> textComp = std::make_shared<FPSComponent>(backgroundObject);
	backgroundObject->AddComponent(textComp);
	backgroundObject->RemoveComponent(backgroundObject->GetComponent<FPSComponent>());
	scene.Add(backgroundObject);

	//Testing child&parent
	//auto go1 = std::make_shared<GameObject>();
	//auto go2 = std::make_shared<GameObject>();
	//auto go3 = std::make_shared<GameObject>();

	//go2->SetParent(go1);
	//go3->SetParent(go1);

	//go1->SetParent(go3);
	//go1->SetParent(go2);

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

		bool doContinue = true;
		auto lastTime = chrono::high_resolution_clock::now();
		float lag = 0.0f;
		while (doContinue)
		{
			const auto currentTime = chrono::high_resolution_clock::now();
			float deltaTime = chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;
			lag += deltaTime;
			doContinue = input.ProcessInput();
			while (lag >= fixedTimeStep)
			{
				sceneManager.FixedUpdate(fixedTimeStep);
				lag -= fixedTimeStep;
			}
			sceneManager.Update(deltaTime);
			renderer.Render();
		}
	}

	Cleanup();
}
