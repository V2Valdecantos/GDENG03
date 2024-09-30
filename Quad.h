#pragma once
#include "GameObject.h"

class Quad : public GameObject
{ 
	public:
		Quad();
		Quad(vec3 pos);
		~Quad();

		void OnEnable() override;
		void Update() override;

		void Move(vec3 newPos) override;
		void setScale(float scale) override;
		void setColor(vec3 color) override;
		void UpdateVertices() override;
};


