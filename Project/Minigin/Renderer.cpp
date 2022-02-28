#include "MiniginPCH.h"
#include "Renderer.h"
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include <backends\imgui_impl_opengl2.h>
#include <backends\imgui_impl_sdl.h>
#include "imgui_plot.h"
#include <chrono>
#include <array>

//Global Variables for Trash the Cache
std::array<int, 1000000> intBuffer{2};

int GetOpenGLDriverIndex()
{
	auto openglIndex = -1;
	const auto driverCount = SDL_GetNumRenderDrivers();
	for (auto i = 0; i < driverCount; i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	//Initialize IMGUI ==================================================
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window, SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();
	//===================================================================
}

void dae::Renderer::Render() const
{
	const auto& color = GetBackgroundColor();
	SDL_SetRenderDrawColor(m_Renderer, color.r, color.g, color.b, color.a);
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	//Run ImGui =============================================
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();

	ImGui::Begin("Exercise 2");
	//ImGui::InputInt("#Samples", &samples);
	if (ImGui::Button("trash the cache"))
		TTCIntBuffer();
	ImGui::End();
	ImGui::Render();

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	//=======================================================

	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	//Destroy IMGUI =========================
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	//=======================================

	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst{};
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

//IMGUI Functions ====================================================
void dae::Renderer::TTCIntBuffer() const
{
	int stepSize{ 1 };
	std::vector<float> results{};
	std::vector<float> stepSizes{};

	while (stepSize <= m_MaxStepSize)
	{
		float deltaTime{};
		for (int repeat = 0; repeat < m_Samples; ++repeat)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (int i = 0; i < intBuffer.size(); i += stepSize)
				intBuffer[i] *= 2;
			auto end = std::chrono::high_resolution_clock::now();
			deltaTime += std::chrono::duration<float, std::milli>(end - start).count();
		}
		deltaTime /= m_Samples;
		results.push_back(deltaTime);
		stepSizes.push_back(static_cast<float>(stepSize));
		stepSize *= 2;
	}

	ImGui::PlotConfig conf;
	conf.values.xs = &stepSizes[0];
	conf.values.ys = &results[0];
	conf.values.count = static_cast<int>(stepSizes.size());
	conf.scale.min = 0;
	conf.scale.max = 25;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.grid_x.show = true;
	conf.grid_y.show = true;
	conf.frame_size = ImVec2(400, 400);
	conf.line_thickness = 2.f;

	ImGui::Plot("Plot", conf);
}
