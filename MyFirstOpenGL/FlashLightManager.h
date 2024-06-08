#pragma once
#include "Camera.h"
#include "InputManager.h"
#include "ProgramManager.h"
#define FLASHLIGHT FlashLightManager::Instance()

class FlashLightManager
{
public:
	inline static FlashLightManager& Instance()
	{
		static FlashLightManager manager;
		return manager;
	}

	void InitializeFlashLight(Camera* _camera);
	void Update();
private:
	FlashLightManager() = default;
	FlashLightManager(const FlashLightManager&) = delete;
	FlashLightManager& operator =(const FlashLightManager&) = delete;

	bool flashLightOn;

	Camera* camera;
	float innerAngle;
	float outerAngle;


};

