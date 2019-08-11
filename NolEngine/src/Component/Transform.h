#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Event/Observable.h"

#include "Component/Component.h"

namespace Nol
{
	class Transform : public Component
	{
	public:
		Observable<const glm::mat4&> OnTransformed;

	private:
		glm::mat4 modelMatrix;

	public:
		NOL_API Transform();
		NOL_API virtual ~Transform() = default;

		NOL_API void Translate(const glm::vec3& v);
		NOL_API void Scale(const glm::vec3& v);
		NOL_API void Rotate(const float angle, const glm::vec3& axis);
		NOL_API const glm::vec3 GetPosition() const;

		NOL_API void SetPosition(glm::vec3 position);

		NOL_API inline const glm::mat4& GetModelMatrix() const { return modelMatrix; }
		NOL_API inline const float* GetDataPointer() { return glm::value_ptr(modelMatrix); };
	};
}

