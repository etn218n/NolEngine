#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Core/Log.h"

#include <glad/glad.h>

namespace Nol
{
	class UniformBuffer
	{
	private:
		std::shared_ptr<unsigned int> ubo;

	public:
		UniformBuffer(size_t bufferSizeInBytes);

		void Bind() { glBindBuffer(GL_UNIFORM_BUFFER, *ubo); }
		void BindToSlot(int slotIndex);
		void UpdateData(size_t dataSizeInBytes, const void* dataPtr);
		void UpdateData(int offsetInBytes, size_t dataSizeInBytes, const void* dataPtr);
	};
}