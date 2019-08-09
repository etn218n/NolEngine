#include "PCH.h"
#include "Shader.h"

namespace Nol
{
	Shader::Shader()
	{
		vertexSource   = DefaultVertexShaderSource;
		fragmentSource = DefaultFragmentShaderSource;

		CreateShaderProgram();
	}

	Shader::Shader(const std::string& filePath)
	{
		ParseShaderSource(filePath);

		CreateShaderProgram();
	}

	Shader::Shader(const Shader & other) : 
		fragmentSource(other.fragmentSource),
		vertexSource(other.vertexSource),
		id(other.id) {}

	void Shader::ParseShaderSource(const std::string& filePath)
	{
		try
		{
			std::ifstream fileStream(filePath);

			std::string line;
			std::stringstream vertexStream;
			std::stringstream fragmentStream;

			std::stringstream* streamSelector = nullptr;

			while (getline(fileStream, line))
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
		}
		catch (std::ifstream::failure e)
		{
			ERR("Failed to read shader file. (Path: \"{0}\")", filePath);
		}
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

		int programID = glCreateProgram();

		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);

		glLinkProgram(programID);

		if (programID == 0)
			ERR("Failed to create shader program.");
		else
		{
			INFO("Succesful to create shader program.");
			
			id = std::shared_ptr<unsigned int>(new unsigned int(programID), [](unsigned int* ID)
			{
				glDeleteProgram(*ID);
			});
		}

		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);
	}
}
