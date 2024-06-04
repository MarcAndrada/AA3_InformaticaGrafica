#include "InputManager.h"

#include <iostream>
void InputManager::CheckInputs(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        key1Action();
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        key2Action();
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        key3Action();
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        keySpaceAction();
    }
}

void InputManager::SetupKey1Input(std::function<void()> _action)
{
    key1Action = _action;
}

void InputManager::SetupKey2Input(std::function<void()> _action)
{
    key2Action = _action;
}

void InputManager::SetupKey3Input(std::function<void()> _action)
{
    key3Action = _action;
}

void InputManager::SetupKeySpaceInput(std::function<void()> _action)
{
    keySpaceAction = _action;
}

