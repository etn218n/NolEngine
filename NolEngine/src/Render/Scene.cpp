#include "PCH.h"
#include "Scene.h"

namespace Nol
{
	Scene::Scene(const std::string& name) : name(name)
	{
		gameobjectList.reserve(100);

		std::shared_ptr<Camera> defaultCamera = std::make_shared<Camera>();
		defaultCamera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 4.0f));

		std::shared_ptr<Light> defaultLight = std::make_shared<Light>();
		defaultLight->GetTransform()->Translate(glm::vec3(1.0f, 1.0f, 0.0f));

		SetCamera(defaultCamera);
		SetLight(defaultLight);
	}

	void Scene::SetCamera(std::shared_ptr<Camera> camera)
	{
		if (camera == nullptr)
		{
			WARN("Camera is NULL.");
			return;
		}

		this->camera = camera;
	}

	void Scene::SetLight(std::shared_ptr<Light>light)
	{
		if (light == nullptr)
		{
			WARN("Light is NULL.");
			return;
		}

		this->light = light;
	}

	void Scene::AddGameObject(std::shared_ptr<GameObject> gameObject)
	{
		for (const auto& gameObj : gameobjectList)
		{
			if (gameObj->GetID() == gameObject->GetID())
			{
				WARN("GameObject is already contained in scene.");
				return;
			}
		}

		MeshRenderer* meshRenderer = gameObject->GetComponent<MeshRenderer>();

		if (meshRenderer == nullptr)
		{
			INFO("GameObject does not have MeshRenderer component.");
			return;
		}

		gameobjectList.push_back(gameObject);
	}

	void Scene::RemoveGameObject(std::shared_ptr<GameObject> gameObject)
	{
		// Revisit this later
		gameobjectList.erase(
			std::remove_if(gameobjectList.begin(), gameobjectList.end(),
				[gameObject](const std::shared_ptr<GameObject> gameObj)
				{ 
					return (gameObj->GetID() == gameObject->GetID()); 
				}),
			gameobjectList.end());
	}
}
