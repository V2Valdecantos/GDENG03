#include "Cube.h"
#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "SwapChain.h"
#include "DeviceContext.h"


Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,0.5,1), Vector3D(1,1,1) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,0.3,1),  Vector3D(1,0.3,1) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,1), Vector3D(1,0.3,1) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(1,1,1), Vector3D(1,1,1), },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(1,0.5,1), Vector3D(1,0,1) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(1,0.3,1),  Vector3D(1,0.3,1) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(1,0,1),  Vector3D(1,0.5,1) }

	};

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	this->vertexBuffer->load(vertex_list, sizeof(vertex), ARRAYSIZE(vertex_list), shaderByteCode, sizeShader);


	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
		//TOP SIDE
		1,6,5,
		5,2,1,
		//BOTTOM SIDE
		7,0,3,
		3,4,7,
		//RIGHT SIDE
		3,2,5,
		5,4,3,
		//LEFT SIDE
		7,6,1,
		1,0,7
	};

	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	this->indexBuffer->load(index_list, ARRAYSIZE(index_list));

	this->cbData = {};
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(CBData));
}

Cube::~Cube()
{
}

void Cube::update(float deltaTime)
{
	this->cbData.m_time = ::GetTickCount();

	this->deltaPos += deltaTime / 10.0f;
	if (this->deltaPos > 1.0f)
		this->deltaPos = 0;


	Matrix4x4 temp;

	this->deltaScale += deltaTime * this->speed;

	//cc.m_world.setScale(Vector3D::lerp(Vector3D(0.5, 0.5, 0), Vector3D(1.0f, 1.0f, 0), (sin(m_delta_scale) + 1.0f) / 2.0f));
	
	//temp.setTranslation(Vector3D::lerp(Vector3D(-1.5f, -1.5f, 0), Vector3D(1.5f,1.5f, 0), m_delta_pos));

	//cc.m_world *= temp;

	this->setRotation(this->deltaScale, this->deltaScale, this->deltaScale);

	this->constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cbData);

}

void Cube::draw(int width, int height, VertexShader* vertexShader, PixelShader* pixelShader)
{

	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
	else {
		this->deltaPos += this->deltaTime * 0.1f;
	}

	Matrix4x4 allMatrix; 
	Matrix4x4 temp;

	allMatrix.setIdentity();
	allMatrix.setScale(this->localScale);

	temp.setIdentity();
	temp.setRotationZ(this->localRotation.m_z);
	allMatrix *= temp;

	temp.setIdentity();
	temp.setRotationY(this->localRotation.m_y);
	allMatrix *= temp;

	temp.setIdentity();
	temp.setRotationX(this->localRotation.m_x);
	allMatrix *= temp;

	temp.setIdentity();
	temp.setTranslation(this->localPosition);
	allMatrix *= temp;

	this->cbData.m_world = allMatrix;
	this->cbData.m_view.setIdentity();
	this->cbData.m_proj.setOrthoLH(width / 400, height / 400, -4.0f, 4.0f);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, this->constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, this->constantBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->indexBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vertexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);

}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
