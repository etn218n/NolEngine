#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component/Camera.h"
#include "Component/GameObject.h"
#include "Component/MeshRenderer.h"

namespace Nol
{
	class Scene
	{
	private:
		//std::multimap<unsigned int, GameObject*> renderMap;
		std::vector<std::pair<GameObject*, MeshRenderer*>> renderList;
		std::string name;

		Camera* camera;

	public:
		NOL_API Scene(const std::string& name, Camera* camera);
		NOL_API Scene(const Scene& other) = delete;
		NOL_API virtual ~Scene() = default;

		NOL_API void SetCamera(Camera* camera);
		NOL_API void AddGameObject(GameObject* gameObject);

		NOL_API inline const int NumberOfRenderTarget() const { return renderList.size(); }

		NOL_API void Render();
	};
}

