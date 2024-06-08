#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

#include "GLManager.h"
#include "TimeManager.h"
#include "InputManager.h"
#include "Entity.h"

class Camera: public Entity
{
public:
    Camera();

  

    void SetupCameraInputs();
    void Update() override;
    void Render() override;

    inline glm::vec3 GetForward() { return forward; }
private:

    glm::vec3 target;

    glm::vec3 up;
    glm::vec3 forward;
    glm::vec3 right;


    float fFov, fNear, fFar;
    float movementSpeed, mouseSensitivity, yaw, pitch, maxPitchAngle;

    bool movingForward;
    bool movingBackwards;
    bool movingRight;
    bool movingLeft;


    void RotateBehaviour();
    void MoveBehaviour();
    

    glm::vec3 CalculateMovementSpeed();
};
