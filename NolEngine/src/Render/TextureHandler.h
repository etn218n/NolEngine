#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Component/Material.h"

#include "Render/Texture.h"
#include "Render/Shader.h"
#include "Render/UniformLocation.h"

namespace Nol
{
	class TextureHandler
	{
	private:
		std::shared_ptr<Material> material;
		std::function<void()> uploadUniformFn;

	public:
		TextureHandler(std::shared_ptr<Material> material);

		inline void UploadUniform() const { uploadUniformFn(); }
	};
}
