#include "MiniginPCH.h"
#include "GameObject.h"
#include "Renderer.h"
#include "BaseComponent.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update()
{
	for (std::shared_ptr<BaseComponent> pComponent : m_pComponents)
	{
		pComponent->Update();
	}
}

void dae::GameObject::FixedUpdate()
{
	for (std::shared_ptr<BaseComponent> pComponent : m_pComponents)
	{
		pComponent->FixedUpdate();
	}
}

void dae::GameObject::Render() const
{
	for (std::shared_ptr<BaseComponent> pComponent : m_pComponents)
	{
		pComponent->Render();
	}
}

void dae::GameObject::AddComponent(std::shared_ptr<BaseComponent> component)
{
	m_pComponents.push_back(component);
}

void dae::GameObject::RemoveComponent(std::shared_ptr<BaseComponent> component)
{
	m_pComponents.erase(std::find(m_pComponents.begin(), m_pComponents.end(), component));
}

template<typename T>
std::shared_ptr<T> dae::GameObject::GetComponent() const
{
	for (std::shared_ptr<T> component : m_pComponents)
	{
		std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);

		if (castedComponent != nullptr)
		{
			return castedComponent;
		}
	}
}

void dae::GameObject::SetParent(std::weak_ptr<GameObject> parent)
{
	m_pParent = parent;
}

std::weak_ptr<dae::GameObject> dae::GameObject::GetParent() const
{
	return m_pParent;
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
	return std::shared_ptr<GameObject>();
}

void dae::GameObject::RemoveChild(size_t idx)
{
	if (idx < m_pChildren.size())
	{
		m_pChildren.erase(std::find(m_pChildren.begin(), m_pChildren.end(), m_pChildren.at(idx)));
	}
}

void dae::GameObject::AddChild(std::shared_ptr<GameObject> gameObject)
{
	if (gameObject != nullptr)
	{
		m_pChildren.push_back(gameObject);
	}
}
