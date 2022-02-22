#include "MiniginPCH.h"
#include "BaseComponent.h"

void dae::BaseComponent::SetLinkedGameObject(std::shared_ptr<GameObject> linkedGameObject)
{
	m_pLinkedGameObject = linkedGameObject;
}
