#include "GameObject.h"

GameObject::GameObject() 
{
	this->position = {0, 0, 0};
	this->scale = 1;
	this->color = { 255, 255, 255 };

	//ObjectManager::getInstance()->addObject(this);
}

GameObject::GameObject(vec3 pos)
{
	this->position = pos;
	this->scale = 1;
	//ObjectManager::getInstance()->addObject(this);
}

GameObject::~GameObject()
{
}

void GameObject::OnEnable()
{
}

void GameObject::Update()
{
}

vec3 GameObject::GetPosition() 
{
	return this->position;
}

void GameObject::Move(vec3 newPos) 
{
	this->position = newPos;
}

std::vector<vertex> GameObject::GetVertices()
{
	return std::vector<vertex>();
}
