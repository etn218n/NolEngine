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

			shader.SetUniform3f("uLight.ambient", scene->light->Ambient());
			shader.SetUniform3f("uLight.diffuse", scene->light->Diffuse());
			shader.SetUniform3f("uLight.specular", scene->light->Specular());
			shader.SetUniform3f("uLight.position", scene->light->GetTransform()->GetPosition());

			shader.SetUniform3f("uMaterial.ambient", glm::vec3(1.0f));
			shader.SetUniform3f("uMaterial.diffuse", glm::vec3(1.0f));
			shader.SetUniform3f("uMaterial.specular", glm::vec3(1.0f));
			shader.SetUniform1f("uMaterial.shininess", 32.0f);

			shader.SetUniform3f("uCameraPosition", scene->camera->GetTransform()->GetPosition());

			meshRenderer->Render();
		}
	}
}

