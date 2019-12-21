#include "PCH.h"
#include "ShaderTechnique.h"

namespace Nol
{
	void ShaderTechnique::VoidFn()
	{
	}

	void ShaderTechnique::TextureFn0x01()
	{
		/*for (size_t i = 0; i < textures.size(); i++)
		{
			shader->SetTextureIndex(i, (int)i);

			glActiveTexture(GL_TEXTURE0 + (int)i);
			glBindTexture(textures[i].Type(), textures[i].ID());
		}*/
	}
}