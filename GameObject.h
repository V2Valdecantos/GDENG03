#pragma once
#include <iostream>
#include "Matrix4x4.h"
#include "Vector3D.h"
#include "Window.h"
#include "Structs.h"

using namespace std;

class VertexShader;
class PixelShader;
class VertexBuffer;
class ConstantBuffer;
class IndexBuffer;

class GameObject
{
	public:
		GameObject(string name);
		~GameObject();

		virtual void Update(float deltaTime, Matrix4x4 m_view) = 0;
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

		string getName();
	
	protected:
		string name;
		Vector3D color;
		Vector3D localPosition;
		Vector3D localScale;
		Vector3D localRotation;
		Matrix4x4 localMatrix;
};


