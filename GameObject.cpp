#include "GameObject.h"

GameObject::GameObject(string name)
{
	this->name = name;
	this->localPosition = Vector3D(0, 0, 0);
	this->localScale = Vector3D(1, 1, 1);
	this->localRotation = Vector3D(0, 0, 0);
	this->color = Vector3D(0.8, 0.8, 0.8); 
}

GameObject::~GameObject()
{
}

void GameObject::Update(float deltaTime, Matrix4x4 view, Matrix4x4 proj)
{
}

void GameObject::draw(Window* window)
{
}

void GameObject::setPosition(float x, float y, float z)
{
	this->localPosition = Vector3D(x, y, z);
}

void GameObject::setPosition(Vector3D pos)
{
	this->localPosition = pos;
}

Vector3D GameObject::getLocalPosition()
{
	return this->localPosition;
}

void GameObject::setScale(float x, float y, float z)
{
	this->localScale = Vector3D(x, y, z);
}

void GameObject::setScale(Vector3D scale)
{
	this->localScale = scale;
}

Vector3D GameObject::getLocalScale()
{
	return this->localScale;
}

void GameObject::setRotation(float x, float y, float z)
{
	this->localRotation = Vector3D(x, y, z);
}

void GameObject::setRotation(Vector3D rot)
{
	this->localRotation = rot;
}

void GameObject::addRotation(float x, float y, float z)
{
	this->localRotation.m_x += x;
	this->localRotation.m_y += y;
	this->localRotation.m_z += z;
}

Vector3D GameObject::getLocalRotation()
{
	return this->localRotation;
}

void GameObject::setColor(float x, float y, float z)
{
	this->color = Vector3D(x, y, z);
}

Vector3D GameObject::getColor()
{
	return this->color;
}

string GameObject::getName()
{
	return this->name;
}
