#pragma once
#include "BaseComponent.h"
#include "Subject.h"

namespace dae
{
	class HealthComponent final: public BaseComponent, public Subject
	{
	public:
		HealthComponent(std::shared_ptr<GameObject> gameObject, int maxLives);
		virtual ~HealthComponent() = default;

		HealthComponent(const HealthComponent& other) = delete;
		HealthComponent(HealthComponent&& other) = delete;
		HealthComponent& operator=(const HealthComponent& other) = delete;
		HealthComponent& operator=(HealthComponent&& other) = delete;

		void Update(float deltaTime) override;

		void Suicide() { m_Lives = 0; };

		int GetLives() const;

	private:
		int m_Lives{};
	};
}

