#include "Quad.h"

Quad::Quad()
{
	
	this->UpdateVertices();
	ObjectManager::getInstance()->addObject(this);
}

Quad::Quad(vec3 pos)
{
	this->position = pos;
	this->UpdateVertices();
	ObjectManager::getInstance()->addObject(this);
}

Quad::~Quad()
{
}

void Quad::OnEnable()
{
}

void Quad::Update()
{
	
}

void Quad::Move(vec3 newPos) 
{
	this->position = newPos;
	this->UpdateVertices();
}

void Quad::setScale(float scale)
{
	this->scale = scale;
	this->UpdateVertices();
}

void Quad::setColor(vec3 color)
{
	this->color = color;
	this->UpdateVertices();
}

void Quad::UpdateVertices() 
{
	this->vertices.clear();
	//set all vertices to position
	vertex bl, tl, br, tr;

	bl.position = this->position;
	tl.position = this->position;
	br.position = this->position;
	tr.position = this->position;

	// offset all vertices accordingly using scale w/ bottom left being the anchor
	// top left
	tl.position.y += (0.5 * this->scale);
	// bottom right
	br.position.x += (0.5 * this->scale);
	// top right
	tr.position.y += (0.5 * this->scale);
	tr.position.x += (0.5 * this->scale);

	//set color
	tl.color = this->color;
	bl.color = this->color;
	tr.color = this->color;
	br.color = this->color;

	// push into the vector
	this->vertices.push_back(bl);
	this->vertices.push_back(tl);
	this->vertices.push_back(br);
	this->vertices.push_back(tr);
}