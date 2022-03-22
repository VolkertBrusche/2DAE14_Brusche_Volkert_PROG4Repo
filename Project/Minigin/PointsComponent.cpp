#include "MiniginPCH.h"
#include "PointsComponent.h"

dae::PointsComponent::PointsComponent(std::shared_ptr<GameObject> gameObject)
	:BaseComponent{gameObject}
	,Subject{}
{
}

void dae::PointsComponent::Update(float)
{
}

void dae::PointsComponent::AddPoints()
{
	m_Points += 10;
	Notify(*m_pLinkedGameObject.lock().get(), Event::PointsChanged);
}

int dae::PointsComponent::GetPoints() const
{
	return m_Points;
}
