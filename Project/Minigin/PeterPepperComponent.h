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

        PeterPepperComponent(const PeterPepperComponent& other) = delete;
        PeterPepperComponent(PeterPepperComponent&& other) = delete;
        PeterPepperComponent& operator=(const PeterPepperComponent& other) = delete;
        PeterPepperComponent& operator=(PeterPepperComponent&& other) = delete;

        void Update(float elapsedSec) override;
    private:
    };
}

