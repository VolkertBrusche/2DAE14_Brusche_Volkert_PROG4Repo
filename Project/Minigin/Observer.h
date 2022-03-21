#pragma once
#include "GameObject.h"

namespace dae
{
	enum class Event
	{
		ActorDied
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void Notify(const GameObject& actor, Event event) = 0;
	};
}

