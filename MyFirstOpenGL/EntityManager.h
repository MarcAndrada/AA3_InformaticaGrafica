#pragma once
#include <vector>
#include <stdlib.h>
#include <ctime> 
#include "GameObject.h"
#include "Primitive.h"
#include "Camera.h"
#include "ModelManager.h"

#define ENTITIES EntityManager::Instance()


class EntityManager
{
public:
	inline static EntityManager& Instance()
	{
		static EntityManager manager;
		return manager;
	}



	inline Camera* GetCamera() { return (Camera*)entities[entities.size() - 1]; }
	void Initialize();
	void EntitiesUpdate();

private:
	EntityManager() = default;
	EntityManager(const EntityManager&) = delete;
	EntityManager& operator =(const EntityManager&) = delete;
	std::vector<Entity*> entities;
	std::vector<glm::vec3> spawnPoints;
	std::vector<bool> usedSpawnPoint;


	void InitializeSpawnPoints();
	void InitializeEntities();
	glm::vec3 GetRandomUnusedPosition();

};

