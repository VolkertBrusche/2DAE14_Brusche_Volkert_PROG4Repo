#pragma once

namespace dae
{
	class GameObject;
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update() = 0;
		virtual void FixedUpdate() {};
		virtual void Render() const {};

		void SetLinkedGameObject(std::shared_ptr<GameObject> linkedGameObject);

	protected:
		std::weak_ptr<GameObject> m_pLinkedGameObject;
	};
}

