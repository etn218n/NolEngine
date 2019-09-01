#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "GameObject.h"
#include "Skybox.h"

namespace Nol
{
	enum class ClearType
	{
		SolidColor,
		DepthOnly,
		Skybox
	};

	class Camera : public GameObject
	{
	public:
		glm::vec4 ClearColor;

	private:
		glm::mat4 viewMatrix;
		glm::mat4 projectionMatrix;
		glm::mat4 projectionViewMatrix;

		Skybox skybox;

		int clearflagMask;

		std::vector<int> flags;

		std::function<void()> clearFnSelector;
		std::function<void()> clearColorFn;
		std::function<void()> clearSkyboxFn;

	public:
		NOL_API Camera(const std::string& name = "None");
		NOL_API virtual ~Camera() = default;

		NOL_API void SetPerspectiveView(float fov, float aspectRatio, float nearPlane, float farPlane);
		NOL_API void SetOrthogonalView(float left, float right, float top, float bottom, float nearPlane, float farPlane);

		NOL_API inline const glm::mat4& ViewMatrix() const { return viewMatrix; }
		NOL_API inline const glm::mat4& ProjectionMatrix() const { return projectionMatrix; }
		NOL_API inline const glm::mat4& ProjectionViewMatrix() const { return projectionViewMatrix; }

		NOL_API void SetClearType(ClearType clearType);
		NOL_API void EnableFlags();
		NOL_API void ClearFlags();
		NOL_API inline void Clear() const { clearFnSelector(); }

	private:
		void SetDefaultMasks();
	};
}

