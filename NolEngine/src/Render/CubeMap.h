#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "Texture.h"

namespace Nol
{
	class CubeMap : public Texture
	{
	public:
		NOL_API CubeMap(const std::vector<std::string>& filePaths);
		NOL_API CubeMap(const std::vector<std::string>& filePaths, TextureSetting setting);
		NOL_API virtual ~CubeMap() = default;

	private:
		void GenerateCubeMap(const std::vector<std::string>& filePaths);
	};
}

