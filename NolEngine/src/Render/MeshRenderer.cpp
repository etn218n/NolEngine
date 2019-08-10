#include "PCH.h"
#include "MeshRenderer.h"

namespace Nol
{
	MeshRenderer::MeshRenderer(Mesh& mesh) : mesh(mesh)
	{
		if (mesh.NumberOfIndices() == 0)
		{
			draw = [&](void)
			{
				glDrawArrays(GL_TRIANGLES, 0, mesh.NumberOfVertices());
			};
		}
		else
		{
			draw = [&](void)
			{
				glDrawElements(GL_TRIANGLES, mesh.NumberOfIndices(), GL_UNSIGNED_INT, 0);
			};
		}

		for (unsigned int i = 0; i < mesh.NumberOfTextures(); i++)
		{
			shader.SetUniform1i("uTexture" + std::to_string(i), i);
		}
	}

	MeshRenderer::MeshRenderer(Mesh& mesh, Shader& shader) : mesh(mesh), shader(shader)
	{
		if (mesh.NumberOfIndices() == 0)
		{
			draw = [&](void) 
			{
				glDrawArrays(GL_TRIANGLES, 0, mesh.NumberOfVertices());
			};
		}
		else
		{
			draw = [&](void)
			{
				glDrawElements(GL_TRIANGLES, mesh.NumberOfIndices(), GL_UNSIGNED_INT, 0);
			};
		}

		for (unsigned int i = 0; i < mesh.NumberOfTextures(); i++)
		{
			shader.SetUniform1i("uTexture" + std::to_string(i), i);
		}
	}

	void MeshRenderer::Render()
	{
		shader.Use();

		//shader.SetUniform4fv("uModel", parent->GetTransform()->GetDataPointer());

		for (unsigned int i = 0; i < mesh.NumberOfTextures(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, mesh.textures[i].GetID());
		}

		glBindVertexArray(mesh.GetVAO());

		draw();
	}
}
