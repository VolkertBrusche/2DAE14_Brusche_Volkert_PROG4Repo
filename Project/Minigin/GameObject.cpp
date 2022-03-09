#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(float deltaTime)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Update(deltaTime);
	}

	for (auto pChildren : m_pChildren)
	{
		pChildren->Update(deltaTime);
	}
}

void dae::GameObject::FixedUpdate(float fixedTimeStamp)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->FixedUpdate(fixedTimeStamp);
	}

	for (auto pChildren : m_pChildren)
	{
		pChildren->FixedUpdate(fixedTimeStamp);
	}
}

void dae::GameObject::Render() const
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->Render();
	}
	
	for (auto pChildren : m_pChildren)
	{
		pChildren->Render();
	}
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	if(component != nullptr)
		m_pComponents.push_back(component);
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{
	if(component != nullptr)
		m_pComponents.erase(std::find(m_pComponents.begin(), m_pComponents.end(), component));
}

void dae::GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
	if (parent != nullptr)
	{
		if (std::find(m_pChildren.begin(), m_pChildren.end(), parent) == m_pChildren.end()) //Checks if the parent is in the children of this gameobject
																							//Avoids parents linking parents
		{
			if (m_pParent.lock() != nullptr) //Checks if current parent is occupied
				m_pParent.lock()->RemoveChild(shared_from_this()); //Removes this gameobject from the children from that parent if so

			m_pParent = parent; //Sets the new parent
			parent->AddChild(shared_from_this()); //Adds the gameobject in the children of the parent
		}
	}
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_pParent.lock();
}

size_t dae::GameObject::GetChildCount() const
{
	return m_pChildren.size();
}

std::shared_ptr<dae::GameObject> dae::GameObject::GetChildAt(size_t idx)
{
	if (idx < m_pChildren.size())
	{
		return m_pChildren[idx];
	}
	return std::shared_ptr<GameObject>(nullptr);
}

void dae::GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	if (child != nullptr)
	{
		m_pChildren.erase(std::find(m_pChildren.begin(), m_pChildren.end(), child));
	}
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> gameObject)
{
	if (gameObject != nullptr && std::find(m_pChildren.begin(), m_pChildren.end(), gameObject) == m_pChildren.end())
	{
		m_pChildren.push_back(gameObject);
	}
}
