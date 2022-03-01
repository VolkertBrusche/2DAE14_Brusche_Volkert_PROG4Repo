#pragma once
#include "BaseComponent.h"
#include "SDL.h"

namespace dae
{
    class GameObject;
    class ImGuiComponent final: public BaseComponent, public std::enable_shared_from_this<ImGuiComponent>
    {
    public:
        ImGuiComponent(std::shared_ptr<GameObject> gameObject, SDL_Window* pWindow);
        virtual ~ImGuiComponent();

        virtual void Update(float deltaTime) override;
        virtual void Render() const override;

    private:
        //IMGUI Variables & Functions ====================================================
        void TTCIntBuffer();
        void TTCGoBuffer();
        void TTCGoAltBuffer();

        int m_SamplesTTCInt{ 100 };
        int m_SamplesTTCGO{ 100 };
        int m_MaxStepSize{ 1024 };
        int m_BaseStepSize{ 1 };

        std::vector<float> m_ResultsTTCInt{};
        std::vector<float> m_ResultsTTCGo{};
        std::vector<float> m_ResultsTTCGoAlt{};
        std::vector<float> m_StepSizes = { 1.f,2.f,4.f,8.f,16.f,32.f,64.f,128.f,256.f,512.f,1024.f };

        bool isTTCintButtonPressed{ false };
        bool isTTCGoButtonPressed{ false };
        bool isTTCGoAltButtonPressed{ false };

        SDL_Window* m_pWindow = nullptr;
        //================================================================================
    };
}

