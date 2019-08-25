#include "PCH.h"
#include "Camera.h"

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
	}

	void Camera::SetPerspectiveView(float fov, float aspectRatio, float nearPlane, float farPlane)
	{
		projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	}

	void Camera::SetOrthogonalView(float left, float right, float top, float bottom, float nearPlane, float farPlane)
	{
		projectionMatrix = glm::ortho<float>(left, right, top, bottom, nearPlane, farPlane);
	}
}
