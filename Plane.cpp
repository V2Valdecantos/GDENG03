#include "Plane.h"

Plane::Plane(string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	this->setRotation(90.0f, 0, 0);

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,0.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{Vector3D(-0.5f,0.5f,0.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(0.5f,0.5f,0.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		{ Vector3D(0.5f,-0.5f,0.0f),     Vector3D(1,1,1),  Vector3D(1,1,1) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.0f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.0f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.0f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.0f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	this->vertexBuffer = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);
	this->vertexBuffer->load(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);

	unsigned int index_list[] =
	{
		//FRONT SIDE
		0,1,2,  //FIRST TRIANGLE
		2,3,0,  //SECOND TRIANGLE
		//BACK SIDE
		4,5,6,
		6,7,4,
	};


	this->indexBuffer = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->indexBuffer->load(index_list, size_index_list);

	this->cbData = {};
	this->constantBuffer = GraphicsEngine::get()->createConstantBuffer();
	this->constantBuffer->load(&cbData, sizeof(CBData));
}

Plane::~Plane()
{
}

void Plane::update(float deltaTime)
{
	this->constantBuffer->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cbData);
}

void Plane::draw(Window* window)
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
	this->cbData.m_proj.setPerspectiveFovLH(90, width / height, 0.1f, 1000.0f);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(vertexShader, this->constantBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(pixelShader, this->constantBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->indexBuffer);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->vertexBuffer);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(vertexShader);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(pixelShader);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->indexBuffer->getSizeIndexList(), 0, 0);
}
