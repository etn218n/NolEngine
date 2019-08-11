#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component/GameObject.h"

namespace Nol
{
	class Camera : public GameObject
	{
	private:
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 projectionViewMatrix;

	public:
		NOL_API Camera(const std::string& name = "None");
		NOL_API virtual ~Camera() = default;

		NOL_API void SetPerspectiveView(float fov, float aspectRatio, float nearPlane, float farPlane);
		NOL_API void SetOrthogonalView(float left, float right, float top, float bottom, float nearPlane, float farPlane);

		NOL_API inline const glm::mat4& GetViewMatrix()				{ return viewMatrix;		   }
		NOL_API inline const glm::mat4& GetProjectionMatrix() const { return projectionMatrix;	   }
		NOL_API inline const glm::mat4& GetProjectionViewMatrix()   { return projectionViewMatrix; }

	private:
		void CalculateMatrices(const glm::mat4& transform);
	};
}

