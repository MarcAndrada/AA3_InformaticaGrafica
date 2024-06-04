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
    void Render() override {}
private:
    enum CameraState {
        PROFILE_VIEW_1,
        PROFILE_VIEW_2,
        DOLLY_ZOOM,
        ORBIT
    };

    CameraState currentState = ORBIT;

    glm::vec3 target;
    glm::vec3 localVectorUp;

    float fFov;
    float fNear;
    float fFar;

    float movementSpeed;

    bool isOrbitating = true;


    void ProfileView1Action();
    void ProfileView2Action();
    void DollyZoomAction();
    void OrbitAction();

    void SetCameraPosition(glm::vec3 _position, glm::vec3 _target, float _fFov);

    void ApplyCameraState();

    void Orbit(float deltaTime);
};
