#include "Component.h"
#include "GameObject.h"

Component::Component(String name, ComponentType type, GameObject* owner)
{
	this->name = name;
	this->type = type;
	this->owner = owner;
}

Component::~Component()
{
	if(!this->owner)
		this->detachOwner();

	delete this;
}

void Component::attachOwner(GameObject* owner)
{
	//this->owner = owner;
	this->owner = owner;
}

void Component::perform(float deltaTime) {

}

void Component::detachOwner()
{
	this->owner = nullptr;
}

GameObject* Component::getOwner()
{
	return this->owner;
}

Component::ComponentType Component::getType()
{
	return this->type;
}

Component::String Component::getName()
{
	return this->name;
}
