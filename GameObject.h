#pragma once
#pragma message ("GO is defined")
#include <iostream>
#include <vector>
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "Window.h"
#include "Structs.h"
#include "Component.h"
using namespace std;

class VertexShader;
class PixelShader;
class VertexBuffer;
class ConstantBuffer;
class IndexBuffer;
class Component;

class GameObject
{
	public:
		GameObject(string name);
		~GameObject();

		virtual void Update(float deltaTime, Matrix4x4 view, Matrix4x4 proj) = 0;
		virtual void draw(Window* window) = 0;

		void setPosition(float x, float y, float z);
		void setPosition(Vector3D pos);
		Vector3D getLocalPosition();

		void setScale(float x, float y, float z);
		void setScale(Vector3D scale);
		Vector3D getLocalScale();

		void setRotation(float x, float y, float z);
		void setRotation(Vector3D rot);
		void addRotation(float x, float y, float z);
		Vector3D getLocalRotation();

		void setColor(float x, float y, float z);
		Vector3D getColor();

		Matrix4x4 getLocalMatrix();
		float* getPhysicsLocalMatrix();
		void setLocalMatrix(Matrix4x4 matrix);
		void setLocalMatrix(float matrix[16]);
		void recomputeMatrix(float matrix[16]);
		string getName();

		void addComponent(Component* component);
		void removeComponent(Component* component);
	
	protected:
		string name;
		Vector3D color;
		Vector3D localPosition;
		Vector3D localScale;
		Vector3D localRotation;
		Matrix4x4 localMatrix;

		Matrix4x4 viewMat;
		Matrix4x4 projMat;

		std::vector<Component*> components;
		bool overrideMatrix = false;
};


