#pragma once
#include "Singleton.h"
#include <memory>
#include <map>
#include "Commands.h"
#include "XBox360Controller.h"

namespace dae
{
	class InputManager final : public Singleton<InputManager>
	{
		using ControllerKey = std::pair<unsigned, XBox360Controller::ControllerButton>;
		using ControllerCommandMap = std::map<ControllerKey, std::unique_ptr<Command>>;

	public:
		InputManager();
		~InputManager();

		bool ProcessInput();

		void SetButtonCommand(unsigned int controllerIndex, XBox360Controller::ControllerButton button, Command* command);

		bool m_IsLooping{ true };

	private:
		XBox360Controller* m_pXboxController;

		ControllerCommandMap m_ConsoleCommands{};
	};

}
