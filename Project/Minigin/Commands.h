#pragma once
#include <iostream>
#include "Scene.h"
#include "GameObject.h"
#include "HealthComponent.h"
#include "PointsComponent.h"

namespace dae
{
	class Command
	{
	public:
		virtual ~Command() = default;
		virtual void Execute() = 0;
		virtual void Undo() = 0;
	};

	class JumpCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Player Jumped!\n"; }
		void Undo() override { std::cout << "Undo Player Jump!\n"; }
	};

	class FireCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Player Fired!\n"; }
		void Undo() override { std::cout << "Undo Player Fire!\n"; }
	};

	class CrouchCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Player Crouched!\n"; }
		void Undo() override { std::cout << "Undo Player Crouch!\n"; }
	};

	class SwapGunCommand final : public Command
	{
	public:
		void Execute() override { std::cout << "Player Swapped Gun!\n"; }
		void Undo() override { std::cout << "Undo Player Swap Gun!\n"; }
	};

	class KillPlayer final : public Command
	{
	public:
		KillPlayer(std::shared_ptr<GameObject> gameObject) : Command{}, m_pGameObject{gameObject} {};

		void Execute() override
		{
			m_pGameObject.lock()->GetChildAt(0)->GetComponent<HealthComponent>()->Suicide();
		}
		void Undo() override { std::cout << "Undo Kill Player!\n"; }

	private:
		std::weak_ptr<GameObject> m_pGameObject;
	};

	class AddPointsCommand final : public Command
	{
	public:
		AddPointsCommand(std::shared_ptr<GameObject> gameObject) : Command{}, m_pGameObject{ gameObject } {};

		void Execute() override
		{
			m_pGameObject.lock()->GetChildAt(1)->GetComponent<PointsComponent>()->AddPoints();
		}
		void Undo() override { std::cout << "Undo AddPoints\n"; }

	private:
		std::weak_ptr<GameObject> m_pGameObject;
	};
}

