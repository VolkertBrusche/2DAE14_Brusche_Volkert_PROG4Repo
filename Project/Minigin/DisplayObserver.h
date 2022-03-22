#pragma once
#include "Observer.h"

namespace dae
{
	class DisplayObserver final: public Observer
	{
	public:
		void Notify(const GameObject& gameObject, Event event) override;
	};
}

