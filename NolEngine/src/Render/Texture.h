#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include <stb/stbimage.h>
#include <glad/glad.h>

namespace Nol
{
	typedef struct textureSetting
	{
		int SWrapping = GL_REPEAT;
		int TWrapping = GL_REPEAT;
		int RWrapping = GL_REPEAT;
		int MinFilter = GL_LINEAR;
		int MagFilter = GL_LINEAR;
	} TextureSetting;

	enum TextureType
	{
		Texture1D   = GL_TEXTURE_1D,
		Texture2D   = GL_TEXTURE_2D,
		Texture3D   = GL_TEXTURE_3D,
		TextureCube = GL_TEXTURE_CUBE_MAP
	};

	class Texture
	{
	private:
		std::string filePath;
		int height;
		int width;
		int depth;
		int nrChannels;

	protected:
		std::shared_ptr<unsigned int> id;
		TextureSetting setting;
		TextureType type;		
		
	public:
		NOL_API Texture(TextureType type, const std::string& filePath); // use default texture setting
		NOL_API Texture(TextureType type, const std::string& filePath, TextureSetting setting);
		NOL_API virtual ~Texture() = default;

		NOL_API inline const std::string& FilePath() const { return filePath; }
		NOL_API inline TextureType Type() const { return type; }
		NOL_API inline int Width()  const { return width;  }
		NOL_API inline int Height() const { return height; }
		NOL_API inline int Depth()  const { return depth;  }
		NOL_API inline int NRChannels()  const { return nrChannels; }
		NOL_API inline unsigned int ID() const { return *id; }
	
	protected:
		Texture() = default;

	private:
		unsigned char* LoadTexture(const std::string& filePath);
		void GenerateTexture();
	};
}
