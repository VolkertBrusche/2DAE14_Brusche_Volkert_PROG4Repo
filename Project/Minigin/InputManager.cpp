#include "MiniginPCH.h"
#include "InputManager.h"
#include <backends\imgui_impl_sdl.h>

dae::InputManager::InputManager()
{
	m_pXboxController[0] = new XBox360Controller(0);
}

dae::InputManager::~InputManager()
{
	for (XBox360Controller* pController : m_pXboxController)
	{
		delete pController;
	}
}

bool dae::InputManager::ProcessInput()
{
	// todo: read the input;

	for (size_t controllerIdx{}; controllerIdx < XUSER_MAX_COUNT; ++controllerIdx)
	{
		if (m_pXboxController[controllerIdx] == nullptr) //If there was not a controller initialized on that idx, continue
			continue;

		m_pXboxController[controllerIdx]->Update();
		for (ControllerCommandMap::iterator controllerIt = m_ConsoleCommands.begin(); controllerIt != m_ConsoleCommands.end(); ++controllerIt)
		{
			if (controllerIt->first.first != controllerIdx) //Checks if the current command isn't meant for the current controllerIdx
				continue;

			if (m_pXboxController[controllerIdx]->IsPressed(controllerIt->first.second) && controllerIt->second.second == CommandState::Pressed ||
				m_pXboxController[controllerIdx]->IsDown(controllerIt->first.second) && controllerIt->second.second == CommandState::Down ||
				m_pXboxController[controllerIdx]->IsUp(controllerIt->first.second) && controllerIt->second.second == CommandState::Up)
				if (controllerIt->second.first)
					controllerIt->second.first->Execute();

			//Quick and dirty solution for ending the program
			if (m_pXboxController[controllerIdx]->IsPressed(XBox360Controller::ControllerButton::Back))
				return false;
		}

	}
	return true;
}

void dae::InputManager::SetButtonCommand(unsigned int controllerIndex, XBox360Controller::ControllerButton button, Command* command, CommandState state)
{
	m_ConsoleCommands[ControllerKey(controllerIndex, button)] = std::pair(std::unique_ptr<Command>(command), state);
}

void dae::InputManager::RemoveButtonCommand(unsigned int controllerIndex, XBox360Controller::ControllerButton button)
{
	m_ConsoleCommands[ControllerKey(controllerIndex, button)].first = nullptr;
	m_ConsoleCommands[ControllerKey(controllerIndex, button)].second = CommandState::Pressed;
}

