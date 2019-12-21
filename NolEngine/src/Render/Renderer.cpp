#include "PCH.h"
#include "Renderer.h"

namespace Nol
{
	std::shared_ptr<Scene> Renderer::activeScene = nullptr;
	UniformBuffer* Renderer::cameraBuffer = nullptr;

	/*Renderer::Renderer()
	{
		cameraBuffer = new UniformBuffer(sizeof(glm::mat4));
	}

	Renderer::Renderer(std::shared_ptr<Scene> activeScene) : Renderer()
	{
		SetScene(activeScene);
	}*/

	void Renderer::Init()
	{
		cameraBuffer = new UniformBuffer(sizeof(glm::mat4));
	}

	void Renderer::SetScene(std::shared_ptr<Scene> scene)
	{
		if (scene == nullptr)
		{
			WARN("Scene is NULL.");
			return;
		}

		activeScene = scene;

		//cameraBuffer->UpdateData(sizeof(glm::mat4), glm::value_ptr(activeScene->mainCamera->ProjectionViewMatrix()));
		cameraBuffer->BindToSlot(0);
	}

	void Renderer::Update()
	{
		activeScene->mainCamera->Clear();
		//cameraBuffer->UpdateData(sizeof(glm::mat4), glm::value_ptr(activeScene->mainCamera->ProjectionViewMatrix()));

		for (const auto& gameObject : activeScene->gameobjectList)
		{
			MeshRenderer* meshRenderer = gameObject->GetComponent<MeshRenderer>();

			if (meshRenderer == nullptr)
				continue;

			const Shader& shader = meshRenderer->GetShader();

			shader.Use();

			shader.SetProjectionViewMatrix(glm::value_ptr(activeScene->mainCamera->ProjectionViewMatrix()));
			shader.SetModelMatrix(gameObject->GetTransform()->DataPointer());

			// temprorary optimization
			if (dynamic_cast<Light*>(gameObject) != nullptr)
			{
				meshRenderer->Render();
				continue;
			}

			shader.SetMaterialColor(meshRenderer->GetMaterial().Color);
			shader.SetMaterialAmbient(meshRenderer->GetMaterial().Ambient);
			shader.SetMaterialDiffuse(meshRenderer->GetMaterial().Diffuse);
			shader.SetMaterialSpecular(meshRenderer->GetMaterial().Specular);
			shader.SetMaterialShininess(meshRenderer->GetMaterial().Shininess);

			shader.SetCameraPosition(activeScene->mainCamera->GetTransform()->Position());

			shader.SetNumberofLights((int)activeScene->lightList.size());

			for (int i = 0; i < activeScene->lightList.size(); i++)
			{
				std::string index = std::to_string(i);

				switch (activeScene->lightList[i]->Type())
				{
				case LightType::PointLight:
					shader.SetLightType(i, (int)LightType::PointLight);

					shader.SetLightColor(i, activeScene->lightList[i]->Color());
					shader.SetLightPosition(i, activeScene->lightList[i]->GetTransform()->Position());

					shader.SetLightConstant(i, 1.0f);
					shader.SetLightLinear(i, 0.09f);
					shader.SetLightQuadratic(i, 0.032f);

					break;

				case LightType::DirectionalLight:
					shader.SetLightType(i, (int)LightType::DirectionalLight);

					shader.SetLightColor(i, activeScene->lightList[i]->Color());
					shader.SetLightPosition(i, activeScene->lightList[i]->GetTransform()->Position());

					break;

				case LightType::SpotLight:
					shader.SetLightType(i, (int)LightType::SpotLight);

					shader.SetLightCutoffAngle(i, glm::cos(glm::radians(12.5f)));
					shader.SetLightOuterCutoffAngle(i, glm::cos(glm::radians(20.0f)));

					shader.SetLightConstant(i, 1.0f);
					shader.SetLightLinear(i, 0.09f);
					shader.SetLightQuadratic(i, 0.032f);

					shader.SetLightColor(i, activeScene->lightList[i]->Color());
					shader.SetLightPosition(i, activeScene->lightList[i]->GetTransform()->Position());

					break;
				}
			}

			meshRenderer->Render();
		}
	}
}

