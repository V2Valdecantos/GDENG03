#include "BaseComponentSystem.h"
#include "PhysicsSystem.h"

BaseComponentSystem* BaseComponentSystem::sharedInstance = nullptr;

BaseComponentSystem* BaseComponentSystem::getInstance()
{
	return sharedInstance;
}

void BaseComponentSystem::initialize()
{
	if (!sharedInstance) {
		sharedInstance = new BaseComponentSystem();
		sharedInstance->physicsSystem = new PhysicsSystem();
	}
}

void BaseComponentSystem::destroy()
{
	if (sharedInstance != NULL) {
		delete sharedInstance;
	}
}

PhysicsSystem* BaseComponentSystem::getPhysicsSystem()
{
	return this->physicsSystem;
}


BaseComponentSystem::BaseComponentSystem() {
	
}

BaseComponentSystem::~BaseComponentSystem()
{
	
}
