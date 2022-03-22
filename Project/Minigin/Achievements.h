#pragma once
#include "Observer.h"
#include <map>
#include <memory>

namespace dae
{
	enum class Achievement
	{
		first_blood
	};

	class Achievements final : public Observer
	{
	public:
		void Notify(const GameObject& gameObject, Event event) override;

	private:
		void Unlock(Achievement achievement);

		using AchievementMap = std::map<Achievement, bool>;
		AchievementMap m_Achievements{};
	};
}

