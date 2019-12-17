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

			shader.SetProjectionViewMatrix(glm::value_ptr(scene->mainCamera->ProjectionViewMatrix()));
			shader.SetModelMatrix(gameObject->GetTransform()->DataPointer());

			// temprorary optimization
			if (dynamic_cast<Light*>(gameObject) != nullptr)
			{
				meshRenderer->Render();
				continue;
			}

			shader.SetMaterialColor(meshRenderer->GetMaterial().Color());
			shader.SetMaterialAmbient(meshRenderer->GetMaterial().Ambient());
			shader.SetMaterialDiffuse(meshRenderer->GetMaterial().Diffuse());
			shader.SetMaterialSpecular(meshRenderer->GetMaterial().Specular());
			shader.SetMaterialShininess(meshRenderer->GetMaterial().Shininess());

			shader.SetCameraPosition(scene->mainCamera->GetTransform()->Position());

			shader.SetNumberofLights((int)scene->lightList.size());

			for (int i = 0; i < scene->lightList.size(); i++)
			{
				std::string index = std::to_string(i);

				switch (scene->lightList[i]->Type())
				{
				case LightType::PointLight:
					shader.SetLightType(i, (int)LightType::PointLight);

					shader.SetLightColor(i, scene->lightList[i]->Color());
					shader.SetLightPosition(i, scene->lightList[i]->GetTransform()->Position());

					shader.SetLightConstant(i, 1.0f);
					shader.SetLightLinear(i, 0.09f);
					shader.SetLightQuadratic(i, 0.032f);

					break;

				case LightType::DirectionalLight:
					shader.SetLightType(i, (int)LightType::DirectionalLight);

					shader.SetLightColor(i, scene->lightList[i]->Color());
					shader.SetLightPosition(i, scene->lightList[i]->GetTransform()->Position());

					break;

				case LightType::SpotLight:
					shader.SetLightType(i, (int)LightType::SpotLight);

					shader.SetLightCutoffAngle(i, glm::cos(glm::radians(12.5f)));
					shader.SetLightOuterCutoffAngle(i, glm::cos(glm::radians(20.0f)));

					shader.SetLightConstant(i, 1.0f);
					shader.SetLightLinear(i, 0.09f);
					shader.SetLightQuadratic(i, 0.032f);

					shader.SetLightColor(i, scene->lightList[i]->Color());
					shader.SetLightPosition(i, scene->lightList[i]->GetTransform()->Position());

					break;
				}
			}

			meshRenderer->Render();
		}
	}
}

