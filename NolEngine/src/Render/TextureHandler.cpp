#include "PCH.h"
#include "TextureHandler.h"

namespace Nol
{
	TextureHandler::TextureHandler(std::shared_ptr<Material> material)
	{
		const Shader& shader = material->GetShader();
		const std::vector<Texture>& textures = material->Textures;

		if (shader.UniformLocation().Texture[0] != -1)
		{
			uploadUniformFn = [shader, textures]() 
			{
				for (size_t i = 0; i < textures.size(); i++)
				{
					shader.SetTextureIndex(i, (int)i);
					glActiveTexture(GL_TEXTURE0 + (int)i);
					glBindTexture(textures[i].Type(), textures[i].ID());
				}
			};
		}
		else
		{
			uploadUniformFn = []() {};
		}
	}
}