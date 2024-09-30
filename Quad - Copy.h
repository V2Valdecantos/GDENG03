#pragma once
#include "GameObject.h"

class Quad : public GameObject
{ 
	private:
		Quad();
		~Quad();

	public:
		void OnEnable() override;
		void Update() override;
		void Draw() override;
};

