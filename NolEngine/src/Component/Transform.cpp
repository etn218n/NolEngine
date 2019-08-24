#include "PCH.h"
#include "Transform.h"

namespace Nol
{
	Transform::Transform() : globalMatrix(glm::mat4(1.0f)), localMatrix(glm::mat4(1.0f)), parent(nullptr) { }

	void Transform::Scale(const glm::vec3 & v)
	{
		globalMatrix = glm::scale(globalMatrix, v);

		Update();
	}

	void Transform::Translate(const glm::vec3& v)
	{
		globalMatrix = glm::translate(globalMatrix, v);

		Update();
	}

	void Transform::Rotate(float degree, const glm::vec3& axis)
	{
		globalMatrix = glm::rotate(globalMatrix, glm::radians(degree), axis);

		Update();
	}

	const glm::vec3 Transform::Position() const
	{
		return glm::vec3(globalMatrix[3].x, globalMatrix[3].y, globalMatrix[3].z);
	}

	const glm::vec3 Transform::LocalPosition() const
	{
		return glm::vec3(localMatrix[3].x, localMatrix[3].y, localMatrix[3].z);
	}

	const glm::vec3 Transform::Front() const
	{
		return glm::normalize(glm::vec3(globalMatrix[2].x, globalMatrix[2].y, globalMatrix[2].z));
	}

	void Transform::SetPosition(const glm::vec3& position)
	{
		globalMatrix[3].x = position.x;
		globalMatrix[3].y = position.y;
		globalMatrix[3].z = position.z;

		Update();
	}

	void Transform::SetLocalPosition(const glm::vec3& position)
	{
		localMatrix[3].x = position.x;
		localMatrix[3].y = position.y;
		localMatrix[3].z = position.z;

		globalMatrix[3].x = parent->globalMatrix[3].x + localMatrix[3].x;
		globalMatrix[3].y = parent->globalMatrix[3].y + localMatrix[3].y;
		globalMatrix[3].z = parent->globalMatrix[3].z + localMatrix[3].z;

		OnTransformed.Publish(globalMatrix);
	}

	void Transform::Update()
	{
		if (parent != nullptr)
			localMatrix = glm::inverse(parent->globalMatrix) * globalMatrix;

		OnTransformed.Publish(globalMatrix);
	}

	void Transform::AddChild(Transform* newChild)
	{
		// Disallow circular reference
		if (newChild == this)
			return;

		for (const auto& child : childList)
		{
			if (child == newChild)
				return;
		}

		childList.push_back(newChild);

		newChild->parent = this;

		// calculate child's local matrix when first attach to this parent transform
		newChild->localMatrix = glm::inverse(this->globalMatrix) * newChild->globalMatrix;

		newChild->parentTransformedSubcriber = this->OnTransformed.Subcribe([newChild](const glm::mat4& parentModelMatrix)
		{
			newChild->globalMatrix = parentModelMatrix * newChild->localMatrix;

			// propergate changes to its children
			newChild->OnTransformed.Publish(newChild->globalMatrix);
		});
	}

	void Transform::RemoveChild(Transform* removedChild)
	{
		childList.erase(
			std::remove_if(childList.begin(), childList.end(),
				[removedChild](Transform* child)
				{
					return (removedChild == child);
				}),
			childList.end());

		OnTransformed.Unsubcribe(removedChild->parentTransformedSubcriber);

		removedChild->localMatrix = glm::mat4(1.0);
		removedChild->parent = nullptr;
	}
}
