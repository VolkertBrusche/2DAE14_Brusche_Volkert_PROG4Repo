#pragma once
#include "BaseComponent.h"
#include "Subject.h"
namespace dae
{
	class PointsComponent final: public BaseComponent, public Subject
	{
	public:
		PointsComponent(std::shared_ptr<GameObject> gameObject);
		virtual ~PointsComponent() = default;

		PointsComponent(const PointsComponent& other) = delete;
		PointsComponent(PointsComponent&& other) = delete;
		PointsComponent& operator=(const PointsComponent& other) = delete;
		PointsComponent& operator=(PointsComponent&& other) = delete;

		void Update(float elapsedSec) override;

		void AddPoints();
		int GetPoints() const;

	private:
		int m_Points{};
	};
}

