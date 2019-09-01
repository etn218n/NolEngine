#include "PCH.h"
#include "Model.h"

namespace Nol
{
	GameObject* Model::GenerateModel(const std::string& filePath, Shader& shader)
	{
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ERR("ASSIMP::{0}", import.GetErrorString());
			return nullptr;
		}
		INFO("Successful to load model file. (Path: \"{0}\")", filePath);

		return ProcessNode(scene->mRootNode, scene, nullptr, shader);
	}

	GameObject* Model::ProcessNode(aiNode* node, const aiScene* scene, GameObject* parent, Shader& shader)
	{
		GameObject* gameobject = new GameObject();

		for (unsigned int i = 0; i < node->mNumMeshes; i++)
		{
			gameobject = new GameObject();

			gameobject->SetParent(parent);

			aiMesh *aiMesh = scene->mMeshes[node->mMeshes[i]];
			Mesh mesh = ProcessAiMesh(aiMesh, scene);

			MeshRenderer meshRenderer(mesh, shader);

			gameobject->AddComponent<MeshRenderer>(meshRenderer);
		}

		// then do the same for each of its children
		for (unsigned int i = 0; i < node->mNumChildren; i++)
		{
			ProcessNode(node->mChildren[i], scene, gameobject, shader);
		}

		return gameobject;
	}

	Mesh Model::ProcessAiMesh(aiMesh *aiMesh, const aiScene* scene)
	{
		std::vector<Vertex> vertices;
		std::vector<unsigned int> indices;
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < aiMesh->mNumVertices; i++)
		{
			Vertex vertex;
			
			glm::vec3 position;
			position.x = aiMesh->mVertices[i].x;
			position.y = aiMesh->mVertices[i].y;
			position.z = aiMesh->mVertices[i].z;
			vertex.Position = position;

			glm::vec3 normal;
			normal.x = aiMesh->mNormals[i].x;
			normal.y = aiMesh->mNormals[i].y;
			normal.z = aiMesh->mNormals[i].z;
			vertex.Normal = normal;
				
			if (aiMesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 texCoord;
				texCoord.x = aiMesh->mTextureCoords[0][i].x;
				texCoord.y = aiMesh->mTextureCoords[0][i].y;
				vertex.TexCoord = texCoord;
			}

			vertices.push_back(vertex);
		}

		for (unsigned int i = 0; i < aiMesh->mNumFaces; i++)
		{
			aiFace face = aiMesh->mFaces[i];

			for (unsigned int j = 0; j < face.mNumIndices; j++)
				indices.push_back(face.mIndices[j]);
		}

		/*if (aiMesh->mMaterialIndex >= 0)
		{
			aiMaterial *material = scene->mMaterials[aiMesh->mMaterialIndex];
			std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE);
			textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
			std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR);

			textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		}*/

		aiMaterial* material = scene->mMaterials[aiMesh->mMaterialIndex];
		// we assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// diffuse: texture_diffuseN
		// specular: texture_specularN
		// normal: texture_normalN

		
		// 1. diffuse maps
		std::vector<Texture> diffuseMaps = LoadMaterialTextures(scene, material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		// 2. specular maps
		std::vector<Texture> specularMaps = LoadMaterialTextures(scene, material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
		// 3. normal maps
		std::vector<Texture> normalMaps = LoadMaterialTextures(scene, material, aiTextureType_HEIGHT);
		textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
		// 4. height maps
		std::vector<Texture> heightMaps = LoadMaterialTextures(scene, material, aiTextureType_AMBIENT);
		textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

		return Mesh(vertices, indices, textures);
	}

	std::vector<Texture> Model::LoadMaterialTextures(const aiScene* scene, aiMaterial* material, aiTextureType type)
	{
		std::vector<Texture> textures;

		for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
		{
			aiString str;
			material->GetTexture(type, i, &str);

			/*std::string fileName = str.C_Str();
			std::string filePath = "./resource/models/" + fileName;

			aiTexture* a = scene->mTextures[0];*/

			Texture texture(TextureType::Texture2D, (unsigned char*)scene->mTextures[1]->pcData);

			INFO("{0}", atoi(str.C_Str()));
			
			textures.push_back(texture);
		}

		return textures;
	}
}
