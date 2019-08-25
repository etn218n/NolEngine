#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component/Light.h"
#include "Component/Camera.h"
#include "Component/GameObject.h"
#include "Component/MeshRenderer.h"

namespace Nol
{
	class Scene
	{
	friend class Renderer;

	private:
		std::vector<GameObject*> gameobjectList;
		std::vector<Light*> lightList;
		std::string name;
		Camera* mainCamera;

	public:
		NOL_API Scene(const std::string& name);
		NOL_API Scene(const Scene& other) = delete;
		NOL_API virtual ~Scene() = default;

		NOL_API void SetMainCamera(Camera* camera);
		NOL_API void AddGameObject(GameObject* gameObject);
		NOL_API void RemoveGameObject(GameObject* gameObject);

		NOL_API inline const int NumberofGameObjects() const { return gameobjectList.size(); }
	};
}

