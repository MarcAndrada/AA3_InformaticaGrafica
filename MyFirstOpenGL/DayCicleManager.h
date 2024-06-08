#pragma once
#include <iostream>
#include "ProgramManager.h"
#include "Primitive.h"

#define DAY_MANAGER DayCicleManager::Instance()
#define PI 3.1415
class DayCicleManager
{
public:
	inline static DayCicleManager& Instance()
	{
		static DayCicleManager manager;
		return manager;
	}

	void InitializeSunAndMoon(Primitive* _sun, Primitive* _moon);
	void DayCycleUpdate(float _deltaTime);
	
	inline glm::vec3 GetRisedSatelite() { return isDay ? sun->transform.position : moon->transform.position; }

private:
	DayCicleManager() = default;
	DayCicleManager(const DayCicleManager&) = delete;
	DayCicleManager& operator =(const DayCicleManager&) = delete;

	float timePassed;
	float cycleDuration;
	float radius;
	float maxAngle;
	float sunInitialAngle;
	float moonInitialAngle;

	bool isDay;
	

	Primitive* sun;
	Primitive* moon;
	
	void Orbit(Primitive* _target, float _initialAngle, float _deltaTime);
	void CheckDayOrNight();
	void SendLightToShader();

	inline bool GetIsDay() { return isDay; }

};

