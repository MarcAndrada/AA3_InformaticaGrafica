#include "InputManager.h"

#include <iostream>
InputManager::InputManager() 
{
    double x, y;
    glfwGetCursorPos(GLM.GetWindow(), &x, &y);
    lastMousePos = glm::vec2(x, y);
}

void InputManager::CheckInputs(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        keyWPressAction();
    }
    else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_RELEASE)
    {
        keyWReleaseAction();
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        keySPressAction();
    }
    else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_RELEASE)
    {
        keySReleaseAction();
    }
    
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        keyAPressAction();
    }
    else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_RELEASE)
    {
        keyAReleaseAction();
    }
    
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        keyDPressAction();
    }
    else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_RELEASE)
    {
        keyDReleaseAction();
    }

}

void InputManager::SetupKeyWInputPressed(std::function<void()> _action)
{
    keyWPressAction = _action;
}
void InputManager::SetupKeyWInputReleased(std::function<void()> _action)
{
    keyWReleaseAction = _action;
}

void InputManager::SetupKeySInputPressed(std::function<void()> _action)
{
    keySPressAction = _action;
}
void InputManager::SetupKeySInputReleased(std::function<void()> _action)
{
    keySReleaseAction = _action;
}

void InputManager::SetupKeyAInputPressed(std::function<void()> _action)
{
    keyAPressAction = _action;
}
void InputManager::SetupKeyAInputReleased(std::function<void()> _action)
{
    keyAReleaseAction = _action;
}

void InputManager::SetupKeyDInputPressed(std::function<void()> _action)
{
    keyDPressAction = _action;
}
void InputManager::SetupKeyDInputReleased(std::function<void()> _action)
{
    keyDReleaseAction = _action;
}

glm::vec2 InputManager::GetCursorDistanceTraveled(GLFWwindow* _window)
{

    double x, y;

    glfwGetCursorPos(_window, &x, &y);
    glm::vec2 newMousePos = glm::vec2(x, y);


    glm::vec2 mouseDistance = glm::vec2(newMousePos.x - lastMousePos.x, lastMousePos.y - newMousePos.y);

    lastMousePos = newMousePos;
    
    return mouseDistance;
}

