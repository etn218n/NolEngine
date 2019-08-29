#include "PCH.h"
#include "MeshRenderer.h"

namespace Nol
{
	MeshRenderer::MeshRenderer(Mesh& mesh) : mesh(mesh)
	{
		SetupSelectors();
	}

	MeshRenderer::MeshRenderer(Mesh& mesh, Shader& shader) : mesh(mesh), shader(shader)
	{
		SetupSelectors();
	}

	MeshRenderer::MeshRenderer(Mesh& mesh, Shader& shader, Material& material) : mesh(mesh), shader(shader), material(material)
	{
		SetupSelectors();
	}

	MeshRenderer::MeshRenderer(const MeshRenderer& other) : mesh(other.mesh), shader(other.shader), material(other.material)
	{
		SetupSelectors();
	}

	void MeshRenderer::SetupSelectors()
	{
		uploadUniformFn = [](const Shader&) {};

		if (mesh.NumberofIndices() == 0)
		{
			drawFn = [&]()
			{
				uploadUniformFn(shader);

				for (unsigned int i = 0; i < mesh.NumberofTextures(); i++)
				{
					shader.SetUniformInt(shader.uniform.Textures[i], (int)i);

					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(mesh.TextureList()[i].Type(), mesh.TextureList()[i].ID());
				}

				glBindVertexArray(mesh.VAO());

				glDrawArrays(GL_TRIANGLES, 0, mesh.NumberofVertices());
			};
		}
		else
		{
			drawFn = [&]()
			{
				uploadUniformFn(shader);

				for (unsigned int i = 0; i < mesh.NumberofTextures(); i++)
				{
					shader.SetUniformInt(shader.uniform.Textures[i], (int)i);

					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(mesh.TextureList()[i].Type(), mesh.TextureList()[i].ID());
				}

				glBindVertexArray(mesh.VAO());

				glDrawElements(GL_TRIANGLES, mesh.NumberofIndices(), GL_UNSIGNED_INT, 0);
			};
		}
	}
}
