#include "PCH.h"
#include "Test.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <conio.h>

namespace Nol
{
	Observable<> Test::OnEnterLoop;

	void Test::LogKeyPress(Window* window, Keycode keycode)	  { INFO("(Window \"{0}\") Key {1} pressed.", window->GetTitle(), (int)keycode);  }
	void Test::LogKeyHold(Window* window, Keycode keycode)	  { INFO("(Window \"{0}\") Key {1} held.", window->GetTitle(), (int)keycode);	  }
	void Test::LogKeyRelease(Window* window, Keycode keycode) { INFO("(Window \"{0}\") Key {1} released.", window->GetTitle(), (int)keycode); }

	void Test::LogMousePress(Window * window, Keycode keycode)   { INFO("(Window \"{0}\") Mouse button {1} pressed.",  window->GetTitle(), (int)keycode); }
	void Test::LogMouseRelease(Window * window, Keycode keycode) { INFO("(Window \"{0}\") Mouse button {1} released.", window->GetTitle(), (int)keycode); }

	void Test::SetupLogEventFor(Window* window)
	{
		window->OnKeyPressed.Subcribe(LogKeyPress);
		window->OnKeyHold.Subcribe(LogKeyHold);
		window->OnKeyReleased.Subcribe(LogKeyRelease);

		window->OnMousePressed.Subcribe(LogMousePress);
		window->OnMouseReleased.Subcribe(LogMouseRelease);
	}

	void Test::InfiniteLoop()
	{
		INFO("Enter Infinite Loop.");

		OnEnterLoop.Publish();

		while (true);
	}

	void Test::PressAnykey()
	{
		_getch();
	}

	void Test::LoadModel(const std::string& filePath)
	{
		Assimp::Importer import;
		const aiScene *scene = import.ReadFile(filePath, aiProcess_Triangulate | aiProcess_FlipUVs);

		if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		{
			ERR("ERROR::ASSIMP::{0}", import.GetErrorString());
			return;
		}

		INFO("{0}", scene->mNumMeshes);
	}
}
