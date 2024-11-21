#include "Camera.h"
#include <iostream>

Camera::Camera(String name) : GameObject(name)
{
	std::cout << "Camera has been created" << std::endl;
	this->setPosition(0, 0, -2);
	updateViewMatrix();
}

Camera::~Camera()
{
}

void Camera::updateViewMatrix()
{
	Matrix4x4 worldCam; worldCam.setIdentity();
	Matrix4x4 temp; temp.setIdentity();
	Vector3D localRot = this->getLocalRotation();

	temp.setIdentity();
	temp.setRotationX(localRot.m_x);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationY(localRot.m_y);
	worldCam *= temp;

	temp.setIdentity();
	temp.setRotationZ(localRot.m_z);
	worldCam *= temp;

	temp.setIdentity();
	temp.setTranslation(this->getLocalPosition());
	worldCam *= temp;


	worldCam.inverse();
	this->localMatrix = worldCam;
}

Matrix4x4 Camera::getViewMatrix()
{
	return this->localMatrix;
}

void Camera::update(float deltaTime, RECT windowBounds)
{
	//std::cout << "Camera is being updated" << std::endl;
	Vector3D localPos = this->getLocalPosition();
	float x = localPos.m_x;
	float y = localPos.m_y;
	float z = localPos.m_z;

	Vector3D localRot = this->getLocalRotation();

	float r_x = localRot.m_x;
	float r_y = localRot.m_y;
	float r_z = localRot.m_z;

	float moveSpeed = 10.0f;

	if (InputSystem::getInstance()->isKeyDown('W')) {

		std::cout << "Camera moving through Z axis" << std::endl;
		z += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}


	else if (InputSystem::getInstance()->isKeyDown('S')) {

		z -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}


	else if (InputSystem::getInstance()->isKeyDown('A')) {

		x += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}


	else if (InputSystem::getInstance()->isKeyDown('D')) {

		x -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('Q')) {
		y += deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('E')) {
		y -= deltaTime * moveSpeed;
		this->setPosition(x, y, z);
		this->updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('R')) {
		r_y += deltaTime * moveSpeed;
		this->setRotation(r_x, r_y, r_z);
		this->updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('T')) {
		r_y -= deltaTime * moveSpeed;
		this->setRotation(r_x, r_y, r_z);
		this->updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('1')) {
		r_x += deltaTime * moveSpeed;
		this->setRotation(r_x, r_y, r_z);
		this->updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('2')) {
		r_x -= deltaTime * moveSpeed;
		this->setRotation(r_x, r_y, r_z);
		this->updateViewMatrix();
	}


	else if (InputSystem::getInstance()->isKeyDown('3')) {
		r_z += deltaTime * moveSpeed;
		this->setRotation(r_x, r_y, r_z);
		this->updateViewMatrix();
	}

	else if (InputSystem::getInstance()->isKeyDown('4')) {
		r_z -= deltaTime * moveSpeed;
		this->setRotation(r_x, r_y, r_z);
		this->updateViewMatrix();
	}


}

void Camera::draw(int width, int height, float deltaTime, VertexShader* vertexShader, PixelShader* pixelShader)
{ }

void Camera::onKeyDown(int key)
{
}

void Camera::onKeyUp(int key)
{
}

void Camera::onMouseMove(const Point mouse_pos)
{
}

void Camera::onLeftMouseDown(const Point mouse_pos)
{
}

void Camera::onLeftMouseUp(const Point mouse_pos)
{
}

void Camera::onRightMouseDown(const Point mouse_pos)
{
	this->mouseDown = true;
}

void Camera::onRightMouseUp(const Point mouse_pos)
{
	this->mouseDown = false;
}

bool Camera::release()
{
	InputSystem::getInstance()->removeListener(this);
	delete this;
	return true;
}


