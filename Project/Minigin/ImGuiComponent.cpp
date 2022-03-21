#include "MiniginPCH.h"
#include "ImGuiComponent.h"
#include "BaseComponent.h"
#include "imgui.h"
#include "imgui_plot.h"
#include <backends\imgui_impl_opengl2.h>
#include <backends\imgui_impl_sdl.h>
#include <chrono>
#include <array>

//Used examples at: https://github.com/soulthreads/imgui-plot

//Classes & Structs for Trash the Cache
struct Transform
{
	float matrix[16] = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};
};
class GameObject3D
{
public:
	Transform transform;
	int ID;
};
class GameObject3DAlt
{
public:
	Transform* transform;
	int ID;
};

//Global Variables for Trash the Cache
std::array<int, 1000000> intBuffer{ 2 };
std::array<GameObject3D, 1000000> goBuffer{ GameObject3D{} };
std::array<GameObject3DAlt, 1000000> goAltBuffer{ GameObject3DAlt{} };

dae::ImGuiComponent::ImGuiComponent(std::shared_ptr<GameObject> gameObject, SDL_Window* pWindow)
	:BaseComponent{gameObject}
	,m_pWindow{pWindow}
{
}

dae::ImGuiComponent::~ImGuiComponent()
{
	m_pWindow = nullptr;
}

