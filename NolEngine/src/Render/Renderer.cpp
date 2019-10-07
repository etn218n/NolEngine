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
		scene->mainCamera->Clear();

		for (const auto& gameObject : scene->gameobjectList)
		{
			MeshRenderer* meshRenderer = gameObject->GetComponent<MeshRenderer>();

			if (meshRenderer == nullptr)
				continue;

			const Shader& shader = meshRenderer->GetShader();

			shader.Use();

			shader.SetUniformVec4Ptr(shader.uniform.ProjectionView, glm::value_ptr(scene->mainCamera->ProjectionViewMatrix()));
			shader.SetUniformVec4Ptr(shader.uniform.Model, gameObject->GetTransform()->DataPointer());

			// temprorary optimization
			if (dynamic_cast<Light*>(gameObject) != nullptr)
			{
				meshRenderer->Render();
				continue;
			}

			shader.SetUniformVec3(shader.uniform.Material.Ambient, meshRenderer->GetMaterial().Ambient());
			shader.SetUniformVec3(shader.uniform.Material.Diffuse, meshRenderer->GetMaterial().Diffuse());
			shader.SetUniformVec3(shader.uniform.Material.Specular, meshRenderer->GetMaterial().Specular());
			shader.SetUniformFloat(shader.uniform.Material.Shininess, meshRenderer->GetMaterial().Shininess());

			shader.SetUniformVec3(shader.uniform.CameraPosition, scene->mainCamera->GetTransform()->Position());

			shader.SetUniformInt(shader.uniform.NumberofLights, (int)scene->lightList.size());

			for (int i = 0; i < scene->lightList.size(); i++)
			{
				std::string index = std::to_string(i);

				switch (scene->lightList[i]->Type())
				{
				case LightType::PointLight:
					shader.SetUniformInt(shader.uniform.Lights[i].Type, (int)LightType::PointLight);

					shader.SetUniformVec3(shader.uniform.Lights[i].Color, scene->lightList[i]->Color());
					shader.SetUniformVec3(shader.uniform.Lights[i].Position, scene->lightList[i]->GetTransform()->Position());

					shader.SetUniformFloat(shader.uniform.Lights[i].Constant, 1.0f);
					shader.SetUniformFloat(shader.uniform.Lights[i].Linear, 0.09f);
					shader.SetUniformFloat(shader.uniform.Lights[i].Quadratic, 0.032f);
					break;

				case LightType::DirectionalLight:
					shader.SetUniformInt(shader.uniform.Lights[i].Type, (int)LightType::DirectionalLight);

					shader.SetUniformVec3(shader.uniform.Lights[i].Color, scene->lightList[i]->Color());
					shader.SetUniformVec3(shader.uniform.Lights[i].Direction, scene->lightList[i]->GetTransform()->Front());
					break;

				case LightType::SpotLight:
					shader.SetUniformInt(shader.uniform.Lights[i].Type, (int)LightType::SpotLight);

					shader.SetUniformVec3(shader.uniform.Lights[i].Color, scene->lightList[i]->Color());
					shader.SetUniformVec3(shader.uniform.Lights[i].Direction, scene->lightList[i]->GetTransform()->Front());

					shader.SetUniformFloat(shader.uniform.Lights[i].Cutoff, glm::cos(glm::radians(12.5f)));
					shader.SetUniformFloat(shader.uniform.Lights[i].OuterCutoff, glm::cos(glm::radians(20.0f)));

					shader.SetUniformFloat(shader.uniform.Lights[i].Constant, 1.0f);
					shader.SetUniformFloat(shader.uniform.Lights[i].Linear, 0.09f);
					shader.SetUniformFloat(shader.uniform.Lights[i].Quadratic, 0.032f);
					break;
				}
			}

			meshRenderer->Render();
		}
	}
}

