#include "MiniginPCH.h"
#include "Achievements.h"

void dae::Achievements::Notify(const GameObject&, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		if (!m_Achievements[Achievement::first_blood])
			Unlock(Achievement::first_blood);
		break;
	}
}

void dae::Achievements::Unlock(Achievement achievement)
{
	m_Achievements[achievement] = true;
	std::cout << "First blood has been achieved!\n";
}
