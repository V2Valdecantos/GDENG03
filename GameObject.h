#pragma once

#include <vector>
#include "GraphicsEngine.h"
#include "DeviceContext.h"
#include "ObjectManager.h"
#include "Structs.h"
#include "WindowsX.h"

class GameObject
{
	public:		
		GameObject();
		GameObject(vec3 pos);
		~GameObject();
		virtual void OnEnable();
		virtual void Update();

		vec3 GetPosition();
		std::vector<vertex> GetVertices();

		virtual void Move(vec3 newPos);
		virtual void setScale(float scale);
		virtual void setColor(vec3 color); 
		virtual void UpdateVertices();
		virtual void Draw();

	protected:
		vec3 position;
		float scale;
		vec3 color;
		std::vector<vertex> vertices;


		
};