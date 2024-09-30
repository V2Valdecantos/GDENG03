#pragma once

#include <vector>
#include "GameObject.h"
#include "Structs.h"

class GameObject;

class ObjectManager
{
	public:
		~ObjectManager();
		
		void addObject(GameObject* newObj);
		void removeObject(GameObject* obj);
		void Update();

		std::vector<vertex> getVertexList();
		std::vector<GameObject*> getObjects();

	private:
		std::vector<GameObject*> objects;


	private:
		static ObjectManager* P_SHARED_INSTANCE;

	private:
		ObjectManager();
		ObjectManager(const ObjectManager&);
		ObjectManager& operator = (const ObjectManager&);

	public:
		static ObjectManager* getInstance();
};
