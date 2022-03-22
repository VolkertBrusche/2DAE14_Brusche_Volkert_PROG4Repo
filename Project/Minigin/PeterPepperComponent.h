#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
    class PeterPepperComponent final: public BaseComponent
    {
    public:
        PeterPepperComponent(std::shared_ptr<GameObject> gameObject);
        virtual ~PeterPepperComponent();

        virtual void Update(float deltaTime) override;
        virtual void Render() const override;

        void Die();
    private:
        std::unique_ptr<Subject> m_pActorDied = nullptr;
        int m_Lives{};
        int m_Points{};
    };
}

