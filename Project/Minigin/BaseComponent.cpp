#include "MiniginPCH.h"
#include "BaseComponent.h"

void dae::BaseComponent::Update()
{
}

void dae::BaseComponent::FixedUpdate()
{
}

void dae::BaseComponent::Render() const
{
}

void dae::BaseComponent::SetLinkedGameObject(std::shared_ptr<GameObject> linkedGameObject)
{
	m_pLinkedGameObject = linkedGameObject;
}
