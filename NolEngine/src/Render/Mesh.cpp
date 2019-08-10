#include "PCH.h"
#include "Mesh.h"

namespace Nol
{
	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<Texture> textures) : textures(textures)
	{
		numberOfVertices = vertices.size();
		numberOfIndices  = 0;

		GenerateMesh((const float*)vertices.data(), nullptr);
	}

	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<Texture> textures) : textures(textures)
	{
		numberOfVertices = vertices.size() / (sizeof(Vertex) / sizeof(float));
		numberOfIndices  = 0;

		GenerateMesh(vertices.data(), nullptr);
	}

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture> textures) : textures(textures)
	{
		numberOfVertices = vertices.size();
		numberOfIndices  = indices.size();

		GenerateMesh((const float*)vertices.data(), indices.data());
	}

	Mesh::Mesh(const std::vector<float>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture> textures) : textures(textures)
	{
		numberOfVertices = vertices.size() / (sizeof(Vertex) / sizeof(float));
		numberOfIndices  = indices.size();

		GenerateMesh(vertices.data(), indices.data());
	}

	Mesh::Mesh(const Mesh& other) :
		numberOfVertices(other.numberOfVertices),
		numberOfIndices(other.numberOfIndices),
		textures(other.textures),
		VAO(other.VAO),
		VBO(other.VBO),
		EBO(other.EBO) {}

	void Mesh::GenerateMesh(const float* vertices, const unsigned int* indices)
	{
		unsigned int vao;

		glGenVertexArrays(1, &vao);

		if (vao == 0)
		{
			ERR("Failed to generate Vertex Array Object. Check if OpenGL context is bound.");
			return;
		}

		glBindVertexArray(vao);

		if (numberOfIndices > 0)
		{
			glGenBuffers(1, &EBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, numberOfIndices * sizeof(unsigned int), indices, GL_STATIC_DRAW);
		}

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, numberOfVertices * sizeof(Vertex), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Position)));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, Normal)));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(offsetof(Vertex, TexCoord)));

		glBindVertexArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		VAO = std::shared_ptr<unsigned int>(new unsigned int(vao), [&](unsigned int*)
		{
			glDeleteBuffers(1, &VBO);
			glDeleteBuffers(1, &EBO);
			glDeleteVertexArrays(1, &(*VAO));
		});

		INFO("Successful to generate mesh. (VAO: {0})", *VAO);
	}
}
