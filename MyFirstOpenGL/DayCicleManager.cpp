#include "DayCicleManager.h"

void DayCicleManager::InitializeSunAndMoon(Primitive* _sun, Primitive* _moon)
{
	sun = _sun;
	moon = _moon;

	cycleDuration = 20.f;
    radius = 5.f;
    maxAngle = 6.25f;//Haciendo pruebas me ha dado que este es el valor que tiene cuando da la vuelta completa
    sunInitialAngle = 0.f;
    moonInitialAngle = maxAngle / 2; 
}

void DayCicleManager::DayCycleUpdate(float _deltaTime)
{
    timePassed += _deltaTime / cycleDuration;

    //Capar el tiempo para que no llegue al infinito y evitar que pete el programa
    if (timePassed >= maxAngle)
        timePassed -= maxAngle;


    //Calcular la orbita del sol
    Orbit(sun, sunInitialAngle, _deltaTime);
    //Calcular la orbita de la luna
    Orbit(moon, moonInitialAngle, _deltaTime);

    CheckDayOrNight();
    SendLightToShader();
}

void DayCicleManager::Orbit(Primitive* _target, float _initialAngle, float _deltaTime)
{
    float currentAngle = _initialAngle + 2 * PI * timePassed;

    glm::vec3 newPos = glm::vec3(
        cos(currentAngle) * radius, //X
        sin(currentAngle) * radius, //Y
        0 //Z
    );

    _target->transform.position = newPos;

}

void DayCicleManager::CheckDayOrNight()
{
    //Si el sol esta debajo del suelo es de noche
    isDay = sun->transform.position.y >= 0;
}

void DayCicleManager::SendLightToShader()
{

    GLuint program = PROGRAMS.GetCompiledPrograms()[0];

    glUseProgram(program);

    //Enviar color del sol
    glm::vec4 sunColor = sun->GetColor();
    glUniform3f(glGetUniformLocation(program, "sunColor"), sunColor.r, sunColor.g, sunColor.b);

    //Enviar color de la luna
    glm::vec4 moonColor = moon->GetColor();
    glUniform3f(glGetUniformLocation(program, "moonColor"), moonColor.r, moonColor.g, moonColor.b);

    //Enviar el tiempo
    float currentAngle = 2 * PI * timePassed;
    float angleSin = sin(currentAngle);
    // El seno nos da un valor de -1 a 1 
    // Lo dividiremos entre 2 para que nos de entre -0.5 y 0.5
    // Y luego le sumamos 0.5 para que nos de de 0 a 1
    float lerpTime = (angleSin / 2) + 0.5f;
    glUniform1f(glGetUniformLocation(program, "lerpTime"), lerpTime);

    std::cout << lerpTime << std::endl;
}