#pragma once

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
};

class GameObject
{	

	private:
		GameObject();
		~GameObject();

	protected:
		vertex vertices;
		vec3 offset;

	public:
		virtual void OnEnable();
		virtual void Update();
		virtual void Draw() = 0;
		
};

