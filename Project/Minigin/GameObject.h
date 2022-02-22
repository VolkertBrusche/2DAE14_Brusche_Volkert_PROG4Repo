#pragma once
namespace dae
{
	class Texture2D;
	class BaseComponent;

	// todo: this should become final.
	class GameObject final
	{
	public:
		void Update(float deltaTime);
		void FixedUpdate(float fixedTimeStamp);
		void Render() const;

		void AddComponent(std::shared_ptr<BaseComponent> component);
		void RemoveComponent(std::shared_ptr<BaseComponent> component);
		template<typename T>
		std::shared_ptr<T> GetComponent() const
		{
			for (auto component : m_pComponents)
			{
				std::shared_ptr<T> castedComponent = std::dynamic_pointer_cast<T>(component);

				if (castedComponent != nullptr)
				{
					return castedComponent;
				}
			}
			return nullptr;
		}

		void SetParent(std::weak_ptr<GameObject> parent);
		std::weak_ptr<GameObject> GetParent() const;

		size_t GetChildCount() const;
		std::shared_ptr<GameObject> GetChildAt(size_t idx);
		void RemoveChild(size_t idx);
		void AddChild(std::shared_ptr<GameObject> gameObject);
		
		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;
		std::vector<std::shared_ptr<GameObject>> m_pChildren;
		std::weak_ptr<GameObject> m_pParent;
	};
}
