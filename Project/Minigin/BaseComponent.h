#pragma once

class GameObject;
namespace dae
{
	class BaseComponent
	{
	public:
		BaseComponent() = default;
		virtual ~BaseComponent() = default;

		BaseComponent(const BaseComponent& other) = delete;
		BaseComponent(BaseComponent&& other) = delete;
		BaseComponent& operator=(const BaseComponent& other) = delete;
		BaseComponent& operator=(BaseComponent&& other) = delete;

		virtual void Update();
		virtual void FixedUpdate();
		virtual void Render() const;

		void SetLinkedGameObject(std::shared_ptr<GameObject> linkedGameObject);

	protected:
		std::weak_ptr<GameObject> m_pLinkedGameObject;
	};
}

