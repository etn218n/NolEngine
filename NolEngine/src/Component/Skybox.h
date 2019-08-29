#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include "MeshRenderer.h"
#include "Render/CubeMap.h"

namespace Nol
{
	class Skybox
	{
	private:
		static const std::vector<float> SkyboxVertices;
		static const std::string& VertexSource;
		static const std::string& FragmentSource;

		CubeMap* cubeMap;
		MeshRenderer* skyboxRenderer;

	public:
		NOL_API Skybox();
		NOL_API Skybox(const std::vector<std::string>& filePaths);
		NOL_API virtual ~Skybox();

		NOL_API inline const MeshRenderer* GetSkyboxRenderer() const { return skyboxRenderer; }

		NOL_API void Render() const;
	};
}
