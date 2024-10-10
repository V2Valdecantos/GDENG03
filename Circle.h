#pragma once
#include "GameObject.h"
#include <cmath>

#define _USE_MATH_DEFINES

class Circle : public GameObject
{
	public:
		Circle();
		Circle(vec3 pos, vec3 vel, float radius);
		~Circle();
		void OnEnable() override;
		void Update() override;

		void Move(vec3 newPos) override;
		void setScale(float scale) override;
		void setColor(vec3 color) override;
		void UpdateVertices() override;
		void Draw() override;

	private:
		float radius;
		vec3 velocity;
};

