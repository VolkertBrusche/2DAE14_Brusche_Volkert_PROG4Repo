#include "MiniginPCH.h"
#include "DisplayObserver.h"
#include "TextComponent.h"
#include "HealthComponent.h"
#include "PointsComponent.h"

void dae::DisplayObserver::Notify(const GameObject& gameObject, Event event)
{
	std::shared_ptr<TextComponent> textComp;
	std::shared_ptr<PointsComponent> pointComp;
	std::shared_ptr<HealthComponent> healthComp;

	switch (event)
	{
	case Event::PointsChanged:
		textComp = gameObject.GetComponent<TextComponent>();
		pointComp = gameObject.GetComponent<PointsComponent>();
		if (textComp != nullptr && pointComp != nullptr)
		{
			textComp->SetText("Points: " + std::to_string(pointComp->GetPoints()));
		}
		break;
	case Event::LivesChanged:
		textComp = gameObject.GetComponent<TextComponent>();
		healthComp = gameObject.GetComponent<HealthComponent>();
		if (textComp != nullptr && healthComp != nullptr)
		{
			textComp->SetText("Lives: " + std::to_string(healthComp->GetLives()));
		}
		break;
	}
}
