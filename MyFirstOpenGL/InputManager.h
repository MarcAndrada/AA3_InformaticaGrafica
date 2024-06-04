#pragma once
#include <GLFW/glfw3.h>
#include <functional>

#define INPUT_MANAGER InputManager::Instance()

class InputManager
{
private:
	InputManager() = default;

	InputManager(const InputManager&) = delete;
	InputManager& operator =(const InputManager&) = delete;

	std::function<void()> key1Action;
	std::function<void()> key2Action;
	std::function<void()> key3Action;
	std::function<void()> keySpaceAction;

public:
	inline static InputManager& Instance()
	{
		static InputManager manager;
		return manager;
	}

	void CheckInputs(GLFWwindow* window);

	void SetupKey1Input(std::function<void()> _action);
	void SetupKey2Input(std::function<void()> _action);
	void SetupKey3Input(std::function<void()> _action);
	void SetupKeySpaceInput(std::function<void()> _action);

};

