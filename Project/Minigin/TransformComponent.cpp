#include "MiniginPCH.h"
#include "TransformComponent.h"
#include "GameObject.h"

dae::TransformComponent::TransformComponent(std::shared_ptr<GameObject> gameObject)
	:BaseComponent{gameObject}
{
	//gameObject->AddComponent(shared_from_this()); //shared_from_this() doesn't work in constructor because
													//the shared_ptr of this hasn't been created yet
}

void dae::TransformComponent::SetPosition(const float x, const float y, const float z)
{
	m_Position.x = x;
	m_Position.y = y;
	m_Position.z = z;
}
