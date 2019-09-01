#include "PCH.h"
#include "Texture.h"

namespace Nol
{
	Texture::Texture(TextureType type, unsigned char* data)
	{
		id = std::shared_ptr<unsigned int>(new unsigned int(0), [](unsigned int* id)
		{
			INFO("Successfully delete texture. (ID: {0})", *id);
			glDeleteTextures(1, &(*id));
		});

		GenerateTexture(data);
	}

	Texture::Texture(TextureType type, const std::string& filePath) : filePath(filePath), type(type)
	{
		id = std::shared_ptr<unsigned int>(new unsigned int(0), [](unsigned int* id)
		{
			INFO("Successfully delete texture. (ID: {0})", *id);
			glDeleteTextures(1, &(*id));
		});

		GenerateTexture();
	}

	Texture::Texture(TextureType type, const std::string& filePath, TextureSetting setting) : setting(setting), filePath(filePath), type(type)
	{
		id = std::shared_ptr<unsigned int>(new unsigned int(0), [](unsigned int* id)
		{
			INFO("Successfully delete texture. (ID: {0})", *id);
			glDeleteTextures(1, &(*id));
		});

		GenerateTexture();
	}

	unsigned char* Texture::LoadTexture(const std::string& filePath)
	{
		stbi_set_flip_vertically_on_load(true);

		unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);

		return data;
	}

	void Texture::GenerateTexture()
	{
		width  = 0;
		height = 0;
		depth  = 0;

		unsigned char* data = LoadTexture(filePath);

		if (data == nullptr)
		{
			ERR("Failed to load texture. (Path: \"{0}\")", filePath);
			return;
		}
		INFO("Successful to load texture. (Path: \"{0}\")", filePath);

		glGenTextures(1, &(*id));

		if (*id == 0)
		{
			ERR("Failed to generate texture. Check if OpenGL context is bound.");
			return;
		}

		glBindTexture(type, *id);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, setting.SWrapping);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, setting.TWrapping);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, setting.MinFilter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, setting.MagFilter);

		// TODO: implementation for other channels
		int channel;

		switch (nrChannels)
		{
			case 1: channel = GL_RED;  break;
			case 3: channel = GL_RGB;  break;
			case 4: channel = GL_RGBA; break;
		}

		switch (type)
		{
			case TextureType::Texture1D: glTexImage1D(type, 0, channel, width, 0, channel, GL_UNSIGNED_BYTE, data); break; break;
			case TextureType::Texture2D: glTexImage2D(type, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data); break;
			case TextureType::Texture3D: glTexImage3D(type, 0, channel, width, height, depth, 0, channel, GL_UNSIGNED_BYTE, data); break; break;
		}

		glGenerateMipmap(type);

		glBindTexture(type, 0);
		stbi_image_free(data);

		if (*id == 0)
			ERR("Failed to generate texture.");
		else
			INFO("Successful to generate texture. (ID: {0})", *id);
	}

	void Texture::GenerateTexture(unsigned char* data)
	{
		width = 0;
		height = 0;
		depth = 0;

		glGenTextures(1, &(*id));

		if (*id == 0)
		{
			ERR("Failed to generate texture. Check if OpenGL context is bound.");
			return;
		}

		glBindTexture(type, *id);

		glTexParameteri(type, GL_TEXTURE_WRAP_S, setting.SWrapping);
		glTexParameteri(type, GL_TEXTURE_WRAP_T, setting.TWrapping);
		glTexParameteri(type, GL_TEXTURE_MIN_FILTER, setting.MinFilter);
		glTexParameteri(type, GL_TEXTURE_MAG_FILTER, setting.MagFilter);

		// TODO: implementation for other channels
		int channel;

		switch (nrChannels)
		{
		case 1: channel = GL_RED;  break;
		case 3: channel = GL_RGB;  break;
		case 4: channel = GL_RGBA; break;
		}

		switch (type)
		{
		case TextureType::Texture1D: glTexImage1D(type, 0, channel, width, 0, channel, GL_UNSIGNED_BYTE, data); break; break;
		case TextureType::Texture2D: glTexImage2D(type, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data); break;
		case TextureType::Texture3D: glTexImage3D(type, 0, channel, width, height, depth, 0, channel, GL_UNSIGNED_BYTE, data); break; break;
		}

		glGenerateMipmap(type);

		glBindTexture(type, 0);
		//free(data);

		if (*id == 0)
			ERR("Failed to generate texture.");
		else
			INFO("Successful to generate texture. (ID: {0})", *id);
	}
}
