#pragma once
#include "BaseComponent.h"
namespace dae
{
    class GameObject;
    class FPSComponent final : public BaseComponent, public std::enable_shared_from_this<FPSComponent>
    {
    public:
        FPSComponent(std::shared_ptr<GameObject> gameObject);
        virtual ~FPSComponent();

        virtual void Update(float deltaTime) override;
        virtual void Render() const override;

        int GetFPS() const;
        
    private:
        int m_FPS{0};
    };
}

