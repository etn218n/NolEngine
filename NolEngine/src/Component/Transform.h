#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Event/Observable.h"

#include "Component/Component.h"

namespace Nol
{
	class Transform : public Component
	{
	friend class GameObject;

	public:
		Observable<const glm::mat4&> OnTransformed;

	private:
		Observer<const glm::mat4&> parentTransformedSubcriber;
		std::vector<Transform*> childList;
		Transform* parent;
		glm::mat4 globalMatrix;
		glm::mat4 localMatrix;

	public:
		NOL_API Transform();
		NOL_API virtual ~Transform() = default;

		NOL_API void Translate(const glm::vec3& v);
		NOL_API void Scale(const glm::vec3& v);
		NOL_API void Rotate(float degree, const glm::vec3& axis);

		NOL_API const glm::vec3 Position() const;
		NOL_API const glm::vec3 LocalPosition() const;
		NOL_API const glm::vec3 Front() const;

		NOL_API void SetPosition(const glm::vec3& position);
		NOL_API void SetLocalPosition(const glm::vec3& position);

		NOL_API inline const glm::mat4& GlobalModelMatrix() const { return globalMatrix; }
		NOL_API inline const glm::mat4& LocalModelMatrix()  const { return localMatrix;  }
		NOL_API inline const float* DataPointer() const { return glm::value_ptr(globalMatrix); };
		
	private:
		void Update();
		void AddChild(Transform* newChild);
		void RemoveChild(Transform* removedChild);
	};
}

