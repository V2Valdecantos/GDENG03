#pragma once

#include <vector>
#include "ObjectManager.h"
#include "Structs.h"

class GameObject
{
	public:		
		GameObject();
		GameObject(vec3 pos);
		~GameObject();
		virtual void OnEnable();
		virtual void Update();

		vec3 GetPosition();
		virtual void Move(vec3 newPos);
		std::vector<vertex> GetVertices();

	protected:
		vec3 position;
		float scale;
		vec3 color;
		std::vector<vertex> vertices;


		
};