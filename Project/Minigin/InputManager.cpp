#include "MiniginPCH.h"
#include "InputManager.h"
#include <backends\imgui_impl_sdl.h>

dae::InputManager::InputManager()
{
	m_pXboxController = new XBox360Controller(0);
}

dae::InputManager::~InputManager()
{
	delete m_pXboxController;
}

bool dae::InputManager::ProcessInput()
{
	// todo: read the input;
	m_pXboxController->Update();

	for (ControllerCommandMap::iterator controllerIt = m_ConsoleCommands.begin(); controllerIt != m_ConsoleCommands.end(); ++controllerIt)
	{
		if (m_pXboxController->IsDown(controllerIt->first.second))
			controllerIt->second->Execute();

		//Quick and dirty solution for ending the program
		if (m_pXboxController->IsPressed(XBox360Controller::ControllerButton::Back))
			return false;
	}

	return true;
}

void dae::InputManager::SetButtonCommand(unsigned int controllerIndex, XBox360Controller::ControllerButton button, Command* command)
{
	m_ConsoleCommands[ControllerKey(controllerIndex, button)] = std::unique_ptr<Command>(command);
}

