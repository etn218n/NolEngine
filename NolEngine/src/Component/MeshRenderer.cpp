#include "PCH.h"
#include "MeshRenderer.h"

namespace Nol
{
	MeshRenderer::MeshRenderer(Mesh& mesh) : mesh(mesh)
	{
		if (mesh.NumberOfIndices() == 0)
		{
			renderSelector = [&](void)
			{
				glDrawArrays(GL_TRIANGLES, 0, mesh.NumberOfVertices());
			};
		}
		else
		{
			renderSelector = [&](void)
			{
				glDrawElements(GL_TRIANGLES, mesh.NumberOfIndices(), GL_UNSIGNED_INT, 0);
			};
		}
	}

	MeshRenderer::MeshRenderer(Mesh& mesh, Shader& shader) : mesh(mesh), shader(shader)
	{
		if (mesh.NumberOfIndices() == 0)
		{
			renderSelector = [&](void) 
			{
				glDrawArrays(GL_TRIANGLES, 0, mesh.NumberOfVertices());
			};
		}
		else
		{
			renderSelector = [&](void)
			{
				glDrawElements(GL_TRIANGLES, mesh.NumberOfIndices(), GL_UNSIGNED_INT, 0);
			};
		}
	}
}
