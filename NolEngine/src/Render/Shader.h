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
		uniform mat4 uProjectionView;

		void main()
		{
			gl_Position    = uProjectionView * uModel * vec4(Position, 1.0);
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

		LightUniformLocation lightUniformLocation;
		MatrixUniformLocation matrixUniformLocation;
		GeneralUniformLocation generalUniformLocation;
		TextureUniformLocation textureUniformLocation;
		MaterialUniformLocation materialUniformLocation;

	public:
		NOL_API Shader();
		NOL_API Shader(const std::string& filePath);
		NOL_API Shader(const std::string& vertexSource, const std::string& fragmentSource);
		NOL_API Shader(const Shader& other);
		NOL_API virtual ~Shader() = default;
		
		NOL_API inline void Use() const { glUseProgram(*id); }

		NOL_API inline unsigned int ID() const { return *id; }
		NOL_API inline const std::string& VertexSource()   const { return vertexSource;   }
		NOL_API inline const std::string& FragmentSource() const { return fragmentSource; }

		NOL_API inline void SetUniformInt(const std::string& uniformName, int i) const { glUniform1i(glGetUniformLocation(*id, uniformName.c_str()), i); }
		NOL_API inline void SetUniformFloat(const std::string& uniformName, float f) const { glUniform1f(glGetUniformLocation(*id, uniformName.c_str()), f); }
		NOL_API inline void SetUniformVec3(const std::string& uniformName, const glm::vec3& v3) const { glUniform3f(glGetUniformLocation(*id, uniformName.c_str()), v3.x, v3.y, v3.z); }
		NOL_API inline void SetUniformVec4(const std::string& uniformName, const glm::vec4& v4) const { glUniform4f(glGetUniformLocation(*id, uniformName.c_str()), v4.x, v4.y, v4.z, v4.w); }
		NOL_API inline void SetUniformVec4Ptr(const std::string& uniformName, const float* ptr) const { glUniformMatrix4fv(glGetUniformLocation(*id, uniformName.c_str()), 1, GL_FALSE, ptr); }

		NOL_API inline void SetUniformInt(int uniformLocation, int i) const { glUniform1i(uniformLocation, i); }
		NOL_API inline void SetUniformFloat(int uniformLocation, float f) const { glUniform1f(uniformLocation, f); }
		NOL_API inline void SetUniformVec3(int uniformLocation, const glm::vec3& v3) const { glUniform3f(uniformLocation, v3.x, v3.y, v3.z); }
		NOL_API inline void SetUniformVec4(int uniformLocation, const glm::vec4& v4) const { glUniform4f(uniformLocation, v4.x, v4.y, v4.z, v4.w); }
		NOL_API inline void SetUniformVec4Ptr(int uniformLocation, const float* ptr) const { glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, ptr); }

		NOL_API inline void SetViewMatrix(const float* ptr)  const { glUniformMatrix4fv(matrixUniformLocation.View,  1, GL_FALSE, ptr); }
		NOL_API inline void SetModelMatrix(const float* ptr) const { glUniformMatrix4fv(matrixUniformLocation.Model, 1, GL_FALSE, ptr); }
		NOL_API inline void SetProjectionMatrix(const float* ptr)     const { glUniformMatrix4fv(matrixUniformLocation.Projection,	   1, GL_FALSE, ptr); }
		NOL_API inline void SetProjectionViewMatrix(const float* ptr) const { glUniformMatrix4fv(matrixUniformLocation.ProjectionView, 1, GL_FALSE, ptr); }

		NOL_API inline void SetMaterialColor(const glm::vec4& v4)    const { glUniform4f(materialUniformLocation.Color, v4.r, v4.g, v4.b, v4.a); }
		NOL_API inline void SetMaterialAmbient(const glm::vec3& v3)  const { glUniform3f(materialUniformLocation.Ambient,  v3.r, v3.g, v3.b);    }
		NOL_API inline void SetMaterialDiffuse(const glm::vec3& v3)  const { glUniform3f(materialUniformLocation.Diffuse,  v3.r, v3.g, v3.b);    }
		NOL_API inline void SetMaterialSpecular(const glm::vec3& v3) const { glUniform3f(materialUniformLocation.Specular, v3.r, v3.g, v3.b);    }
		NOL_API inline void SetMaterialShininess(float shininess)    const { glUniform1f(materialUniformLocation.Shininess, shininess); }

		NOL_API inline void SetNumberofLights(int numberofLights) const { glUniform1i(lightUniformLocation.NumberofLights, numberofLights); }
		NOL_API inline void SetLightType(size_t lightIndex, int lightType) const { glUniform1i(lightUniformLocation.Lights[lightIndex].Type, 1); }

		NOL_API inline void SetLightColor(size_t lightIndex, const glm::vec3& v3)     const { glUniform3f(lightUniformLocation.Lights[lightIndex].Color,	 v3.r, v3.g, v3.b); }
		NOL_API inline void SetLightPosition(size_t lightIndex, const glm::vec3& v3)  const { glUniform3f(lightUniformLocation.Lights[lightIndex].Position,  v3.x, v3.y, v3.z); }
		NOL_API inline void SetLightDirection(size_t lightIndex, const glm::vec3& v3) const { glUniform3f(lightUniformLocation.Lights[lightIndex].Direction, v3.x, v3.y, v3.z); }

		NOL_API inline void SetLightLinear(size_t lightIndex, float linear) const { glUniform1f(lightUniformLocation.Lights[lightIndex].Linear, linear); }
		NOL_API inline void SetLightConstant(size_t lightIndex, float constant) const { glUniform1f(lightUniformLocation.Lights[lightIndex].Constant, constant); }
		NOL_API inline void SetLightQuadratic(size_t lightIndex, float quadratic) const { glUniform1f(lightUniformLocation.Lights[lightIndex].Quadratic, quadratic); }
		NOL_API inline void SetLightCutoffAngle(size_t lightIndex, float angle) const { glUniform1f(lightUniformLocation.Lights[lightIndex].CutoffAngle, angle); }
		NOL_API inline void SetLightOuterCutoffAngle(size_t lightIndex, float angle) const { glUniform1f(lightUniformLocation.Lights[lightIndex].OuterCutoffAngle, angle); }

		NOL_API inline void SetTextureIndex(size_t textureIndex, int index) const { glUniform1i(textureUniformLocation.Textures[textureIndex], index); }

		NOL_API inline void SetCameraPosition(const glm::vec3& v3) const { glUniform3f(generalUniformLocation.CameraPosition, v3.x, v3.y, v3.z); }
		NOL_API inline void SetColor(const glm::vec4& v4) const { glUniform4f(generalUniformLocation.Color, v4.r, v4.b, v4.g, v4.a); }

	private:
		bool ParseShaderSource(const std::string& filePath);
		unsigned int CompileShader(ShaderType shaderType);
		void CreateShaderProgram();
		void SetupUniform();
	};
}

