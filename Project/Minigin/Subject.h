#pragma once
#include "GameObject.h"
#include "Observer.h"
#include <vector>

namespace dae
{
	class Observer;
	class Subject
	{
	public:
		void AddObserver(Observer* observer);
		void RemoveObserver(Observer* observer);

	protected:
		void Notify(const GameObject& actor, Event event);

	private:
		std::vector<Observer*> m_pObservers;
	};
}

