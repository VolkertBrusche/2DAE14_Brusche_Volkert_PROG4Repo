#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent(std::shared_ptr<GameObject> gameObject);
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update(float deltaTime) = 0;
		virtual void FixedUpdate(float) {};
		virtual void Render() const {};

	protected:
		std::weak_ptr<GameObject> m_pLinkedGameObject;
	};
}

