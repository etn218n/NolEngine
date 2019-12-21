#include "PCH.h"
#include "Shader.h"

namespace Nol
{
	Shader::Shader()
	{
		vertexSource   = DefaultVertexShaderSource;
		fragmentSource = DefaultFragmentShaderSource;

		CreateShaderProgram();

		SetupUniform();
	}

	Shader::Shader(const std::string& filePath)
	{
		if (ParseShaderSource(filePath) == true)
		{
			CreateShaderProgram();
		}

		SetupUniform();
	}

	Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource) : vertexSource(vertexSource), fragmentSource(fragmentSource)
	{
		CreateShaderProgram();

		SetupUniform();
	}

	Shader::Shader(const Shader& other) :
		fragmentSource(other.fragmentSource),
		vertexSource(other.vertexSource),
		uniformLocation(other.uniformLocation),
		id(other.id) {}

	bool Shader::ParseShaderSource(const std::string& filePath)
	{
		std::ifstream fileStream(filePath);

		if (!fileStream.is_open())
		{
			ERR("Failed to read shader file. (Path: \"{0}\")", filePath);
			return false;
		}

		std::string line;
		std::stringstream vertexStream;
		std::stringstream fragmentStream;

		std::stringstream* streamSelector = nullptr;

		while (std::getline(fileStream, line))
		{
			if (line.find("#define vertex") != std::string::npos)
				streamSelector = &vertexStream;
			else if (line.find("#define fragment") != std::string::npos)
				streamSelector = &fragmentStream;
			else
				*streamSelector << line << '\n';
		}

		vertexSource   = vertexStream.str();
		fragmentSource = fragmentStream.str();

		fileStream.close();

		return true;
	}

	unsigned int Shader::CompileShader(ShaderType shaderType)
	{
		unsigned int shaderID = glCreateShader((int)shaderType);

		const char* source;

		switch (shaderType)
		{
			case ShaderType::Vertex:   source = vertexSource.c_str();   break;
			case ShaderType::Fragment: source = fragmentSource.c_str(); break;
		}

		glShaderSource(shaderID, 1, &source, NULL);
		glCompileShader(shaderID);

		int success;
		char infoLog[512];
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);

		if (!success)
		{
			glGetShaderInfoLog(shaderID, 512, NULL, infoLog);
			ERR("Shader compilation failed. {0}", infoLog);
			return 0;
		}

		std::string shaderName = (shaderType == ShaderType::Vertex) ? "Vertex" : "Fragment";

		if (shaderID == 0)
			ERR("{0} shader failed to generate. Check if OpenGL context is bound.", shaderName);

		return shaderID;
	}

	void Shader::CreateShaderProgram()
	{
		unsigned int vertexID   = CompileShader(ShaderType::Vertex);
		unsigned int fragmentID = CompileShader(ShaderType::Fragment);

		if (vertexID == 0)
		{
			ERR("Failed to generate vertex shader program.");
			return;
		}

		if (fragmentID == 0)
		{
			ERR("Failed to generate fragment shader program.");
			return;
		}

		int programID = glCreateProgram();

		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);

		glLinkProgram(programID);

		if (programID == 0)
			ERR("Failed to generate shader program.");
		else
		{
			INFO("Successful to generate shader program. (ID: {0})", programID);
			
			id = std::shared_ptr<unsigned int>(new unsigned int(programID), [](unsigned int* ID)
			{
				glDeleteProgram(*ID);
			});
		}

		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}

	void Shader::SetupUniform()
	{
		uniformLocation.ViewMatrix  = glGetUniformLocation(*id, "uView");
		uniformLocation.ModelMatrix = glGetUniformLocation(*id, "uModel");
		uniformLocation.ProjectionMatrix	 = glGetUniformLocation(*id, "uProjection");
		uniformLocation.ProjectionViewMatrix = glGetUniformLocation(*id, "uProjectionView");

		uniformLocation.Material.Color	   = glGetUniformLocation(*id, "uMaterial.Color");
		uniformLocation.Material.Ambient   = glGetUniformLocation(*id, "uMaterial.Ambient");
		uniformLocation.Material.Diffuse   = glGetUniformLocation(*id, "uMaterial.Diffuse");
		uniformLocation.Material.Specular  = glGetUniformLocation(*id, "uMaterial.Specular");
		uniformLocation.Material.Shininess = glGetUniformLocation(*id, "uMaterial.Shininess");

		uniformLocation.CameraPosition = glGetUniformLocation(*id, "uCameraPosition");
		uniformLocation.Color = glGetUniformLocation(*id, "uColor");

		unsigned int cameraBlockIndex = glGetUniformBlockIndex(*id, "CameraBuffer");
		glUniformBlockBinding(*id, cameraBlockIndex, CameraBufferIndex);

		uniformLocation.NumberofLights = glGetUniformLocation(*id, "uNumberofLights");

		for (size_t i = 0; i < MaxNumberofLightSupported; i++)
		{
			std::string index = std::to_string(i);

			uniformLocation.Light[i].Type      = glGetUniformLocation(*id, std::string("uLight["+index+"].Type").c_str());
			uniformLocation.Light[i].Color	   = glGetUniformLocation(*id, std::string("uLight["+index+"].Color").c_str());
			uniformLocation.Light[i].Position  = glGetUniformLocation(*id, std::string("uLight["+index+"].Position").c_str());
			uniformLocation.Light[i].Direction = glGetUniformLocation(*id, std::string("uLight["+index+"].Direction").c_str());

			uniformLocation.Light[i].Constant  = glGetUniformLocation(*id, std::string("uLight["+index+"].Constant").c_str());
			uniformLocation.Light[i].Linear    = glGetUniformLocation(*id, std::string("uLight["+index+"].Linear").c_str());
			uniformLocation.Light[i].Quadratic = glGetUniformLocation(*id, std::string("uLight["+index+"].Quadratic").c_str());

			uniformLocation.Light[i].CutoffAngle	  = glGetUniformLocation(*id, std::string("uLight["+index+"].CutoffAngle").c_str());
			uniformLocation.Light[i].OuterCutoffAngle = glGetUniformLocation(*id, std::string("uLight["+index+"].OuterCutoffAngle").c_str());
		}

		for (size_t i = 0; i < MaxNumberofTextureSupported; i++)
		{
			std::string index = std::to_string(i);

			uniformLocation.Texture[i] = glGetUniformLocation(*id, std::string("uTexture" + index).c_str());
		}
	}
}
