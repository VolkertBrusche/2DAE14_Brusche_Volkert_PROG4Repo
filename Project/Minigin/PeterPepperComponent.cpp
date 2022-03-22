#include "MiniginPCH.h"
#include "PeterPepperComponent.h"
#include "HealthComponent.h"
#include "PointsComponent.h"
#include "Achievements.h"

dae::PeterPepperComponent::PeterPepperComponent(std::shared_ptr<GameObject> gameObject)
	:BaseComponent{gameObject}
{
}

dae::PeterPepperComponent::~PeterPepperComponent()
{
}

void dae::PeterPepperComponent::Update(float)
{
}
