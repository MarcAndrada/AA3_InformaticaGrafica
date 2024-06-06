#include "Camera.h"

Camera::Camera() 
{
    transform.position = glm::vec3(0.f, 5.f, -10.f);
    target = glm::vec3(0.f, 0.f, 0.f);
    right = glm::vec3(-1.f, 0.f, 0.f);
    up = glm::vec3(0.f, 1.f, 0.f);
    forward = glm::vec3(0.f, 0.f, 1.f);

    fFov = 45.f;
    fNear = 0.1f;
    fFar = 100.f;
    movementSpeed = 5.f;
    mouseSensitivity = 0.1f;
    yaw = 0.f;
    pitch = 0.f;
    maxPitchAngle = 89.f;

}

void Camera::SetupCameraInputs()
{
    //Asignamos la funcion que hara cada input usando una lambda

    INPUT_MANAGER.SetupKeyWInputPressed([this]() {
        movingForward = true;
        });
    INPUT_MANAGER.SetupKeyWInputReleased([this]() {
        movingForward = false;
        });


    INPUT_MANAGER.SetupKeySInputPressed([this]() {
        movingBackwards = true;
        });
    INPUT_MANAGER.SetupKeySInputReleased([this]() {
        movingBackwards = false;
        });

    INPUT_MANAGER.SetupKeyAInputPressed([this]() {
        movingLeft = true;
        });
    INPUT_MANAGER.SetupKeyAInputReleased([this]() {
        movingLeft = false;
        });

    INPUT_MANAGER.SetupKeyDInputPressed([this]() {
        movingRight = true;
        });
    INPUT_MANAGER.SetupKeyDInputReleased([this]() {
        movingRight = false;
        });

}


void Camera::RotateBehaviour()
{
    glm::vec2 mouseDistanceTraveled = INPUT_MANAGER.GetCursorDistanceTraveled(GLM.GetWindow());

    glm::vec2 mouseOffset = mouseDistanceTraveled * mouseSensitivity;

    yaw += mouseOffset.x;
    pitch += mouseOffset.y;
    if (pitch > maxPitchAngle)
        pitch = maxPitchAngle;
    else if (pitch < -maxPitchAngle)
        pitch = -maxPitchAngle;

    glm::vec3 tmpForward;
    tmpForward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    tmpForward.y = sin(glm::radians(pitch));
    tmpForward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    forward = glm::normalize(tmpForward);
    
    glm::vec3 tmpRight;
    float rightYaw = yaw + 90;
    tmpRight.x = cos(glm::radians(rightYaw)) * cos(glm::radians(0.f));
    tmpRight.y = sin(glm::radians(0.f));
    tmpRight.z = sin(glm::radians(rightYaw)) * cos(glm::radians(0.f));
    
    right = glm::normalize(tmpRight);
}

void Camera::MoveBehaviour()
{
    float deltaTime = TIME_MANAGER.GetDeltaTime();

    //Asignarle la posicion segun los inputs apretados
    transform.position += (CalculateMovementSpeed() * deltaTime);
        
}

glm::vec3 Camera::CalculateMovementSpeed()
{
    glm::vec3 movementDirection = glm::vec3(0.f);

    if (movingForward)
        movementDirection += forward * movementSpeed;
    if (movingBackwards)
        movementDirection -= forward * movementSpeed;
    if (movingRight)
        movementDirection += right * movementSpeed;
    if (movingLeft)
        movementDirection -= right * movementSpeed;

 
    return movementDirection;
}


void Camera::Update()
{
    RotateBehaviour();
    MoveBehaviour();

    glm::mat4 viewMatrix = glm::lookAt(transform.position /* Eye */, transform.position + forward /* Target */, up /* Up */);

    glm::mat4 projectionMatrix = glm::perspective(glm::radians(fFov), (float)WINDOW_WIDTH / (float)WINDOW_HEIGHT, fNear, fFar);

    for (GLuint program : PROGRAMS.GetCompiledPrograms())
    {
        glUseProgram(program);
        glUniformMatrix4fv(glGetUniformLocation(program, "viewMatrix"), 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(glGetUniformLocation(program, "projectionMatrix"), 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    }    
}
