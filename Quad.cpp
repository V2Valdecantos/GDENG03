#include "Quad.h"

Quad::Quad()
{
	
	this->UpdateVertices();
	ObjectManager::getInstance()->addObject(this);
}

Quad::Quad(vec3 pos)
{
	
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

void Quad::UpdateVertices() 
{
	//set all vertices to position
	vertex bl, tl, br, tr;

	bl.position = this->position;
	bl.position1 = this->position;
	tl.position = this->position;
	tl.position1 = this->position;
	br.position = this->position;
	br.position1 = this->position;
	tr.position = this->position;
	tr.position1 = this->position;

	// offset all vertices accordingly using scale w/ bottom left being the anchor
	// top left
	tl.position.y += (0.5 * scale);
	tl .position1.y += (0.5 * scale);
	// bottom right
	tr.position.x += (0.5 * scale);
	tr.position1.x += (0.5 * scale);
	// top right
	br.position.y += (0.5 * scale);
	br.position.x += (0.5 * scale);
	br.position1.y += (0.5 * scale);
	br.position1.x += (0.5 * scale);

	//set color
	tl.color = this->color;
	tl.color1 = this->color;
	bl.color = this->color;
	bl.color1 = this->color;
	tr.color = this->color;
	tr.color1 = this->color;
	br.color = this->color;
	br.color1 = this->color;

	// push into the vector
	this->vertices.push_back(bl);
	this->vertices.push_back(tl);
	this->vertices.push_back(br);
	this->vertices.push_back(tr);
}