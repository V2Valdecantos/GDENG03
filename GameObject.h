#pragma once
#include <iostream>
#include "Matrix4x4.h"
#include "Vector3D.h"

using namespace std;

class VertexShader;
class PixelShader;

class GameObject
{
	public:
		GameObject(string name);
		~GameObject();

		virtual void update(float deltaTime) = 0;
		virtual void draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader) = 0;

		void setPosition(float x, float y, float z);
		void setPosition(Vector3D pos);
		Vector3D getLocalPosition();

		void setScale(float x, float y, float z);
		void setScale(Vector3D scale);
		Vector3D getLocalScale();

		void setRotation(float x, float y, float z);
		void setRotation(Vector3D rot);
		Vector3D getLocalRotation();

		string getName();

		struct vertex
		{
			Vector3D position;
			Vector3D color;
			Vector3D color1;
		};

		__declspec(align(16))
			struct CBData
		{
			Matrix4x4 m_world;
			Matrix4x4 m_view;
			Matrix4x4 m_proj;
			float m_time;
		};
	
	protected:
		string name;
		Vector3D localPosition;
		Vector3D localScale;
		Vector3D localRotation;
		Matrix4x4 localMatrix;
};


