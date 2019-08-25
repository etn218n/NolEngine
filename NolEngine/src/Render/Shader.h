#pragma once

#include "PCH.h"
#include "NolAPI.h"

#include <glad/glad.h>

#include "Uniform.h"

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
	public:
		Uniform uniform;

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

		NOL_API inline const unsigned int ID() const { return *id; }
		NOL_API inline const std::string& VertexSource()   const { return vertexSource;   }
		NOL_API inline const std::string& FragmentSource() const { return fragmentSource; }

		NOL_API inline void SetUniformInt(const std::string& uniformName, int i) const { glUniform1i(glGetUniformLocation(*id, uniformName.c_str()), i); }
		NOL_API inline void SetUniformFloat(const std::string& uniformName, float f) const { glUniform1f(glGetUniformLocation(*id, uniformName.c_str()), f); }
		NOL_API inline void SetUniformVec3(const std::string& uniformName, glm::vec3 v3) const { glUniform3f(glGetUniformLocation(*id, uniformName.c_str()), v3.x, v3.y, v3.z); }
		NOL_API inline void SetUniformVec4(const std::string& uniformName, glm::vec4 v4) const { glUniform4f(glGetUniformLocation(*id, uniformName.c_str()), v4.x, v4.y, v4.z, v4.w); }
		NOL_API inline void SetUniformVec4Ptr(const std::string& uniformName, const float* ptr) const { glUniformMatrix4fv(glGetUniformLocation(*id, uniformName.c_str()), 1, GL_FALSE, ptr); }

		NOL_API inline void SetUniformInt(int uniformLocation, int i) const { glUniform1i(uniformLocation, i); }
		NOL_API inline void SetUniformFloat(int uniformLocation, float f) const { glUniform1f(uniformLocation, f); }
		NOL_API inline void SetUniformVec3(int uniformLocation, glm::vec3 v3) const { glUniform3f(uniformLocation, v3.x, v3.y, v3.z); }
		NOL_API inline void SetUniformVec4(int uniformLocation, glm::vec4 v4) const { glUniform4f(uniformLocation, v4.x, v4.y, v4.z, v4.w); }
		NOL_API inline void SetUniformVec4Ptr(int uniformLocation, const float* ptr) const { glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, ptr); }

	private:
		bool ParseShaderSource(const std::string& filePath);
		unsigned int CompileShader(ShaderType shaderType);
		void CreateShaderProgram();
		void SetupUniform();
	};
}

