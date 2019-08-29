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
	private:
		std::vector<Texture> textures;
		unsigned int numberofVertices;
		unsigned int numberofIndices;
		std::shared_ptr<unsigned int> vao;
		unsigned int vbo;
		unsigned int ebo;

	public:
		NOL_API Mesh(const std::vector<Vertex>& vertices, bool isPositionOnly = false);
		NOL_API Mesh(const std::vector<float>& vertices,  bool isPositionOnly = false);
		NOL_API Mesh(const std::vector<Vertex>& vertices, const std::vector<Texture> textures, bool isPositionOnly = false);
		NOL_API Mesh(const std::vector<float>& vertices,  const std::vector<Texture> textures, bool isPositionOnly = false);
		NOL_API Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
		NOL_API Mesh(const std::vector<float>& vertices,  const std::vector<unsigned int>& indices);
		NOL_API Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture> textures);
		NOL_API Mesh(const std::vector<float>& vertices,  const std::vector<unsigned int>& indices, const std::vector<Texture> textures);
		NOL_API Mesh(const Mesh& other);
		NOL_API virtual ~Mesh() = default;

		NOL_API inline unsigned int VAO() const { return *vao; }
		NOL_API inline unsigned int VBO() const { return  vbo; }
		NOL_API inline unsigned int EBO() const { return  ebo; }

		NOL_API inline const std::vector<Texture>& TextureList() const { return textures; }

		NOL_API inline unsigned int NumberofVertices() const { return numberofVertices; }
		NOL_API inline unsigned int NumberofIndices()  const { return numberofIndices;  }
		NOL_API inline unsigned int NumberofTextures() const { return textures.size();  }

	private:
		void GenerateMesh(const float* vertices, const unsigned int* indices, bool isPositionOnly);
	};
}

