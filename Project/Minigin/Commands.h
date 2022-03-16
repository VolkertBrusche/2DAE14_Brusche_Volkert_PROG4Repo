#pragma once
#include <iostream>

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
}

