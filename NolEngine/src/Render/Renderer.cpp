#include "PCH.h"
#include "Renderer.h"

namespace Nol
{
	Renderer::Renderer(std::shared_ptr<Scene> scene) : scene(scene)
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

			shader.SetUniformVec4Ptr("uViewProjection", glm::value_ptr(scene->camera->GetProjectionViewMatrix()));
			shader.SetUniformVec4Ptr("uModel", gameObject->GetTransform()->GetDataPointer());

			shader.SetUniformVec3("uMaterial.ambient", meshRenderer->GetMaterial().Ambient());
			shader.SetUniformVec3("uMaterial.diffuse", meshRenderer->GetMaterial().Diffuse());
			shader.SetUniformVec3("uMaterial.specular", meshRenderer->GetMaterial().Specular());
			shader.SetUniformFloat("uMaterial.shininess", meshRenderer->GetMaterial().Shininess());

			shader.SetUniformVec3("uCameraPosition", scene->camera->GetTransform()->GetPosition());

			switch (scene->light->Type())
			{
			case LightType::PointLight:
				shader.SetUniformInt("uLight.type", (int)LightType::PointLight);

				shader.SetUniformVec3("uLight.color", scene->light->Color());
				shader.SetUniformVec3("uLight.position", scene->light->GetTransform()->GetPosition());

				shader.SetUniformFloat("uLight.constant", 1.0f);
				shader.SetUniformFloat("uLight.linear", 0.09f);
				shader.SetUniformFloat("uLight.quadratic", 0.032f);
				break;

			case LightType::DirectionalLight:
				shader.SetUniformInt("uLight.type", (int)LightType::DirectionalLight);

				shader.SetUniformVec3("uLight.color", scene->light->Color());
				shader.SetUniformVec3("uLight.direction", scene->light->GetTransform()->GetFront());
				break;

			case LightType::SpotLight:
				shader.SetUniformInt("uLight.type", (int)LightType::SpotLight);

				shader.SetUniformVec3("uLight.color", scene->light->Color());
				shader.SetUniformVec3("uLight.direction", scene->light->GetTransform()->GetFront());
				shader.SetUniformFloat("uLight.cutoff", glm::cos(glm::radians(12.5f)));
				shader.SetUniformFloat("uLight.outercutoff", glm::cos(glm::radians(20.0f)));

				shader.SetUniformFloat("uLight.constant", 1.0f);
				shader.SetUniformFloat("uLight.linear", 0.09f);
				shader.SetUniformFloat("uLight.quadratic", 0.032f);
				break;
			}


			meshRenderer->Render();
		}
	}
}

