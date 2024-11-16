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
	this->viewMat = view;
	this->projMat = proj;

	for (Component* component : this->components) 
	{
		component->perform(deltaTime);
	}
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

Matrix4x4 GameObject::getLocalMatrix()
{
	return this->localMatrix;
}

float* GameObject::getPhysicsLocalMatrix()
{
	Matrix4x4 allMatrix; allMatrix.setIdentity();
	Matrix4x4 translationMatrix; translationMatrix.setIdentity();
	translationMatrix.setTranslation(this->getLocalPosition());

	Vector3D ones = { 1, 1, 1 };
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(ones); //physics 3D only accepts uniform scale for rigidbody
	Vector3D rotation = this->getLocalRotation();
	Matrix4x4 xMatrix; xMatrix.setRotationX(rotation.m_x);
	Matrix4x4 yMatrix; yMatrix.setRotationY(rotation.m_y);
	Matrix4x4 zMatrix; zMatrix.setRotationZ(rotation.m_z);

	//Scale --> Rotate --> Transform as recommended order.
	Matrix4x4 rotMatrix; rotMatrix.setIdentity();
	rotMatrix = rotMatrix.multiplyTo(xMatrix.multiplyTo(yMatrix.multiplyTo(zMatrix)));

	allMatrix = allMatrix.multiplyTo(scaleMatrix.multiplyTo(rotMatrix));
	allMatrix = allMatrix.multiplyTo(translationMatrix);

	return allMatrix.getMatrix();
}

void GameObject::setLocalMatrix(Matrix4x4 matrix)
{
	this->localMatrix = matrix;
}

void GameObject::setLocalMatrix(float matrix[16])
{
	int index = 0;
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			this->localMatrix.m_mat[i][j] = matrix[index];
			index++;
		}
	}
}

void GameObject::recomputeMatrix(float matrix[16])
{
	float matrix4x4[4][4];
	matrix4x4[0][0] = matrix[0];
	matrix4x4[0][1] = matrix[1];
	matrix4x4[0][2] = matrix[2];
	matrix4x4[0][3] = matrix[3];

	matrix4x4[1][0] = matrix[4];
	matrix4x4[1][1] = matrix[5];
	matrix4x4[1][2] = matrix[6];
	matrix4x4[1][3] = matrix[7];

	matrix4x4[2][0] = matrix[8];
	matrix4x4[2][1] = matrix[9];
	matrix4x4[2][2] = matrix[10];
	matrix4x4[2][3] = matrix[11];

	matrix4x4[3][0] = matrix[12];
	matrix4x4[3][1] = matrix[13];
	matrix4x4[3][2] = matrix[14];
	matrix4x4[3][3] = matrix[15];

	Matrix4x4 newMatrix; newMatrix.setMatrix(matrix4x4);
	Matrix4x4 scaleMatrix; scaleMatrix.setScale(this->localScale);
	Matrix4x4 transMatrix; transMatrix.setTranslation(this->localPosition);
	this->localMatrix = scaleMatrix.multiplyTo(transMatrix.multiplyTo(newMatrix));
	this->overrideMatrix = true;
}

string GameObject::getName()
{
	return this->name;
}

void GameObject::addComponent(Component* component)
{
	this->components.push_back(component);
}

void GameObject::removeComponent(Component* component)
{
	int index = 0;
	for (Component* comp : this->components) 
	{
		if (comp == component) 
		{
			this->components.erase(this->components.begin() + index);
		}
		index++;
	}
}
