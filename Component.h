#pragma once
#include "ComponentTypes.h"
#include "GameObject.h"
#include <string>

class GameObject;
class Component
{
	public:
		Component(std::string name);
		~Component();

		void attachOwner(GameObject* owner);
		void detachOwner();
		GameObject* getOwner();
		ComponentType getType();
		std::string getName();

		virtual void perform(float deltaTime) = 0;

	protected:
		GameObject* owner;
		ComponentType type;
		std::string name;
};

