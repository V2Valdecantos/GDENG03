#include "ObjectManager.h"

ObjectManager::~ObjectManager()
{
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

void ObjectManager::popObject()
{
	if(this->objects.size() > 0)
		this->objects.pop_back();
}

void ObjectManager::clearObjects()
{
	this->objects.clear();
}


void ObjectManager::Update(float deltaTime)
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->Update(deltaTime, CameraManager::getInstance()->getViewMatrix(), CameraManager::getInstance()->getProjMatrix());
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
