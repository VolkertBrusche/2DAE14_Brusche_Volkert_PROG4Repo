#include "MiniginPCH.h"
#include "TextureComponent.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "GameObject.h"
#include "TransformComponent.h"

dae::TextureComponent::TextureComponent(std::shared_ptr<GameObject> gameObject)
	:BaseComponent{gameObject}
{
	gameObject->AddComponent(shared_from_this());
}

dae::TextureComponent::~TextureComponent()
{
	m_pTexture = nullptr;
}

void dae::TextureComponent::Render() const
{
	const auto& pos = m_pLinkedGameObject.lock().get()->GetComponent<TransformComponent>()->GetPosition();
	Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
}

void dae::TextureComponent::SetTexture(const std::string& filename)
{
	m_pTexture = ResourceManager::GetInstance().LoadTexture(filename);
}
