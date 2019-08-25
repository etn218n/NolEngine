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

			if (meshRenderer == nullptr)
				continue;

			const Shader& shader = meshRenderer->GetShader();

			shader.Use();

			shader.SetUniformVec4Ptr("uViewProjection", glm::value_ptr(scene->mainCamera->ProjectionViewMatrix()));
			shader.SetUniformVec4Ptr("uModel", gameObject->GetTransform()->DataPointer());

			// temprorary optimization
			if (dynamic_cast<Light*>(gameObject) != nullptr)
			{
				meshRenderer->Render();
				continue;
			}

			shader.SetUniformVec3("uMaterial.ambient", meshRenderer->GetMaterial().Ambient());
			shader.SetUniformVec3("uMaterial.diffuse", meshRenderer->GetMaterial().Diffuse());
			shader.SetUniformVec3("uMaterial.specular", meshRenderer->GetMaterial().Specular());
			shader.SetUniformFloat("uMaterial.shininess", meshRenderer->GetMaterial().Shininess());

			shader.SetUniformVec3("uCameraPosition", scene->mainCamera->GetTransform()->Position());

			shader.SetUniformInt("uNumberofLights", scene->lightList.size());

			for (int i = 0; i < scene->lightList.size(); i++)
			{
				std::string index = std::to_string(i);

				switch (scene->lightList[i]->Type())
				{
				case LightType::PointLight:
					shader.SetUniformInt("uLight["+index+"].type", (int)LightType::PointLight);

					shader.SetUniformVec3("uLight["+index+"].color", scene->lightList[i]->Color());
					shader.SetUniformVec3("uLight["+index+"].position", scene->lightList[i]->GetTransform()->Position());

					shader.SetUniformFloat("uLight["+index+"].constant", 1.0f);
					shader.SetUniformFloat("uLight["+index+"].linear", 0.09f);
					shader.SetUniformFloat("uLight["+index+"].quadratic", 0.032f);
					break;

				case LightType::DirectionalLight:
					shader.SetUniformInt("uLight["+index+"].type", (int)LightType::DirectionalLight);

					shader.SetUniformVec3("uLight["+index+"].color", scene->lightList[i]->Color());
					shader.SetUniformVec3("uLight["+index+"].direction", scene->lightList[i]->GetTransform()->Front());
					break;

				case LightType::SpotLight:
					shader.SetUniformInt("uLight["+index+"].type", (int)LightType::SpotLight);

					shader.SetUniformVec3("uLight["+index+"].color", scene->lightList[i]->Color());
					shader.SetUniformVec3("uLight["+index+"].direction", scene->lightList[i]->GetTransform()->Front());
					shader.SetUniformFloat("uLight["+index+"].cutoff", glm::cos(glm::radians(12.5f)));
					shader.SetUniformFloat("uLight["+index+"].outercutoff", glm::cos(glm::radians(20.0f)));

					shader.SetUniformFloat("uLight["+index+"].constant", 1.0f);
					shader.SetUniformFloat("uLight["+index+"].linear", 0.09f);
					shader.SetUniformFloat("uLight["+index+"].quadratic", 0.032f);
					break;
				}
			}

			meshRenderer->Render();
		}
	}
}

