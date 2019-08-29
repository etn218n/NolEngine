#include "PCH.h"
#include "Camera.h"

#include <glad/glad.h>

namespace Nol
{
	Camera::Camera(const std::string & name) : GameObject(name)
	{
		viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		viewMatrix = glm::inverse(transform->GlobalModelMatrix());

		// default projection of camera
		SetPerspectiveView(45.0f, 4.0f / 3.0f, 0.1f, 100.0f);

		projectionViewMatrix = projectionMatrix * viewMatrix;

		// update ViewMatrix everytimes its transform changed
		transform->OnTransformed.Subcribe([this](const glm::mat4& transform)
		{
			viewMatrix = glm::inverse(transform);

			projectionViewMatrix = projectionMatrix * viewMatrix;
		});

		SetDefaultMasks();

		clearColorFn = [this]() 
		{
			glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
			glClear(clearflagMask);
		};

		clearSkyboxFn = [this]()
		{
			glClear(clearflagMask);

			glDepthMask(GL_FALSE);

			const Shader& shader = skybox.GetSkyboxRenderer()->GetShader();

			shader.Use();

			glm::mat4 projectionView = projectionMatrix * glm::mat4(glm::mat3(viewMatrix));

			shader.SetUniformVec4Ptr(shader.uniform.ProjectionView, glm::value_ptr(projectionView));

			skybox.Render();

			glDepthMask(GL_TRUE);
		};

		clearFnSelector = clearSkyboxFn;
	}

	void Camera::SetPerspectiveView(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	}

	void Camera::SetOrthogonalView(float left, float right, float top, float bottom, float nearPlane, float farPlane)
	{
		projectionMatrix = glm::ortho<float>(left, right, top, bottom, nearPlane, farPlane);
	}

	void Camera::SetDefaultMasks()
	{
		clearflagMask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;

		flags.push_back(GL_DEPTH_TEST);
		flags.push_back(GL_CULL_FACE);
		
		EnableFlags();

		glCullFace(GL_BACK);
	}

	void Camera::SetClearType(ClearType clearType)
	{
		switch (clearType)
		{
			case ClearType::SolidColor: clearFnSelector = clearColorFn;  break;
			case ClearType::Skybox:     clearFnSelector = clearSkyboxFn; break;
		}
	}

	void Camera::EnableFlags()
	{
		for (const auto flag : flags)
			glEnable(flag);
	}

	void Camera::ClearFlags()
	{
		for (int i = flags.size() - 1; i <= 0; i--)
		{
			glDisable(flags[i]);
			flags.pop_back();
		}
	}
}
