#include "Cube.h"



Cube::Cube(string name, void* shaderByteCode, size_t sizeShader) : GameObject(name)
{
	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->compileVertexShader(L"VertexShader.hlsl", "vsmain", &shader_byte_code, &size_shader);

	vertex vertex_list[] =
	{
		//X - Y - Z
		//FRONT FACE
		{Vector3D(-0.5f,-0.5f,-0.5f),    Vector3D(1,0,0),  Vector3D(0.2f,0,0) },
		{Vector3D(-0.5f,0.5f,-0.5f),    Vector3D(1,1,0), Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,0.5f,-0.5f),   Vector3D(1,1,0),  Vector3D(0.2f,0.2f,0) },
		{ Vector3D(0.5f,-0.5f,-0.5f),     Vector3D(1,0,0), Vector3D(0.2f,0,0) },

		//BACK FACE
		{ Vector3D(0.5f,-0.5f,0.5f),    Vector3D(0,1,0), Vector3D(0,0.2f,0) },
		{ Vector3D(0.5f,0.5f,0.5f),    Vector3D(0,1,1), Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,0.5f,0.5f),   Vector3D(0,1,1),  Vector3D(0,0.2f,0.2f) },
		{ Vector3D(-0.5f,-0.5f,0.5f),     Vector3D(0,1,0), Vector3D(0,0.2f,0) }

	};

	this->m_vb = GraphicsEngine::get()->createVertexBuffer();
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
	};


	this->m_ib = GraphicsEngine::get()->createIndexBuffer();
	UINT size_index_list = ARRAYSIZE(index_list);

	this->m_ib->load(index_list, size_index_list);

	GraphicsEngine::get()->releaseCompiledShader();

	GraphicsEngine::get()->compilePixelShader(L"PixelShader.hlsl", "psmain", &shader_byte_code, &size_shader);
	m_ps = GraphicsEngine::get()->createPixelShader(shader_byte_code, size_shader);
	this->m_vb->load(vertex_list, sizeof(vertex), size_list, shaderByteCode, sizeShader);
	GraphicsEngine::get()->releaseCompiledShader();

	CBData cc;
	cc.m_time = 0;

	m_cb = GraphicsEngine::get()->createConstantBuffer();
	m_cb->load(&cc, sizeof(CBData));

	this->cbData = {};
	this->m_cb = GraphicsEngine::get()->createConstantBuffer();
	this->m_cb->load(&cbData, sizeof(CBData));
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

	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->m_vs, this->m_cb);
	GraphicsEngine::get()->getImmediateDeviceContext()->setConstantBuffer(this->m_ps, this->m_cb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setIndexBuffer(this->m_ib);
	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexBuffer(this->m_vb);

	GraphicsEngine::get()->getImmediateDeviceContext()->setVertexShader(this->m_vs);
	GraphicsEngine::get()->getImmediateDeviceContext()->setPixelShader(this->m_ps);

	GraphicsEngine::get()->getImmediateDeviceContext()->drawIndexedTriangleList(this->m_ib->getSizeIndexList(), 0, 0);

}

void Cube::setAnimSpeed(float speed)
{
	this->speed = speed;
}
