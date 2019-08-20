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

	MeshRenderer::MeshRenderer(const MeshRenderer& other) : 
		mesh(other.mesh), 
		shader(other.shader)
	{
		SetupSelectors();
	}

	void MeshRenderer::SetupSelectors()
	{
		uploadUniformFn = [](const Shader&) {};

		if (mesh.NumberOfIndices() == 0)
		{
			drawFn = [&]()
			{
				uploadUniformFn(shader);

				for (unsigned int i = 0; i < mesh.NumberOfTextures(); i++)
				{
					shader.SetUniformInt("uTexture" + std::to_string(i), (int)i);

					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, mesh.GetTextureList()[i].GetID());
				}

				glBindVertexArray(mesh.GetVAO());

				glDrawArrays(GL_TRIANGLES, 0, mesh.NumberOfVertices());
			};
		}
		else
		{
			drawFn = [&]()
			{
				uploadUniformFn(shader);

				for (unsigned int i = 0; i < mesh.NumberOfTextures(); i++)
				{
					shader.SetUniformInt("uTexture" + std::to_string(i), (int)i);

					glActiveTexture(GL_TEXTURE0 + i);
					glBindTexture(GL_TEXTURE_2D, mesh.GetTextureList()[i].GetID());
				}

				glBindVertexArray(mesh.GetVAO());

				glDrawElements(GL_TRIANGLES, mesh.NumberOfIndices(), GL_UNSIGNED_INT, 0);
			};
		}
	}
}
