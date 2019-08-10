#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Render/Texture.h"

#include <glad/glad.h>

namespace Nol
{
	typedef struct vertex
	{
		glm::vec3 Position = glm::vec3(0.0f);
		glm::vec3 Normal   = glm::vec3(0.0f);
		glm::vec2 TexCoord = glm::vec2(0.0f);
	} Vertex;

	class Mesh
	{
	friend class MeshRenderer;

	private:
		std::vector<Texture> textures;
		unsigned int numberOfVertices;
		unsigned int numberOfIndices;

		std::shared_ptr<unsigned int> VAO;
		unsigned int VBO;
		unsigned int EBO;

	public:
		NOL_API Mesh(const std::vector<Vertex>& vertices, const std::vector<Texture> textures);
		NOL_API Mesh(const std::vector<float>& vertices,  const std::vector<Texture> textures);
		NOL_API Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture> textures);
		NOL_API Mesh(const std::vector<float>& vertices,  const std::vector<unsigned int>& indices, const std::vector<Texture> textures);
		NOL_API Mesh(const Mesh& other);
		NOL_API virtual ~Mesh() = default;

		NOL_API inline const unsigned int GetVAO() const { return *VAO; }
		NOL_API inline const unsigned int GetVBO() const { return  VBO; }
		NOL_API inline const unsigned int GetEBO() const { return  EBO; }

		NOL_API inline const unsigned int NumberOfVertices() const { return numberOfVertices; }
		NOL_API inline const unsigned int NumberOfIndices()  const { return numberOfIndices;  }
		NOL_API inline const unsigned int NumberOfTextures() const { return textures.size();  }

	private:
		void GenerateMesh(const float* vertices, const unsigned int* indices);
	};
}

