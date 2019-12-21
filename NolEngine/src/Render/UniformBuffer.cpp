#include "PCH.h"
#include "UniformBuffer.h"

namespace Nol
{
	UniformBuffer::UniformBuffer(size_t bufferSizeInBytes)
	{
		unsigned int newUBO = -1;
		glGenBuffers(1, &newUBO);

		if (newUBO != -1)
		{
			glBindBuffer(GL_UNIFORM_BUFFER, newUBO);
			glBufferData(GL_UNIFORM_BUFFER, bufferSizeInBytes, NULL, GL_STATIC_DRAW);
			glBindBuffer(GL_UNIFORM_BUFFER, 0);

			ubo = std::shared_ptr<unsigned int>(new unsigned int(newUBO), [&](unsigned int*)
			{
				glDeleteBuffers(1, &(*ubo));
				INFO("Successful to delete uniform buffer. (UBO: {0})", *ubo);
			});

			INFO("Successful to create uniform buffer. (UBO: {0})", *ubo);
		}
		else
		{
			ERR("Failed to create uniform buffer.");
		}
	}

	void UniformBuffer::BindToSlot(int slotIndex)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
		glBindBufferBase(GL_UNIFORM_BUFFER, slotIndex, *ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::UpdateData(size_t dataSizeInBytes, const void* dataPtr)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, dataSizeInBytes, dataPtr);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void UniformBuffer::UpdateData(int offsetInBytes, size_t dataSizeInBytes, const void* dataPtr)
	{
		glBindBuffer(GL_UNIFORM_BUFFER, *ubo);
		glBufferSubData(GL_UNIFORM_BUFFER, offsetInBytes, dataSizeInBytes, dataPtr);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}
}