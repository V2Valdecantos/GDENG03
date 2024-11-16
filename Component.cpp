#include "Component.h"

Component::Component(std::string name, GameObject* owner)
{
	this->name = name;
	this->owner = owner;
	this->type = ComponentType::PHYSICS;
}

Component::~Component()
{
}

void Component::attachOwner(GameObject* owner)
{
	this->owner = owner;
}

void Component::detachOwner()
{
	this->owner = NULL;
}

GameObject* Component::getOwner()
{
	return this->owner;
}

ComponentType Component::getType()
{
	return this->type;
}

std::string Component::getName()
{
	return this->name;
}
