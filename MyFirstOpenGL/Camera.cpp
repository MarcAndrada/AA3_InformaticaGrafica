#include "Camera.h"

Camera::Camera() 
{
    transform.position = glm::vec3(0.f, 5.f, 10.f);
    target = glm::vec3(0.f, 0.f, 0.f);
    localVectorUp = glm::vec3(0.f, 1.f, 0.f);
    fFov = 45.f;
    fNear = 0.1f;
    fFar = 100.f;
    movementSpeed = 5.f;
    isOrbitating = true;
    currentState = ORBIT;
}

void Camera::HandleKeyboardInput(GLFWwindow* window) 
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        SetCameraPosition(glm::vec3(0.5f, 2.f, 0.25f), glm::vec3(1.f, 2.f, 0.25f), 45);

        currentState = PROFILE_VIEW_1;
    }
    else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
        SetCameraPosition(glm::vec3(1.f, 2.f, 0.f), glm::vec3(-1.f, 2.f, 0.f), 45);

        currentState = PROFILE_VIEW_2;
    }
    else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        SetCameraPosition(glm::vec3(0.f, 2.f, 15.f), glm::vec3(0.f, 2.f, 0.f), 45);

        currentState = DOLLY_ZOOM;
    }
    else if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        SetCameraPosition(glm::vec3(0.f, 5.f, 10.f), glm::vec3(0.f), 45);

        currentState = ORBIT;
    }
}

void Camera::SetCameraPosition(glm::vec3 _position, glm::vec3 _target, float _fFov)
{
    transform.position = _position;
    target = _target;
    fFov = _fFov;
}

void Camera::ApplyCameraState()
{
    float deltaTime = TIME_MANAGER.GetDeltaTime();

    switch (currentState) {
    case PROFILE_VIEW_1:
    case PROFILE_VIEW_2:
        break;
    case DOLLY_ZOOM:
        fFov += movementSpeed * deltaTime;
        transform.position.z -= movementSpeed * deltaTime;
        
        if (fFov >= 60)
        {
            SetCameraPosition(glm::vec3(0.f, 5.f, 10.f), glm::vec3(0.f), 45);

            currentState = ORBIT;
        }

        break;
    case ORBIT:
    default:
        Orbit(deltaTime);
        break;
    }
}

void Camera::Orbit(float deltaTime)
{
    float angle = 0.5f * deltaTime;
    glm::vec3 relativePos = transform.position - target;

    float newX = cos(angle) * relativePos.x - sin(angle) * relativePos.z;
    float newZ = sin(angle) * relativePos.x + cos(angle) * relativePos.z;

    transform.position.x = target.x + newX;
    transform.position.z = target.z + newZ;
}

void Camera::Update()
{
    TIME_MANAGER.Update();
    HandleKeyboardInput(GLM.GetWindow());
    ApplyCameraState();

    glm::mat4 viewMatrix = glm::lookAt(transform.position /* Eye */, target /* Target */, localVectorUp /* Up */);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fFov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, fNear, fFar);

    for (GLuint program : PROGRAMS.GetCompiledPrograms())
    {
        glUseProgram(program);
        glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }    
}
