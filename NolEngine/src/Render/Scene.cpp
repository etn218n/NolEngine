#include "PCH.h"
#include "Scene.h"

namespace Nol
{
	Scene::Scene(const std::string& name) : name(name)
	{
		gameobjectList.reserve(100);

		/*Camera* defaultCamera = new Camera();
		defaultCamera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 4.0f));

		Light* defaultLight = new Light();
		defaultLight->GetTransform()->Translate(glm::vec3(1.0f, 1.0f, 0.0f));

		SetMainCamera(defaultCamera);
		AddGameObject(defaultLight);*/
	}

	void Scene::SetMainCamera(Camera* camera)
	{
		if (camera == nullptr)
		{
			WARN("Camera is NULL.");
			return;
		}

		mainCamera = camera;
	}

	void Scene::AddGameObject(GameObject* gameObject)
	{
		for (const auto& gameObj : gameobjectList)
		{
			if (gameObj->GetID() == gameObject->GetID())
			{
				WARN("GameObject is already contained in scene.");
				return;
			}
		}

		Light* light = dynamic_cast<Light*>(gameObject);

		if (light != nullptr)
		{
			lightList.push_back(static_cast<Light*>(gameObject));
			INFO("Light added.");
		}

		/*MeshRenderer* meshRenderer = gameObject->GetComponent<MeshRenderer>();

		if (meshRenderer == nullptr)
		{
			INFO("GameObject does not have MeshRenderer component.");
			return;
		}*/

		gameobjectList.push_back(gameObject);
	}

	void Scene::RemoveGameObject(GameObject* gameObject)
	{
		Light* light = dynamic_cast<Light*>(gameObject);

		if (light != nullptr)
		{
			lightList.erase(
				std::remove_if(lightList.begin(), lightList.end(),
					[gameObject](const Light* light)
					{
						return (light->GetID() == gameObject->GetID());
					}),
					lightList.end());
		}

		// Revisit this later
		gameobjectList.erase(
			std::remove_if(gameobjectList.begin(), gameobjectList.end(),
				[gameObject](const GameObject* gameObj)
				{ 
					return (gameObj->GetID() == gameObject->GetID()); 
				}),
			gameobjectList.end());
	}
}
