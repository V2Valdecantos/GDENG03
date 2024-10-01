#pragma once

#include <vector>
#include <cstdlib>
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

		void MakeRandomQuad();

		std::vector<vertex> getVertexList();
		std::vector<GameObject*> getObjects();

	private:
		std::vector<GameObject*> objects;
		float red = 1;
		float green = 0;
		float blue = 0;
		int cycleMode = 1;

	private:
		static ObjectManager* P_SHARED_INSTANCE;

	private:
		ObjectManager();
		ObjectManager(const ObjectManager&);
		ObjectManager& operator = (const ObjectManager&);

	public:
		static ObjectManager* getInstance();
};
