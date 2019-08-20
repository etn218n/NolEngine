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
		if (ParseShaderSource(filePath) == true)
		{
			CreateShaderProgram();
		}
	}

	Shader::Shader(const Shader & other) : 
		fragmentSource(other.fragmentSource),
		vertexSource(other.vertexSource),
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

	void Shader::SetUniformInt(const std::string& uniformName, int i) const
	{
		glUniform1i(glGetUniformLocation(*id, uniformName.c_str()), i);
	}

	void Shader::SetUniformFloat(const std::string & uniformName, float f) const
	{
		glUniform1f(glGetUniformLocation(*id, uniformName.c_str()), f);
	}

	void Shader::SetUniformVec3(const std::string& uniformName, glm::vec3 v3) const
	{
		glUniform3f(glGetUniformLocation(*id, uniformName.c_str()), v3.x, v3.y, v3.z);
	}

	void Shader::SetUniformVec4(const std::string& uniformName, glm::vec4 v4) const
	{
		glUniform4f(glGetUniformLocation(*id, uniformName.c_str()), v4.x, v4.y, v4.z, v4.w);
	}

	void Shader::SetUniformVec4Ptr(const std::string& uniformName, const float* ptr) const
	{
		glUniformMatrix4fv(glGetUniformLocation(*id, uniformName.c_str()), 1, GL_FALSE, ptr);
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
}
