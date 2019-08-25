#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include <stb/stbimage.h>
#include <glad/glad.h>

namespace Nol
{
	typedef struct textureSetting
	{
		int TextureType		   = GL_TEXTURE_2D;
		int HorizontalWrapping = GL_REPEAT;
		int VerticalWrapping   = GL_REPEAT;
		int MinFilter		   = GL_LINEAR;
		int MagFilter		   = GL_LINEAR;
	} TextureSetting;

	class Texture
	{
	private:
		std::shared_ptr<unsigned int> id;
		std::shared_ptr<const unsigned char> data;
		int height;
		int width;
		int nrChannels;
		TextureSetting setting;
		
	public:
		NOL_API Texture(const std::string& filePath, TextureSetting setting);
		NOL_API Texture(const std::string& filePath); // use default texture setting
		NOL_API Texture(const Texture& other);
		NOL_API virtual ~Texture() = default;

		NOL_API inline const int Type() const { return setting.TextureType; }
		NOL_API inline const int Width() const { return width; }
		NOL_API inline const int Height() const { return height; }
		NOL_API inline const int NRChannels() const { return nrChannels; }
		NOL_API inline const unsigned int ID() const { return *id; }

	private:
		bool LoadTexture(const std::string& filePath);
		void GenerateTexture();
	};
}
