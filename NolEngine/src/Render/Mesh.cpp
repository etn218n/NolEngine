#include "PCH.h"
#include "Mesh.h"

namespace Nol
{
	Mesh::Mesh(const std::vector<Vertex>& vertices)
	{
		numberofVertices = vertices.size();
		numberofIndices = 0;

		GenerateMesh((const float*)vertices.data(), nullptr);
	}

	Mesh::Mesh(const std::vector<float>& vertices)
	{
		numberofVertices = vertices.size() / (sizeof(Vertex) / sizeof(float));
		numberofIndices = 0;

		GenerateMesh(vertices.data(), nullptr);
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Texture> textures) : textures(textures)
	{
		numberofVertices = vertices.size();
		numberofIndices  = 0;

		GenerateMesh((const float*)vertices.data(), nullptr);
	}

	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<Texture> textures) : textures(textures)
	{
		numberofVertices = vertices.size() / (sizeof(Vertex) / sizeof(float));
		numberofIndices  = 0;

		GenerateMesh(vertices.data(), nullptr);
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
	{
		numberofVertices = vertices.size();
		numberofIndices = indices.size();

		GenerateMesh((const float*)vertices.data(), indices.data());
	}

	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices)
	{
		numberofVertices = vertices.size() / (sizeof(Vertex) / sizeof(float));
		numberofIndices = indices.size();

		GenerateMesh(vertices.data(), indices.data());
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture> textures) : textures(textures)
	{
		numberofVertices = vertices.size();
		numberofIndices  = indices.size();

		GenerateMesh((const float*)vertices.data(), indices.data());
	}

	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture> textures) : textures(textures)
	{
		numberofVertices = vertices.size() / (sizeof(Vertex) / sizeof(float));
		numberofIndices  = indices.size();

		GenerateMesh(vertices.data(), indices.data());
	}

	Mesh::Mesh(const Mesh& other) :
		numberofVertices(other.numberofVertices),
		numberofIndices(other.numberofIndices),
		textures(other.textures),
		vao(other.vao),
		vbo(other.vbo),
		ebo(other.ebo) {}

	void Mesh::GenerateMesh(const float* vertices, const unsigned int* indices)
	{
		unsigned int newVAO;

		glGenVertexArrays(1, &newVAO);

		if (newVAO == 0)
		{
			ERR("Failed to generate Vertex Array Object. Check if OpenGL context is bound.");
			return;
		}

		glBindVertexArray(newVAO);

		if (numberofIndices > 0)
		{
			glGenBuffers(1, &ebo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberofIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		}

		glGenBuffers(1, &vbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, numberofVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Position)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, TexCoord)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		vao = std::shared_ptr<unsigned int>(new unsigned int(newVAO), [&](unsigned int*)
		{
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ebo);
			glDeleteVertexArrays(1, &(*vao));
		});

		INFO("Successful to generate mesh. (VAO: {0})", *vao);
	}
}
