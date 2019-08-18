#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include <glad/glad.h>

namespace Nol
{
	const std::string DefaultVertexShaderSource = R"(
		#version 330 core

		layout(location = 0) in vec3 Position;
		layout(location = 1) in vec3 Normal;
		layout(location = 2) in vec2 TexCoord;

		out vec3 VertexNormal;
		out vec2 VertexTexCoord;

		uniform mat4 uModel;
		uniform mat4 uViewProjection;

		void main()
		{
			gl_Position    = uViewProjection * uModel * vec4(Position, 1.0);
			VertexNormal   = Normal;
			VertexTexCoord = TexCoord;
		})";

	const std::string DefaultFragmentShaderSource = R"(
		#version 330 core

		in vec3 VertexNormal;
		in vec2 VertexTexCoord;

		out vec4 FragColor;

		uniform sampler2D uTexture0;

		void main()
		{
			FragColor = texture(uTexture0, VertexTexCoord);
		})";

	enum class ShaderType
	{
		Vertex   = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER,
		Geometry = GL_GEOMETRY_SHADER,
	};

	class Shader
	{
	private:
		std::shared_ptr<unsigned int> id;
		std::string vertexSource;
		std::string fragmentSource;

	public:
		NOL_API Shader();
		NOL_API Shader(const std::string& filePath);
		NOL_API Shader(const Shader& other);
		NOL_API virtual ~Shader() = default;
		
		NOL_API inline void Use() const { glUseProgram(*id); }

		NOL_API inline const unsigned int GetID() const { return *id; }
		NOL_API inline const std::string& GetVertexSource()   const { return vertexSource;   }
		NOL_API inline const std::string& GetFragmentSource() const { return fragmentSource; }

		NOL_API void SetUniform1i(const std::string& uniformName, int index)   const;
		NOL_API void SetUniform1f(const std::string& uniformName, float f)     const;
		NOL_API void SetUniform3f(const std::string& uniformName, glm::vec3 v) const;
		NOL_API void SetUniform4f(const std::string& uniformName, glm::vec4 v) const;
		NOL_API void SetUniform4fv(const std::string& uniformName, const float* f) const;

	private:
		bool ParseShaderSource(const std::string& filePath);
		unsigned int CompileShader(ShaderType shaderType);
		void CreateShaderProgram();
	};
}

