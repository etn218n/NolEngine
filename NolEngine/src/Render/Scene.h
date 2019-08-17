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
		std::vector<std::shared_ptr<GameObject>> gameobjectList;
		std::string name;

		std::shared_ptr<Camera> camera;
		std::shared_ptr<Light>  light;

	public:
		NOL_API Scene(const std::string& name);
		NOL_API Scene(const Scene& other) = delete;
		NOL_API virtual ~Scene() = default;

		NOL_API void SetCamera(std::shared_ptr<Camera> camera);
		NOL_API void SetLight(std::shared_ptr<Light> light);
		NOL_API void AddGameObject(std::shared_ptr<GameObject> gameObject);
		NOL_API void RemoveGameObject(std::shared_ptr<GameObject> gameObject);

		NOL_API inline const int NumberOfGameObject() const { return gameobjectList.size(); }
	};
}

