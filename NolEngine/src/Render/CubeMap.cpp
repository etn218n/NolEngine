#include "PCH.h"
#include "CubeMap.h"

namespace Nol
{
	CubeMap::CubeMap(const std::vector<std::string>& filePaths)
	{
		type = TextureType::TextureCube;

		// default setting
		setting.MinFilter = GL_LINEAR;
		setting.MagFilter = GL_LINEAR;
		setting.SWrapping = GL_CLAMP_TO_EDGE;
		setting.TWrapping = GL_CLAMP_TO_EDGE;
		setting.RWrapping = GL_CLAMP_TO_EDGE;

		GenerateCubeMap(filePaths);
	}

	CubeMap::CubeMap(const std::vector<std::string>& filePaths, TextureSetting setting)
	{
		this->setting = setting;

		type = TextureType::TextureCube;

		GenerateCubeMap(filePaths);
	}

	void CubeMap::GenerateCubeMap(const std::vector<std::string>& filePaths)
	{
		unsigned int textureID;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		int width, height, nrChannels;

		stbi_set_flip_vertically_on_load(false);

		for (unsigned int i = 0; i < filePaths.size(); i++)
		{
			unsigned char *data = stbi_load(filePaths[i].c_str(), &width, &height, &nrChannels, 0);

			if (data)
			{
				int channel;

				switch (nrChannels)
				{
					case 1: channel = GL_RED;  break;
					case 3: channel = GL_RGB;  break;
					case 4: channel = GL_RGBA; break;
				}

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data);
				INFO("Successful to load cubemap texture. (Path: \"{0}\")", filePaths[i]);
			}
			else
				ERR("Failed to load cubemap texture. (Path: \"{0}\")", filePaths[i]);

			stbi_image_free(data);
		}

		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, setting.MinFilter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, setting.MagFilter);
		glTexParameteri(type, GL_TEXTURE_WRAP_S, setting.SWrapping);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, setting.TWrapping);
		glTexParameteri(type, GL_TEXTURE_WRAP_R, setting.RWrapping);

		if (textureID == 0)
			ERR("Failed to generate CubeMap.");
		else
		{
			id = std::shared_ptr<unsigned int>(new unsigned int(textureID), [](unsigned int* id)
			{
				INFO("Successfully delete CubeMap. (ID: {0})", *id);
				glDeleteTextures(1, &(*id));
			});

			INFO("Successful to generate CubeMap.");
		}
	}
}
