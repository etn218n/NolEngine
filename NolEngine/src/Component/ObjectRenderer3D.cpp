#include "PCH.h"
#include "ObjectRenderer3D.h"

namespace Nol
{
	ObjectRenderer3D::ObjectRenderer3D(std::shared_ptr<Shader> shader, std::shared_ptr<Mesh> mesh, std::shared_ptr<Material> material) :
		shader(shader), mesh(mesh), material(material)
	{
		if (mesh->NumberofIndices() == 0)
		{
			drawFn = std::bind(&ObjectRenderer3D::DrawArray, this);
		}
		else
		{
			drawFn = std::bind(&ObjectRenderer3D::DrawElement, this);
		}
	}

	void ObjectRenderer3D::DrawArray()
	{
		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)mesh->NumberofVertices());
	}

	void ObjectRenderer3D::DrawElement()
	{
		glDrawElements(GL_TRIANGLES, (GLsizei)mesh->NumberofIndices(), GL_UNSIGNED_INT, 0);
	}
}
