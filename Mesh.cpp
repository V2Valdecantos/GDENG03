#include "Mesh.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include <tiny_obj_loader.h>

#include <locale>
#include <codecvt>

#include "GraphicsEngine.h"
#include "VertexMesh.h"

Mesh::Mesh(const wchar_t* full_path): Resource(full_path)
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	std::wstring ws(full_path);
	std::string inputfile(ws.begin(), ws.end());
	this->path = inputfile;

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, inputfile.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	int vector_size = 0;
	for (size_t s = shapes.size(); s-- > 0; ) {
		vector_size += shapes[s].mesh.indices.size();
	}

	tinyobj::real_t tx, ty;
	
	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(vector_size);
		list_indices.reserve(vector_size);

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = attribs.vertices[index.vertex_index * 3];
				tinyobj::real_t vy = attribs.vertices[index.vertex_index * 3 + 1];
				tinyobj::real_t vz = attribs.vertices[index.vertex_index * 3 + 2];

				if (attribs.texcoords.size() != 0) 
				{
					tx = attribs.texcoords[index.texcoord_index * 2];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}
				else 
				{
					tx = 0;
					ty = 0;
				}

				

				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	m_vertex_buffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
	m_index_buffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&list_indices[0], (UINT)list_indices.size());

}


Mesh::~Mesh()
{
}

const VertexBufferPtr & Mesh::getVertexBuffer()
{
	return m_vertex_buffer;
}

const IndexBufferPtr & Mesh::getIndexBuffer()
{
	return m_index_buffer;
}

void Mesh::setScale(float scale)
{
	this->scale = scale;
	this->updateMesh();
}

void Mesh::Move(float x, float y, float z)
{
	this->pos_x = x;
	this->pos_y = y;
	this->pos_z = z;
	this->updateMesh();
}

void Mesh::updateMesh()
{
	tinyobj::attrib_t attribs;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string warn;
	std::string err;

	bool res = tinyobj::LoadObj(&attribs, &shapes, &materials, &warn, &err, path.c_str());

	if (!err.empty()) throw std::exception("Mesh not created successfully");

	if (!res) throw std::exception("Mesh not created successfully");

	if (shapes.size() > 1) throw std::exception("Mesh not created successfully");

	std::vector<VertexMesh> list_vertices;
	std::vector<unsigned int> list_indices;

	int vector_size = 0;
	for (size_t s = shapes.size(); s-- > 0; ) {
		vector_size += shapes[s].mesh.indices.size();
	}

	tinyobj::real_t tx, ty;

	for (size_t s = 0; s < shapes.size(); s++)
	{
		size_t index_offset = 0;
		list_vertices.reserve(vector_size);
		list_indices.reserve(vector_size);

		for (size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++)
		{
			unsigned char num_face_verts = shapes[s].mesh.num_face_vertices[f];

			for (unsigned char v = 0; v < num_face_verts; v++)
			{
				tinyobj::index_t index = shapes[s].mesh.indices[index_offset + v];

				tinyobj::real_t vx = (attribs.vertices[index.vertex_index * 3] + pos_x) * scale;
				tinyobj::real_t vy = (attribs.vertices[index.vertex_index * 3 + 1] + pos_y) * scale;
				tinyobj::real_t vz = (attribs.vertices[index.vertex_index * 3 + 2] + pos_z)  * scale;

				if (attribs.texcoords.size() != 0)
				{
					tx = attribs.texcoords[index.texcoord_index * 2];
					ty = attribs.texcoords[index.texcoord_index * 2 + 1];
				}
				else
				{
					tx = 0;
					ty = 0;
				}



				VertexMesh vertex(Vector3D(vx, vy, vz), Vector2D(tx, ty));
				list_vertices.push_back(vertex);

				list_indices.push_back((unsigned int)index_offset + v);
			}

			index_offset += num_face_verts;
		}
	}

	void* shader_byte_code = nullptr;
	size_t size_shader = 0;
	GraphicsEngine::get()->getVertexMeshLayoutShaderByteCodeAndSize(&shader_byte_code, &size_shader);
	m_vertex_buffer = GraphicsEngine::get()->getRenderSystem()->createVertexBuffer(&list_vertices[0], sizeof(VertexMesh),
		(UINT)list_vertices.size(), shader_byte_code, (UINT)size_shader);
	m_index_buffer = GraphicsEngine::get()->getRenderSystem()->createIndexBuffer(&list_indices[0], (UINT)list_indices.size());

}
