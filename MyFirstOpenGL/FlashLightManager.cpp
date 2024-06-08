#include "FlashLightManager.h"

void FlashLightManager::InitializeFlashLight(Camera* _camera)
{
	flashLightOn = false;
	camera = _camera;
	innerAngle = 5.f;
	outerAngle = 15.f;

	INPUT_MANAGER.SetupKeyFInputPressed([this]() {
		flashLightOn = true;
		});
	INPUT_MANAGER.SetupKeyFInputReleased([this]() {
		flashLightOn = false;
		});

}

void FlashLightManager::Update()
{
	GLuint program = PROGRAMS.GetCompiledPrograms()[0];

	glUseProgram(program);
	//Le pasamos si la linterna esta encendido o no
	glUniform1i(glGetUniformLocation(program, "flashlightOn"), flashLightOn);
	//Le pasamos las variables de la camara
	glUniform3f(glGetUniformLocation(program, "cameraPosition"), camera->transform.position.x, camera->transform.position.y, camera->transform.position.z);
	glUniform3f(glGetUniformLocation(program, "cameraForward"), camera->GetForward().x, camera->GetForward().y, camera->GetForward().z);

	glUniform1f(glGetUniformLocation(program, "innerAngle"), innerAngle);
	glUniform1f(glGetUniformLocation(program, "outerAngle"), outerAngle);

}


