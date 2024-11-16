#pragma once
#include "Component.h"
#include "PhysicsSystem.h"
#include "Structs.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;
class PhysicsComponent : public Component
{
public:
	PhysicsComponent(std::string name, GameObject* owner);
	~PhysicsComponent();
	void perform(float deltaTime) override;

	RigidBody* getRigidBody();

private:
	float mass = 1000.0f; //in kilograms
	RigidBody* rigidBody;
};

