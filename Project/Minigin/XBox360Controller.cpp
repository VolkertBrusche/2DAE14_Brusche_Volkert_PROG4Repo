#include "MiniginPCH.h"
#include "XBox360Controller.h"

//Xinput & pimpl includes
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include <iostream>
#pragma comment(lib, "xinput.lib")

using namespace dae;

class XBox360Controller::XBox360ControllerImpl
{
	XINPUT_STATE previousState{};
	XINPUT_STATE currentState{};

	WORD buttonsPressedThisFrame;
	WORD buttonsReleasedThisFrame;

	unsigned int _controllerIndex;

public:
	XBox360ControllerImpl(unsigned int controllerIndex);

	void Update();

	bool IsDownThisFrame(unsigned int button) const;
	bool IsUpThisFrame(unsigned int button) const;
	bool IsPressed(unsigned int button) const;
};

//XBOX360CONTROLLER Implementation
XBox360Controller::XBox360Controller(unsigned int controllerIndex)
{
	pImpl = new XBox360ControllerImpl(controllerIndex);
}

XBox360Controller::~XBox360Controller()
{
	delete pImpl;
}

void XBox360Controller::Update()
{
	pImpl->Update();
}

bool XBox360Controller::IsDown(ControllerButton button) const
{
	return pImpl->IsDownThisFrame(static_cast<int>(button));
}

bool XBox360Controller::IsUp(ControllerButton button) const
{
	return pImpl->IsUpThisFrame(static_cast<int>(button));
}

bool XBox360Controller::IsPressed(ControllerButton button) const
{
	return pImpl->IsPressed(static_cast<int>(button));
}


//XBOX360CONTROLLERIMPL Implementation
XBox360Controller::XBox360ControllerImpl::XBox360ControllerImpl(unsigned int controllerIndex)
{
	ZeroMemory(&previousState, sizeof(XINPUT_STATE));
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	_controllerIndex = controllerIndex;
}

void XBox360Controller::XBox360ControllerImpl::Update()
{
	CopyMemory(&previousState, &currentState, sizeof(XINPUT_STATE));
	ZeroMemory(&currentState, sizeof(XINPUT_STATE));
	XInputGetState(_controllerIndex, &currentState);

	auto buttonChanges = currentState.Gamepad.wButtons ^ previousState.Gamepad.wButtons;
	buttonsPressedThisFrame = buttonChanges & currentState.Gamepad.wButtons;
	buttonsReleasedThisFrame = buttonChanges & (~currentState.Gamepad.wButtons);
}

bool XBox360Controller::XBox360ControllerImpl::IsDownThisFrame(unsigned int button) const
{
	return buttonsPressedThisFrame & button;
}

bool XBox360Controller::XBox360ControllerImpl::IsUpThisFrame(unsigned int button) const
{
	return buttonsReleasedThisFrame & button;
}

bool XBox360Controller::XBox360ControllerImpl::IsPressed(unsigned int button) const
{
	return currentState.Gamepad.wButtons & button;
}