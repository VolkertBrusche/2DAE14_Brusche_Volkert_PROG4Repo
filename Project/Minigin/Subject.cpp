#include "MiniginPCH.h"
#include "Subject.h"
#include <algorithm>

void dae::Subject::AddObserver(Observer* observer)
{
	m_pObservers.push_back(observer);
}

void dae::Subject::RemoveObserver(Observer* observer)
{
	m_pObservers.erase(std::find(m_pObservers.begin(), m_pObservers.end(), observer));
}

void dae::Subject::Notify(const GameObject& actor, Event event)
{
	for (Observer* observer : m_pObservers)
	{
		observer->Notify(actor, event);
	}
}
