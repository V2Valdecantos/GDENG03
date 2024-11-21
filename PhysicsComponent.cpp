#include "PhysicsComponent.h"
#include "GameObject.h"

PhysicsComponent::PhysicsComponent(String name, GameObject* owner) : Component(name, ComponentType::Physics, owner)
{
	BaseComponentSystem::getInstance()->getPhysicsSystem()->registerComponent(this);
	PhysicsCommon* physicsCommon = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsCommon();
	PhysicsWorld* physicsWorld = BaseComponentSystem::getInstance()->getPhysicsSystem()->getPhysicsWorld();
	// Create a rigid body in the world
	Vector3D scale = this->getOwner()->getLocalScale();
	Vector3 position;
	position.x = this->getOwner()->getLocalPosition().m_x;
	position.y = this->getOwner()->getLocalPosition().m_y;
	position.z = this->getOwner()->getLocalPosition().m_z;

	//Quaternion q = Quaternion(this->getOwner()->getLocalRotation().m_x, this->getOwner()->getLocalRotation().m_y, this->getOwner()->getLocalRotation().m_z, 1);
	Transform transform;
	//transform.setPosition(position);
	//transform.setOrientation(q);
	transform.setFromOpenGL(this->getOwner()->getLocalPhysicsMatrix());

	BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x, scale.m_y, scale.m_z));
	this->rigidBody = physicsWorld->createRigidBody(transform);
	this->rigidBody->addCollider(boxShape, transform);
	this->rigidBody->updateMassPropertiesFromColliders();
	this->rigidBody->setMass(this->mass);
	this->rigidBody->setType(BodyType::DYNAMIC);

	transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);

}

PhysicsComponent::~PhysicsComponent()
{
}

void PhysicsComponent::perform(float deltaTime)
{
	const Transform transform = this->rigidBody->getTransform();
	float matrix[16];
	transform.getOpenGLMatrix(matrix);

	this->getOwner()->recomputeMatrix(matrix);
}


RigidBody* PhysicsComponent::getRigidbody()
{
	return this->rigidBody;
}
