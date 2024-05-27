#include "EntityManager.h"

void EntityManager::InitializeEntities()
{
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[1], glm::vec3(0.f, 0.f, -2.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f), MODELS.GetModel(0), Light(1.f, 1.f, 1.f, 1.f), 0)); //Troll Normal
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[1], glm::vec3(2.f, 0.f, 0.f), glm::vec3(0.f, 270, 0.f), glm::vec3(1.f), MODELS.GetModel(0), Light(0.322f, 0.525f, 1.f, 1.f), 0)); //Troll Azul
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[1], glm::vec3(-2.f, 0.f, 0.f), glm::vec3(0.f, 90.f, 0.f), glm::vec3(1.f), MODELS.GetModel(0), Light(0.349f, 1.f, 0.263f, 1.f), 0)); //Troll Verde
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[1], glm::vec3(0.5f, 0.f, 0.5f), glm::vec3(0.f, 45.f, 0.f), glm::vec3(0.7f, 0.4f, 0.7f), MODELS.GetModel(1), Light(1.f, 1.f, 1.f, 1.f), 1));//Piedra
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.5f, 0.f, -0.5f), glm::vec3(0.f, 135.f, 0.f), glm::vec3(0.7f, 0.4f, 0.7f), MODELS.GetModel(1), Light(1.f, 1.f, 1.f, 1.f), 1));//Piedra
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(-0.5f, 0.f, -0.5f), glm::vec3(0.f, 45.f, 0.f), glm::vec3(0.7f, 0.4f, 0.7f), MODELS.GetModel(1), Light(1.f, 1.f, 1.f, 1.f), 1));//Piedra
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(-0.5f, 0.f, 0.5f), glm::vec3(0.f, 135.f, 0.f), glm::vec3(0.7f, 0.4f, 0.7f), MODELS.GetModel(1), Light(1.f, 1.f, 1.f, 1.f), 1));//Piedra
																	 
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[1], glm::vec3(1.f, 4.f, -2.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 0.5f, 1.f), MODELS.GetModel(1), Light(1.f, 1.f, 1.f, 2.5f), 1));//Nube
	entities.push_back(new GameObject(PROGRAMS.GetCompiledPrograms()[1], glm::vec3(-2.f, 4.f, 1.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(1.f, 0.5f, 1.f), MODELS.GetModel(1), Light(1.f, 1.f, 1.f, 2.5f), 1));//Nube

	entities.push_back(new Primitive(PROGRAMS.GetCompiledPrograms()[0], glm::vec3(0.f, -1.f, 0.f), glm::vec3(0.f, 1.f, 0.f), glm::vec3(10.f, 1.f, 10.f), glm::vec4(0.7f, 0.5f, 0.f, 1.f), Light(0.3f, 0.3f, 0.3f, 1.f))); //Suelo

	entities.push_back(new Camera());
}

void EntityManager::EntitiesUpdate()
{
	for (Entity* item : entities)
	{
		item->Update();
		item->Render();
	}

}