void dae::ImGuiComponent::Update(float)
{
	//ImGui newFrame
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_pWindow);
	ImGui::NewFrame();

	//Run ImGui =============================================
	ImGui::Begin("Exercise 2", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::InputInt("# samples", &m_SamplesTTCInt);
	if (ImGui::Button("Trash the Cache integers"))
	{
		TTCIntBuffer();
		isTTCintButtonPressed = true;
	}
	if (isTTCintButtonPressed)
	{
		//Trash the cache Integer plot config ======================================
		ImGui::PlotConfig confTTCInt;
		confTTCInt.values.xs = m_StepSizes.data();
		confTTCInt.values.ys = m_ResultsTTCInt.data();
		confTTCInt.values.count = static_cast<int>(m_StepSizes.size());
		confTTCInt.scale.min = 0;
		confTTCInt.scale.max = *std::max_element(m_ResultsTTCInt.cbegin(), m_ResultsTTCInt.cend());
		confTTCInt.tooltip.show = true;
		confTTCInt.tooltip.format = "x=%.2f, y=%.2f";
		confTTCInt.grid_x.show = true;
		confTTCInt.grid_y.show = true;
		confTTCInt.frame_size = ImVec2(200, 100);
		confTTCInt.line_thickness = 2.f;
		ImGui::Plot("Integer Buffer", confTTCInt);
		//==========================================================================
	}
	ImGui::End();

	ImGui::Begin("Exercise 3", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::InputInt("# samples", &m_SamplesTTCGO);
	if (ImGui::Button("Trash the Cache GameObject3D"))
	{
		TTCGoBuffer();
		isTTCGoButtonPressed = true;
	}
	if (isTTCGoButtonPressed)
	{
		//Trash the cache GameObject3D plot config =================================
		float max = *std::max_element(m_ResultsTTCGo.cbegin(), m_ResultsTTCGo.cend());
		if (max > m_MaxElement)
			m_MaxElement = max;

		ImGui::PlotConfig confTTCGo;
		confTTCGo.values.xs = m_StepSizes.data();
		confTTCGo.values.ys = m_ResultsTTCGo.data();
		confTTCGo.values.count = static_cast<int>(m_StepSizes.size());
		confTTCGo.scale.min = 0;
		confTTCGo.scale.max = m_MaxElement;
		confTTCGo.tooltip.show = true;
		confTTCGo.tooltip.format = "x=%.2f, y=%.2f";
		confTTCGo.grid_x.show = true;
		confTTCGo.grid_y.show = true;
		confTTCGo.frame_size = ImVec2(200, 100);
		confTTCGo.line_thickness = 2.f;
		ImGui::Plot("GameObject3D Buffer", confTTCGo);
		//==========================================================================
	}

	if (ImGui::Button("Trash the Cache GameObject3DAlt"))
	{
		TTCGoAltBuffer();
		isTTCGoAltButtonPressed = true;
	}
	if (isTTCGoAltButtonPressed)
	{
		float max = *std::max_element(m_ResultsTTCGoAlt.cbegin(), m_ResultsTTCGoAlt.cend());
		if (max > m_MaxElement)
			m_MaxElement = max;

		//Trash the cache GameObject3DAlt plot config ==============================
		ImGui::PlotConfig confTTCGoAlt;
		confTTCGoAlt.values.xs = m_StepSizes.data();
		confTTCGoAlt.values.ys = m_ResultsTTCGoAlt.data();
		confTTCGoAlt.values.count = static_cast<int>(m_StepSizes.size());
		confTTCGoAlt.scale.min = 0;
		confTTCGoAlt.scale.max = m_MaxElement;
		confTTCGoAlt.tooltip.show = true;
		confTTCGoAlt.tooltip.format = "x=%.2f, y=%.2f";
		confTTCGoAlt.grid_x.show = true;
		confTTCGoAlt.grid_y.show = true;
		confTTCGoAlt.frame_size = ImVec2(200, 100);
		confTTCGoAlt.line_thickness = 2.f;
		ImGui::Plot("GameObject3DAlt Buffer", confTTCGoAlt);
		//==========================================================================
	}
	if (isTTCGoButtonPressed && isTTCGoAltButtonPressed)
	{
		const float* pResultsCombined[] = { m_ResultsTTCGo.data(), m_ResultsTTCGoAlt.data()};

		//Trash the cache GameObject3DAlt plot config ==============================
		ImGui::PlotConfig confTTCCombined;
		confTTCCombined.values.xs = m_StepSizes.data();
		confTTCCombined.values.ys_list = &pResultsCombined[0];
		confTTCCombined.values.ys_count = 2;
		confTTCCombined.values.count = static_cast<int>(m_StepSizes.size());
		confTTCCombined.scale.min = 0;
		confTTCCombined.scale.max = m_MaxElement;
		confTTCCombined.tooltip.show = true;
		confTTCCombined.tooltip.format = "x=%.2f, y=%.2f";
		confTTCCombined.grid_x.show = true;
		confTTCCombined.grid_y.show = true;
		confTTCCombined.frame_size = ImVec2(200, 100);
		confTTCCombined.line_thickness = 2.f;
		ImGui::Plot("Combined Buffer", confTTCCombined);
		//==========================================================================
	}
	ImGui::End();
	//=======================================================
}

void dae::ImGuiComponent::Render() const
{
}

//IMGUI Functions ====================================================
void dae::ImGuiComponent::TTCIntBuffer()
{
	int stepSize{ m_BaseStepSize };
	m_ResultsTTCInt.clear();

	while (stepSize <= m_MaxStepSize)
	{
		float deltaTime{};
		for (int repeat = 0; repeat < m_SamplesTTCInt; ++repeat)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i < intBuffer.size(); i += stepSize)
				intBuffer[i] *= 2;
			auto end = std::chrono::high_resolution_clock::now();
			deltaTime += std::chrono::duration<float, std::milli>(end - start).count();
		}
		deltaTime /= m_SamplesTTCInt;
		m_ResultsTTCInt.push_back(deltaTime);
		stepSize *= 2;
	}
}
void dae::ImGuiComponent::TTCGoBuffer()
{
	int stepSize{ m_BaseStepSize };
	m_ResultsTTCGo.clear();

	while (stepSize <= m_MaxStepSize)
	{
		float deltaTime{};
		for (int repeat = 0; repeat < m_SamplesTTCGO; ++repeat)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i < goBuffer.size(); i += stepSize)
				goBuffer[i].ID = 2;
			auto end = std::chrono::high_resolution_clock::now();
			deltaTime += std::chrono::duration<float, std::milli>(end - start).count();
		}
		deltaTime /= m_SamplesTTCGO;

		m_ResultsTTCGo.push_back(deltaTime);
		stepSize *= 2;
	}
}
void dae::ImGuiComponent::TTCGoAltBuffer()
{
	int stepSize{ m_BaseStepSize };
	m_ResultsTTCGoAlt.clear();

	while (stepSize <= m_MaxStepSize)
	{
		float deltaTime{};
		for (int repeat = 0; repeat < m_SamplesTTCGO; ++repeat)
		{
			auto start = std::chrono::high_resolution_clock::now();
			for (size_t i = 0; i < goAltBuffer.size(); i += stepSize)
				goAltBuffer[i].ID = 2;
			auto end = std::chrono::high_resolution_clock::now();
			deltaTime += std::chrono::duration<float, std::milli>(end - start).count();
		}
		deltaTime /= m_SamplesTTCGO;

		m_ResultsTTCGoAlt.push_back(deltaTime);
		stepSize *= 2;
	}
}
