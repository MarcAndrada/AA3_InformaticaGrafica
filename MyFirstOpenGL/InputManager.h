#pragma once
#include "GLManager.h"
#include <GLFW/glfw3.h>
#include <glm.hpp>
#include <functional>

#define INPUT_MANAGER InputManager::Instance()

class InputManager
{
private:
	InputManager();

	InputManager(const InputManager&) = delete;
	InputManager& operator =(const InputManager&) = delete;

	std::function<void()> keyWPressAction;
	std::function<void()> keyWReleaseAction;
	std::function<void()> keySPressAction;
	std::function<void()> keySReleaseAction;
	std::function<void()> keyAPressAction;
	std::function<void()> keyAReleaseAction;
	std::function<void()> keyDPressAction;
	std::function<void()> keyDReleaseAction;

	std::function<void()> keyFPressAction;
	std::function<void()> keyFReleaseAction;

	glm::vec2 lastMousePos;

public:
	inline static InputManager& Instance()
	{
		static InputManager manager;
		return manager;
	}

	void CheckInputs(GLFWwindow* window);

	void SetupKeyWInputPressed(std::function<void()> _action);
	void SetupKeyWInputReleased(std::function<void()> _action);
	void SetupKeySInputPressed(std::function<void()> _action);
	void SetupKeySInputReleased(std::function<void()> _action);
	void SetupKeyAInputPressed(std::function<void()> _action);
	void SetupKeyAInputReleased(std::function<void()> _action);
	void SetupKeyDInputPressed(std::function<void()> _action);
	void SetupKeyDInputReleased(std::function<void()> _action);
	void SetupKeyFInputPressed(std::function<void()> _action);
	void SetupKeyFInputReleased(std::function<void()> _action);

	glm::vec2 GetCursorDistanceTraveled(GLFWwindow* _window);
};

