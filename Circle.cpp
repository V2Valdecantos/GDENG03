#include "Circle.h"

Circle::Circle()
{
	this->UpdateVertices();
	ObjectManager::getInstance()->addObject(this);
}

Circle::Circle(vec3 pos, vec3 vel, float radius)
{
	this->position = pos;
	this->velocity = vel;
	this->radius = radius;
	this->UpdateVertices();
	ObjectManager::getInstance()->addObject(this);
}

Circle::~Circle()
{
}

void Circle::OnEnable()
{
}

void Circle::Update()
{
	this->position.x += this->velocity.x * EngineTime::getDeltaTime();
	this->position.y += this->velocity.y * EngineTime::getDeltaTime();

	if (this->position.x >= 1 - this->radius) 
	{
		this->velocity.x *= -1;
		this->position.x = 1 - this->radius;
	}
	if (this->position.x <= -1 + this->radius)
	{
		this->velocity.x *= -1;
		this->position.x = -1 + this->radius;
	}

	if (this->position.y >= 1 - this->radius)
	{
		this->velocity.y *= -1;
		this->position.y = 1 - this->radius;
	}
	if (this->position.y <= -1 + this->radius)
	{
		this->velocity.y *= -1;
		this->position.y = -1 + this->radius;
	}
}

void Circle::Move(vec3 newPos)
{
	this->position = newPos;
	this->UpdateVertices();
}

void Circle::setScale(float scale)
{
	this->scale = scale;
	this->UpdateVertices();
}

void Circle::setColor(vec3 color)
{
	this->color = color;
	this->UpdateVertices();
}

void Circle::UpdateVertices()
{
	this->vertices.clear();

	int nTriangles = 100;
	int counter = 1;

	float angleStep = (2.0f * 3.141592653) / nTriangles;

	for (int i = 0; i <= nTriangles; ++i) {
		float angle = i * angleStep;
		if (counter == 2) 
		{
			vertices.push_back({ this->position, this->color });
			counter = 0;
		}
		else 
		{
			counter++;
		}

		float x = this->radius * cos(angle);
		float y = this->radius * sin(angle);
		vertices.push_back({ vec3{this->position.x + x, this->position.y + y, 0.0f }, this->color });
		
	}
}

void Circle::Draw()
{
	//int v_drawn = 0;
	//for (int i = 0; i < ObjectManager::getInstance()->getObjects().size(); i++)
	//{
	//	GraphicsEngine::get()->getImmediateDeviceContext()->drawPoints(this->GetVertices().size(), v_drawn);
	//	v_drawn += int(ObjectManager::getInstance()->getObjects().at(i)->GetVertices().size());
	//}
}
