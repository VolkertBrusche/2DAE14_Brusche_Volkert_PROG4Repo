#include "MiniginPCH.h"
#include "HealthComponent.h"

dae::HealthComponent::HealthComponent(std::shared_ptr<GameObject> gameObject, int maxLives)
	:BaseComponent{gameObject}
	,Subject{}
	,m_Lives{maxLives}
{
}

void dae::HealthComponent::Update(float)
{
	if (m_Lives == 0)
	{
		Notify(*m_pLinkedGameObject.lock().get(), Event::ActorDied);
		Notify(*m_pLinkedGameObject.lock().get(), Event::LivesChanged);
	}
}

int dae::HealthComponent::GetLives() const
{
	return m_Lives;
}
