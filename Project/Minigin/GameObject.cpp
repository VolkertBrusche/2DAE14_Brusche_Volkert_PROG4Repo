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
}

void dae::GameObject::FixedUpdate(float fixedTimeStamp)
{
	for (auto pComponent : m_pComponents)
	{
		pComponent->FixedUpdate(fixedTimeStamp);
	}
}

void dae::GameObject::Render() const
{
	for (auto pComponent : m_pComponents)
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
