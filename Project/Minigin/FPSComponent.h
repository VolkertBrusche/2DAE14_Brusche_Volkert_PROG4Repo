#pragma once
#include "BaseComponent.h"
namespace dae
{
    class FPSComponent final:
        public BaseComponent
    {
    public:
        FPSComponent() = default;
        virtual ~FPSComponent();

        virtual void Update(float deltaTime) override;
        virtual void Render() const override;

        int GetFPS() const;
        
    private:
        int m_FPS{0};
    };
}

