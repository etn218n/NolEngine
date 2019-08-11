#include "PCH.h"
#include "Transform.h"

namespace Nol
{
	Transform::Transform() : modelMatrix(glm::mat4(1.0f))
	{
	}

	void Transform::Scale(const glm::vec3 & v)
	{
		modelMatrix = glm::scale(modelMatrix, v);

		OnTransformed.Publish(modelMatrix);
	}

	void Transform::Translate(const glm::vec3& v)
	{
		modelMatrix = glm::translate(modelMatrix, v);

		OnTransformed.Publish(modelMatrix);
	}

	void Transform::Rotate(const float angle, const glm::vec3& axis)
	{
		modelMatrix = glm::rotate(modelMatrix, glm::radians(angle), axis);

		OnTransformed.Publish(modelMatrix);
	}

	const glm::vec3 Transform::GetPosition() const
	{
		return glm::vec3(modelMatrix[3].x, modelMatrix[3].y, modelMatrix[3].z);
	}

	void Transform::SetPosition(glm::vec3 position)
	{
		modelMatrix[3].x = position.x;
		modelMatrix[3].y = position.y;
		modelMatrix[3].z = position.z;

		OnTransformed.Publish(modelMatrix);
	}
}
