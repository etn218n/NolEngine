#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "GameObject.h"
#include "MeshRenderer.h"

#include "Render/Mesh.h"
#include "Render/Shader.h"
#include "Render/Texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace Nol
{
	class Model
	{
	public:
		NOL_API Model() = delete;
		NOL_API virtual ~Model() = default;

		NOL_API static GameObject* GenerateModel(const std::string& filePath, Shader& shader);

	private:
		static GameObject* ProcessNode(aiNode *node, const aiScene *scene, GameObject* parent, Shader& shader);
		static Mesh ProcessAiMesh(aiMesh *aiMesh, const aiScene *scene);
		static std::vector<Texture> LoadMaterialTextures(const aiScene* scene, aiMaterial *material, aiTextureType type);
	};
}

