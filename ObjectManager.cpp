#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
}

std::vector<vertex> ObjectManager::getVertexList()
{
	std::vector<vertex> vertices;

	for (int i = 0; i < this->objects.size(); i++) 
	{
		for (int j = 0; j < this->objects[i]->GetVertices().size(); j++)
		{
			vertices.push_back(this->objects[i]->GetVertices()[j]);
		}
		
	}

	return vertices;
}

std::vector<GameObject*> ObjectManager::getObjects()
{
	return this->objects;
}

void ObjectManager::addObject(GameObject* newObj)
{
	this->objects.push_back(newObj);
}

void ObjectManager::removeObject(GameObject* obj)
{
	for (int i = 0; i < this->objects.size(); i++) 
	{
		if (this->objects[i] == obj) 
		{
			this->objects.erase(this->objects.begin() + i);
		}
	}
}

void ObjectManager::Update()
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Update();
	}

	if (cycleMode == 1)
	{
		this->red -= 0.01;

		if (this->red <= 0.5)
			this->cycleMode = 2;

	}
	if (cycleMode == 2)
	{
		this->red -= 0.01;
		this->blue += 0.03;

		if (this->blue >= 1)
			this->cycleMode = 3;

	}
	if (cycleMode == 3)
	{
		this->blue -= 0.01;

		if (this->blue <= 0.5)
			this->cycleMode = 4;

	}
	if (cycleMode == 4)
	{
		this->blue -= 0.01;
		this->green += 0.03;

		if (this->green >= 1)
			this->cycleMode = 5;

	}
	if (cycleMode == 5)
	{
		this->green -= 0.01;

		if (this->green <= 0.5)
			this->cycleMode = 6;

	}
	if (cycleMode == 6)
	{
		this->green -= 0.01;
		this->red += 0.03;

		if (this->red >= 1)
			this->cycleMode = 1;

	}

	for (int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->setColor({ red, green, blue });

	}
		
}

void ObjectManager::MakeRandomQuad()
{

}


ObjectManager* ObjectManager::P_SHARED_INSTANCE = NULL;
ObjectManager::ObjectManager() {}
ObjectManager::ObjectManager(const ObjectManager&) {}

ObjectManager* ObjectManager::getInstance() {
	if (P_SHARED_INSTANCE == NULL)
		P_SHARED_INSTANCE = new ObjectManager();

	return P_SHARED_INSTANCE;
}
