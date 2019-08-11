#include "PCH.h"
#include "Scene.h"

namespace Nol
{
	Scene::Scene(const std::string& name, Camera* camera) : name(name), camera(camera)
	{
		if (camera == nullptr)
			WARN("Camera is NULL.");

		renderList.reserve(100);
	}

	void Scene::SetCamera(Camera* camera)
	{
		if (camera == nullptr)
		{
			WARN("Camera is NULL.");
			return;
		}

		this->camera = camera;
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		MeshRenderer* meshRenderer = gameObject->GetComponent<MeshRenderer>();

		if (meshRenderer == nullptr)
		{
			INFO("GameObject does not have MeshRenderer component.");
			return;
		}

		renderList.push_back({ gameObject, meshRenderer });
	}

	void Scene::Render() 
	{
		for (const auto& entry : renderList)
		{
			MeshRenderer* meshRenderer = entry.second;

			Shader shader = meshRenderer->GetShader();
			Mesh mesh = meshRenderer->GetMesh();

			shader.Use();

			shader.SetUniform4fv("uModel", entry.first->GetTransform()->GetDataPointer());
			shader.SetUniform4fv("uViewProjection", glm::value_ptr(camera->GetProjectionViewMatrix()));

			for (unsigned int i = 0; i < mesh.NumberOfTextures(); i++)
			{
				shader.SetUniform1i("uTexture" + std::to_string(i), i);

				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, mesh.GetTextureList()[i].GetID());
			}

			glBindVertexArray(mesh.GetVAO());

			meshRenderer->Render();
		}
	}

	/*void Scene::AddGameObject(GameObject* gameObject)
	{
		MeshRenderer* meshRenderer = gameObject->GetComponent<MeshRenderer>();

		if (meshRenderer == nullptr)
		{
			INFO("GameObject does not have MeshRenderer component.");
			return;
		}

		unsigned int vaoID = meshRenderer->GetMesh().GetVAO();

		renderMap.insert({ vaoID, gameObject });
	}

	void Scene::Render()
	{
		typedef std::multimap<unsigned int, GameObject*>::iterator MapIterator;

		for (auto& entry : renderMap)
		{
			 Get iterator corresponds to each vaoID
			std::pair<MapIterator, MapIterator> listOfGameObject = renderMap.equal_range(entry.first);

			for (MapIterator it = listOfGameObject.first; it != listOfGameObject.second; it++)
			{

			}
		}
	}*/
}
