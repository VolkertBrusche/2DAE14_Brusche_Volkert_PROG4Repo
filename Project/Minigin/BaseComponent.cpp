#include "MiniginPCH.h"
#include "BaseComponent.h"

dae::BaseComponent::BaseComponent(std::shared_ptr<GameObject> gameObject)
	:m_pLinkedGameObject{gameObject}
{
}
