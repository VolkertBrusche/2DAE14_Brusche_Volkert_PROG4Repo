#pragma once
#include "GameObject.h"

namespace dae
{
	enum class Event
	{
		ActorDied,
		LivesChanged,
		PointsChanged
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject& gameObject, Event event) = 0;
	};
}

