#include "PCH.h"
#include "Skybox.h"

namespace Nol
{
	const std::vector<float> Skybox::SkyboxVertices = {
		// positions          
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		 1.0f,  1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f
	};

	const std::string& Skybox::VertexSource = R"(
		#version 330 core

		layout (location = 0) in vec3 Position;

		out vec3 TexCoord;

		uniform mat4 uProjectionView;

		void main()
		{
			TexCoord = Position;
			gl_Position  = uProjectionView * vec4(Position, 1.0);
		})";

	const std::string& Skybox::FragmentSource = R"(
		#version 330 core

		out vec4 FragColor;

		in vec3 TexCoord;

		uniform samplerCube uTexture0;

		void main()
		{    
			FragColor = texture(uTexture0, TexCoord);
		})";

	Skybox::Skybox()
	{
		cubeMap = new CubeMap({ "./resource/skybox/right.jpg",
								"./resource/skybox/left.jpg",
								"./resource/skybox/top.jpg",
								"./resource/skybox/bottom.jpg",
								"./resource/skybox/front.jpg",
								"./resource/skybox/back.jpg" });

		Shader skyboxShader(VertexSource, FragmentSource);
		Mesh skyboxMesh(SkyboxVertices, { static_cast<Texture>(*cubeMap) }, true);

		skyboxRenderer = new MeshRenderer(skyboxMesh, skyboxShader);
	}

	Skybox::Skybox(const std::vector<std::string>& filePaths)
	{
		cubeMap = new CubeMap(filePaths);

		Shader skyboxShader(VertexSource, FragmentSource);
		Mesh skyboxMesh(SkyboxVertices, { static_cast<Texture>(*cubeMap) }, true);

		skyboxRenderer = new MeshRenderer(skyboxMesh, skyboxShader);
	}

	Skybox::~Skybox()
	{
		delete cubeMap;
		delete skyboxRenderer;
	}

	void Skybox::Render() const
	{
		skyboxRenderer->Render();
	}
}