#include "PCH.h"
#include "Renderer.h"

namespace Nol
{
	Renderer::Renderer(std::shared_ptr<Scene>  scene) : scene(scene)
	{
	}

	void Renderer::SetScene(std::shared_ptr<Scene> scene)
	{
		if (scene == nullptr)
		{
			WARN("Scene is NULL.");
			return;
		}

		this->scene = scene;
	}

	void Renderer::Update()
	{
		for (const auto& gameObject : scene->gameobjectList)
		{
			MeshRenderer* meshRenderer = gameObject->GetComponent<MeshRenderer>();

			const Shader& shader = meshRenderer->GetShader();

			shader.Use();

			shader.SetUniform4fv("uViewProjection", glm::value_ptr(scene->camera->GetProjectionViewMatrix()));

			shader.SetUniform4fv("uModel", gameObject->GetTransform()->GetDataPointer());

			shader.SetUniform4f("uLightColor", scene->light->Color());

			meshRenderer->Render();
		}
	}
}

