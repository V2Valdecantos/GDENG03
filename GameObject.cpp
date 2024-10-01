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
	this->color = { 255, 255, 255 };
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

void GameObject::setScale(float scale)
{
	this->scale = scale;
}

void GameObject::setColor(vec3 color)
{
	this->color = color;
}

void GameObject::UpdateVertices()
{

}

void GameObject::Draw()
{
	int v_drawn = 0;
	for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++)
	{
		GraphicsEngine::get()->getImmediateDeviceContext()->drawTriangleStrip(ObjectManager::getInstance()->getObjects().at(i)->GetVertices().size(), v_drawn);
		v_drawn += int(ObjectManager::getInstance()->getObjects().at(i)->GetVertices().size());
	}
}

std::vector<vertex> GameObject::GetVertices()
{
	return this->vertices;
}
