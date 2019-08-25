#include "PCH.h"
#include "Texture.h"

namespace Nol
{
	Texture::Texture(const std::string& filePath, TextureSetting setting) : setting(setting), filePath(filePath)
	{
		id = std::shared_ptr<unsigned int>(new unsigned int(0), [](unsigned int* id)
		{
			INFO("Successfully delete texture. (ID: {0})", *id);
			glDeleteTextures(1, &(*id));
		});

		if (LoadTexture(filePath) == false)
			ERR("Failed to load texture. (Path: \"{0}\")", filePath);
		else
		{
			INFO("Successful to load texture. (Path: \"{0}\")", filePath);

			GenerateTexture();
		}
	}

	Texture::Texture(const std::string& filePath) : filePath(filePath)
	{
		id = std::shared_ptr<unsigned int>(new unsigned int(0), [](unsigned int* id)
		{
			INFO("Successfully delete texture. (ID: {0})", *id);
			glDeleteTextures(1, &(*id));
		});

		if (LoadTexture(filePath) == false)
			ERR("Failed to load texture. (Path: \"{0}\")", filePath);
		else
		{
			INFO("Successful to load texture. (Path: \"{0}\")", filePath);

			GenerateTexture();
		}
	}

	Texture::Texture(const Texture& other) :
		nrChannels(other.nrChannels),
		filePath(other.filePath),
		setting(other.setting),
		height(other.height),
		width(other.width),
		data(other.data),
		id(other.id) {}

	bool Texture::LoadTexture(const std::string& filePath)
	{
		stbi_set_flip_vertically_on_load(true);

		data = std::shared_ptr<const unsigned char>(stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0));

		return (data != nullptr);
	}

	void Texture::GenerateTexture()
	{
		glGenTextures(1, &(*id));

		if (*id == 0)
		{
			ERR("Failed to generate texture. Check if OpenGL context is bound.");
			return;
		}

		glBindTexture(setting.TextureType, *id);

		glTexParameteri(setting.TextureType, GL_TEXTURE_WRAP_S, setting.HorizontalWrapping);
		glTexParameteri(setting.TextureType, GL_TEXTURE_WRAP_T, setting.VerticalWrapping);
		glTexParameteri(setting.TextureType, GL_TEXTURE_MIN_FILTER, setting.MinFilter);
		glTexParameteri(setting.TextureType, GL_TEXTURE_MAG_FILTER, setting.MagFilter);

		// TODO: implementation for other channels
		int channel = nrChannels == 3 ? GL_RGB : GL_RGBA;

		glTexImage2D(setting.TextureType, 0, channel, width, height, 0, channel, GL_UNSIGNED_BYTE, data.get());
		glGenerateMipmap(setting.TextureType);

		glBindTexture(setting.TextureType, 0);

		if (*id == 0)
			ERR("Failed to generate texture.");
		else
			INFO("Successful to generate texture. (ID: {0})", *id);
	}
}
