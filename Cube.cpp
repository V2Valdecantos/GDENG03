#include "Cube.h"



Cube::Cube(string name, ConstantBuffer* m_cb) : GameObject(name)
{
	vertex vertex_list[] =
	{
		//X - Y - Z
		////FRONT FACE
		//{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		//{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		//{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		//{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		////BACK FACE
		//{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		//{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		//{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		//{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }


		//wCOLOR INPUT
		{Vector3D(-0.5f,-0.5f,-0.5f),  this->color,  this->color },
		{Vector3D(-0.5f,0.5f,-0.5f),   this->color,  this->color },
		{ Vector3D(0.5f,0.5f,-0.5f),   this->color,  this->color },
		{ Vector3D(0.5f,-0.5f,-0.5f),  this->color,  this->color },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),   this->color,  this->color },
		{ Vector3D(0.5f,0.5f,0.5f),    this->color,  this->color },
		{ Vector3D(-0.5f,0.5f,0.5f),   this->color,  this->color },
		{ Vector3D(-0.5f,-0.5f,0.5f),  this->color,  this->color }

		////PLANE
		//{ Vector3D(10.0f,0.0f,-100.0f),    Vector3D(1,1,1),  Vector3D(1,1,1) },
		//{ Vector3D(10.0f,0.0f,10.0f),		Vector3D(1,1,1),  Vector3D(1,1,1) },
		//{ Vector3D(10.0f,0.0f,-100.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) },
		//{ Vector3D(-10.0f,0.0f,10.0f),   Vector3D(1,1,1),  Vector3D(1,1,1) }

	};

	m_vb = GraphicsEngine::get()->createVertexBuffer();
	UINT size_list = ARRAYSIZE(vertex_list);


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

		////PLANE
		//8,9,10,
		//9,11,10
	};


	m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	m_ib->load(index_list, size_index_list);




	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	m_vs = GraphicsEngine::get()->createVertexShader(shader_byte_code, size_shader);
	m_vb->load(vertex_list, sizeof(vertex), size_list, shader_byte_code, size_shader);

	GraphicsEngine::get()->releaseCompiledShader();


	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	GraphicsEngine::get()->releaseCompiledShader();

	this->m_cb = m_cb;
}

Cube::~Cube()
{
}

void Cube::Update(float deltaTime, Matrix4x4 m_view)
{
	this->cbData.m_time = deltaTime;
	this->deltaPos += deltaTime / 10.0f;
	if (this->deltaPos > 1.0f)
		this->deltaPos = 0;

	this->deltaScale += deltaTime / 10.0f;
	if (this->deltaScale < 0.25f)
		this->deltaScale = 0;

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
	this->cbData.m_view = m_view;
	this->cbData.m_proj.setPerspectiveFovLH(1.57f, ((float)1024 / (float)768), 0.1f, 100.0f);

	this->m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cbData);

	

	//this->cbData.m_world.setScale(this->localScale);

	//this->setPosition(Vector3D::lerp(Vector3D(0, 0, 0), Vector3D(1.0f, 0.5f, 0), this->deltaPos));
	temp.setTranslation(this->localPosition);

	this->cbData.m_world *= temp;

	//this->setScale(Vector3D::lerp(Vector3D(1, 1, 1), Vector3D(0.25, 0.25, 0.25), this->deltaPos));
	temp.setScale(this->localScale);

	this->addRotation(this->speed * deltaTime, this->speed * deltaTime, this->speed * deltaTime);
	temp.setRotationX(this->localRotation.m_x);
	temp.setRotationY(this->localRotation.m_y);
	temp.setRotationZ(this->localRotation.m_z);

	this->m_cb->update(GraphicsEngine::get()->getImmediateDeviceContext(), &this->cbData);

}

void Cube::draw(Window* window)
{
	RECT rc = window->getClientWindowRect();
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	if (this->deltaPos > 1.0f) {
		this->deltaPos = 0.0f;
	}
	else {
		this->deltaPos += this->deltaTime * 0.1f;
	}

	//Matrix4x4 allMatrix;
	//Matrix4x4 temp;

	//allMatrix.setIdentity();
	//allMatrix.setScale(this->localScale);

	//temp.setIdentity();
	//temp.setRotationZ(this->localRotation.m_z);
	//allMatrix *= temp;

	//temp.setIdentity();
	//temp.setRotationY(this->localRotation.m_y);
	//allMatrix *= temp;

	//temp.setIdentity();
	//temp.setRotationX(this->localRotation.m_x);
	//allMatrix *= temp;

	//temp.setIdentity();
	//temp.setTranslation(this->localPosition);
	//allMatrix *= temp;

	//this->cbData.m_world = allMatrix;
	//this->cbData.m_view.setIdentity();
	//this->cbData.m_proj.setOrthoLH(width / 400, height / 400, -4.0f, 4.0f);

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_vs, m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(m_ps, m_cb);

	//SET DEFAULT SHADER IN THE GRAPHICS PIPELINE TO BE ABLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(m_ps);


	//SET THE VERTICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(m_vb);
	//SET THE INDICES OF THE TRIANGLE TO DRAW
	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(m_ib);


	// FINALLY DRAW THE TRIANGLE
	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(m_ib->getSizeIndexList(), 0, 0);

}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
