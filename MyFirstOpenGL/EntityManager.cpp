#include "EntityManager.h"

void EntityManager::Initialize()
{
	//Inicializamos las entidades del sol y la luna
	InitializeSunAndMoon();

	//Inicializamos puntos de spawn de las entidades
	InitializeSpawnPoints();

	//Inicializamos las entidades
	InitializeEntities();

	//Suelo
	entities.push_back(new Primitive(
		PROGRAMS.GetCompiledPrograms()[1], //Programa
		glm::vec3(0.f, -1.f, 0.f), //Posicion
		glm::vec3(0.f, 1.f, 0.f), //Rotacion
		glm::vec3(10.f, 1.f, 10.f), //Escala
		glm::vec4(0.35f, 0.2f, 0.f,1.f)) //Color
	); 

	//Camara
	entities.push_back(new Camera());
}

void EntityManager::EntitiesUpdate()
{
	//Hacemos el update y render de cada entidad
	for (Entity* item : entities)
	{
		item->Update();
		item->Render();
	}

}

void EntityManager::InitializeSunAndMoon()
{
	// El sol y la luna son primitivas ya que no queremos que se vean afectados por la iluminacion
	// Utilizan el Programa 1 porque es el que utilizan las primitivas

	//Creamos el sol
	Primitive* sun = new Primitive(
		PROGRAMS.GetCompiledPrograms()[1], //Programa
		glm::vec3(0.f, 0.f, 0.f), //Posicion
		glm::vec3(0.f, 1.f, 0.f), //Rotacion
		glm::vec3(0.3f, 0.3f, 0.3f), //Escala
		glm::vec4(1.f, 0.98f, 0.17f, 3.f)//Color
	); 
	entities.push_back(sun);

	//Creamos la luna
	Primitive* moon = new Primitive(
		PROGRAMS.GetCompiledPrograms()[1], //Programa
		glm::vec3(0.f, 0.f, 0.f), //Posicion
		glm::vec3(0.f, 1.f, 0.f), //Rotacion
		glm::vec3(0.3f, 0.3f, 0.3f), //Escala
		glm::vec4(0.66f, 0.74f, 1.f, 3.f) //Color
	);
	entities.push_back(moon);

	//Le pasamos al day manager el sol y la luna para que sincronize el comportamiento
	DAY_MANAGER.InitializeSunAndMoon(sun, moon);

}

void EntityManager::InitializeSpawnPoints()
{
	//Agregamos unos puntos de spawn hardcodeados
	spawnPoints.push_back(glm::vec3(4.f, 0.f, -3.f));
	spawnPoints.push_back(glm::vec3(-2.5f, 0.f, 0.2f));
	spawnPoints.push_back(glm::vec3(-4.f, 0.f, -2.6f));
	spawnPoints.push_back(glm::vec3(0.5f, 0.f, 5.f));
	spawnPoints.push_back(glm::vec3(2.4f, 0.f, 1.7f));
	spawnPoints.push_back(glm::vec3(0.6f, 0.f, -0.9f));
	spawnPoints.push_back(glm::vec3(-1.f, 0.f, -4.f));

	//Definimos cuales de estos puntos de spawn estan siendo utilizados
	for (int i = 0; i < spawnPoints.size(); i++)
		usedSpawnPoint.push_back(false);

}

void EntityManager::InitializeEntities()
{
	int modelsInScene = 3; //Cantidad de modelos totales en la escena
	int programId = 0; //Id del programa que utilizan las entidades con textura
	int totalModels = MODELS.GetTotalModels();
	int randomStarterModel = (rand() % totalModels); //Modelo y textura random por el que empezaremos a colocar las entidades

	for (int i = 0; i < modelsInScene; i++)
	{
		//Seleccionar un modelo y textura random utilizando el generado anteriormente 
		//Para que no se repita tanto cada vez que se abre el programa
		int currentModelAndTexture = (randomStarterModel + i) % totalModels;

		float minScale = 0.6f;
		int maxScale = 1;
		//Generar una escala random entre 0.5 y 3.5 (es solo un float para que sea uniforme)
		float randomScale = (float)(rand() % maxScale) + minScale;

		entities.push_back(new GameObject(
				PROGRAMS.GetCompiledPrograms()[programId],
				GetRandomUnusedPosition(), //Seleccionar un punto de spawn random
				glm::vec3(0.f, rand() % 360, 0.f), //Generar rotacion random
				glm::vec3(randomScale), //Aplicar escala random
				MODELS.GetModel(currentModelAndTexture),
				Light(1.f, 1.f, 1.f, 0.1f), //Luz ambiental
				currentModelAndTexture //Id de la texura
		));
	}
}

glm::vec3 EntityManager::GetRandomUnusedPosition()
{
	//Generamos un id random
	int randomPosId = rand() % spawnPoints.size();
	glm::vec3 randomPos;
	//Comprobamos si este punto de spawn esta en uso
	//Si lo esta llamaremos de nuevo a esta funcion haciendola recursiva
	if (usedSpawnPoint[randomPosId])
		randomPos = GetRandomUnusedPosition();
	else
	{
		//En caso de que no este utilizado lo sera la posicion que devolvamos y lo marcaremos como usado
		randomPos = spawnPoints[randomPosId];
		usedSpawnPoint[randomPosId] = true;
	}


	return randomPos;
}


