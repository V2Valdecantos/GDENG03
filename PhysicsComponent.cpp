#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(std::string name) : Component(name)
{
	this->name = name;

	PhysicsCommon* physicsCommon = PhysicsSystem::getInstance()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = PhysicsSystem::getInstance()->getPhysicsWorld();	

	//convert vector3d to vector3
	Vector3 position;
	position.x = this->getOwner()->getLocalPosition().m_x;
	position.y = this->getOwner()->getLocalPosition().m_y;
	position.z = this->getOwner()->getLocalPosition().m_z;

	Vector3 rotation;
	position.x = this->getOwner()->getLocalRotation().m_x;
	position.y = this->getOwner()->getLocalRotation().m_y;
	position.z = this->getOwner()->getLocalRotation().m_z;

	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();
	Transform transform; transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2)); //half extent
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setLocalMatrix(matrix);
}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->setLocalMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
	return this->rigidBody;
}
