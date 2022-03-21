#pragma once
#include "Singleton.h"
#include <memory>
#include <map>
#include <array>
#include "Commands.h"
#include "XBox360Controller.h"

//Xinput Includes
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")

namespace dae
{
	enum class CommandState
	{
		Pressed,
		Down,
		Up
	};

	class InputManager final : public Singleton<InputManager>
	{
		using CommandKey = std::pair<std::unique_ptr<Command>, CommandState>;
		using ControllerKey = std::pair<unsigned, XBox360Controller::ControllerButton>;
		using ControllerCommandMap = std::map<ControllerKey, CommandKey>;

	public:
		InputManager();
		~InputManager();

		bool ProcessInput();

		void SetButtonCommand(unsigned int controllerIndex, XBox360Controller::ControllerButton button, Command* command, CommandState state); //Add command state
		void RemoveButtonCommand(unsigned int controllerIndex, XBox360Controller::ControllerButton button);

	private:

		std::array<XBox360Controller*, XUSER_MAX_COUNT> m_pXboxController;

		ControllerCommandMap m_ConsoleCommands{};
	};

}
