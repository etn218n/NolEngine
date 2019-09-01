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

	void Scene::AddGameObject(GameObject* addedGameObject)
	{
		for (const auto& gameobject : gameobjectList)
		{
			if (gameobject->ID() == addedGameObject->ID())
			{
				WARN("GameObject is already contained in this scene.");
				return;
			}
		}

		Light* addedLight = dynamic_cast<Light*>(addedGameObject);

		if (addedLight != nullptr)
			lightList.push_back(static_cast<Light*>(addedGameObject));

		gameobjectList.push_back(addedGameObject);

		for (auto const& child : addedGameObject->ChildList())
			AddGameObject(child);
	}

	void Scene::RemoveGameObject(GameObject* removedGameObject)
	{
		Light* removedLight = dynamic_cast<Light*>(removedGameObject);

		if (removedLight != nullptr)
		{
			lightList.erase(
				std::remove_if(lightList.begin(), lightList.end(),
					[removedGameObject](const Light* light)
					{
						return (light->ID() == removedGameObject->ID());
					}),
					lightList.end());
		}

		// Revisit this later
		gameobjectList.erase(
			std::remove_if(gameobjectList.begin(), gameobjectList.end(),
				[removedGameObject](const GameObject* gameobject)
				{ 
					return (gameobject->ID() == removedGameObject->ID());
				}),
			gameobjectList.end());

		for (auto const& child : removedGameObject->ChildList())
			RemoveGameObject(child);
	}

	bool Scene::Contain(GameObject* searchedGameObject)
	{
		for (const auto& gameobject : gameobjectList)
		{
			if (gameobject->ID() == searchedGameObject->ID())
				return true;
		}

		Light* searchedLight = dynamic_cast<Light*>(searchedGameObject);

		if (searchedLight != nullptr)
		{
			for (const auto& light : lightList)
			{
				if (searchedLight->ID() == light->ID())
					return true;
			}
		}

		return false;
	}
}
