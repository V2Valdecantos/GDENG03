#pragma once
#include "Component.h"
#include "PhysicsSystem.h"
#include <reactphysics3d/reactphysics3d.h>

using namespace reactphysics3d;

class PhysicsComponent : public Component
{
public:
	PhysicsComponent(String name, GameObject* owner);
	~PhysicsComponent();
	void perform(float deltaTime) override;
	RigidBody* getRigidbody();

public:
	float mass = 1000.0f;

private:
	RigidBody* rigidBody;

	friend class GameObject;

};

