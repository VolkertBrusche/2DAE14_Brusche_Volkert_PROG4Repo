#include "MiniginPCH.h"
#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"

dae::FPSComponent::~FPSComponent()
{
}

void dae::FPSComponent::Update(float deltaTime)
{
	m_FPS = static_cast<int>(1 / deltaTime);
	m_pLinkedGameObject.lock().get()->GetComponent<TextComponent>()->SetText(std::to_string(m_FPS) + " FPS");
}

void dae::FPSComponent::Render() const
{
}

int dae::FPSComponent::GetFPS() const
{
	return m_FPS;
}
