#include <NolEngine.h>
#include <stdlib.h> 
#include <time.h> 

using namespace Nol;

void Bar(Nol::Window* window, Keycode keycode)
{
	if (keycode == Keycode::Escape)
		window->Close();
}

const int NumberofLights = 10;
const int NumberofCubes  = 0;

struct FireFly
{
	glm::vec3 speed = glm::vec3(0.0f);
	glm::vec3 range = glm::vec3(0.0f);
	glm::vec3 angle = glm::vec3(0.0f);
};

int main()
{
	std::shared_ptr<Scene> scene = std::make_shared<Scene>("Example");

	std::vector<Light*> lights;
	lights.reserve(20);

	std::vector<FireFly> fireFlies;
	fireFlies.reserve(20);

	Engine::OnAwake.Subcribe([&]()
	{
			Engine::GameWindow()->OnKeyPressed.Subcribe(Bar);

			std::vector<float> cubeVertices = {
				/*   Position    */   /*    Normal    */    /*Texture*/
			   -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f,
				0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f,  1.0f,
				0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f,  0.0f,
				0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f,  1.0f,
			   -0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f,
			   -0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  1.0f,

			   /*   Position    */   /*    Normal    */    /*Texture*/
			  -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,
			   0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  0.0f,
			   0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  1.0f,
			   0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   1.0f,  1.0f,
			  -0.5f,  0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f,  1.0f,
			  -0.5f, -0.5f,  0.5f,   0.0f,  0.0f,  1.0f,   0.0f,  0.0f,

			  /*   Position    */   /*    Normal    */    /*Texture*/
			 -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f,  0.0f,
			 -0.5f,  0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   1.0f,  1.0f,
			 -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  1.0f,
			 -0.5f, -0.5f, -0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  1.0f,
			 -0.5f, -0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   0.0f,  0.0f,
			 -0.5f,  0.5f,  0.5f,  -1.0f,  0.0f,  0.0f,   1.0f,  0.0f,

			 /*   Position    */   /*    Normal    */    /*Texture*/
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f,  1.0f,
			 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f,  1.0f,
			 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f,  0.0f,

			 /*   Position    */   /*    Normal    */    /*Texture*/
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f,  1.0f,
			 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  1.0f,
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,
			 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,
			-0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f,  0.0f,
			-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f,  1.0f,

			/*   Position    */   /*    Normal    */    /*Texture*/
		   -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,
			0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f,  0.0f,
			0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f,  1.0f,
			0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f,  0.0f,
		   -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,
		   -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  0.0f };

			Vertex topLeft;
			topLeft.Position = glm::vec3(-1.0f, 1.0f, 0.0f);
			topLeft.Normal = glm::vec3(0.0f, 0.0f, 1.0f);

			Vertex bottomLeft;
			bottomLeft.Position = glm::vec3(-1.0f, -1.0f, 0.0f);
			bottomLeft.Normal = glm::vec3(0.0f, 0.0f, 1.0f);

			Vertex topRight;
			topRight.Position = glm::vec3(1.0f, 1.0f, 0.0f);
			topRight.Normal = glm::vec3(0.0f, 0.0f, 1.0f);

			Vertex bottomRight;
			bottomRight.Position = glm::vec3(1.0f, -1.0f, 0.0f);
			bottomRight.Normal = glm::vec3(0.0f, 0.0f, 1.0f);

			std::vector<Vertex> planeVertices = { topLeft, bottomLeft, topRight, bottomRight };

			Texture wallTexture(TextureType::Texture2D, "./resource/textures/wall.jpg");

			Shader testShader("./resource/shaders/TestShader.gl");
			Shader lightSourceShader("./resource/shaders/LightSource.gl");

			Mesh cubeMesh(cubeVertices, { wallTexture });
			Mesh planeMesh(planeVertices, { 0, 1, 2, 1, 3, 2 });

			MeshRenderer cubeMeshRenderer(cubeMesh, testShader);
			MeshRenderer lightMeshRenderer(cubeMesh, lightSourceShader);
			MeshRenderer planeMeshRenderer(planeMesh, testShader);

			srand((unsigned int)time(NULL));

			GameObject* plane = new GameObject();

			std::vector<GameObject*> cubes;
			cubes.reserve(20);

			Camera* camera = new Camera();

			for (int i = 0; i < NumberofLights; i++)
			{
				float r = (float)rand() / RAND_MAX;
				float g = (float)rand() / RAND_MAX;
				float b = (float)rand() / RAND_MAX;

				Light* light = new Light(LightType::PointLight);
				light->AddComponent<MeshRenderer>(lightMeshRenderer);
				light->SetColor(glm::vec3(r, g, b));
				light->GetTransform()->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
				light->GetComponent<MeshRenderer>()->SetUniformsFn([light](const Shader& shader)
				{
					shader.SetColor(light->Color());
				});

				FireFly fireFly;
				fireFly.range = glm::vec3((float)rand() / RAND_MAX + 4.5f, (float)rand() / RAND_MAX + 4.5f, (float)rand() / RAND_MAX + 4);
				fireFly.speed = glm::vec3((float)rand() / RAND_MAX / 50, (float)rand() / RAND_MAX / 50, (float)rand() / RAND_MAX / 50);

				lights.push_back(light);
				fireFlies.push_back(fireFly);
			}

			plane->AddComponent<MeshRenderer>(planeMeshRenderer);
			plane->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, -3.0f));
			plane->GetTransform()->Scale(glm::vec3(10.0f, 10.0f, 1.0f));

			for (int i = 0, x = -8, y = 5; i < NumberofCubes; i++)
			{
				GameObject* cube = new GameObject("Cube" + std::to_string(i));
				cube->AddComponent<MeshRenderer>(cubeMeshRenderer);

				if (i % 7 == 0 && i != 0)
				{
					x = -8;
					y = y - 2;
				}

				x = x + 2;

				cube->GetTransform()->Translate(glm::vec3(x, y, 0.0f));

				cubes.push_back(cube);
			}

			camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 13.0f));
			camera->ClearColor = glm::vec4(0.3f, 0.3f, 0.3f, 1.0f);

			GameObject* crysis = Model::GenerateModel("./resource/models/scene.fbx", testShader);

			scene->AddGameObject(crysis);

			crysis->GetTransform()->SetPosition(glm::vec3(0.0f, -4.0f, -2.0f));
			crysis->GetTransform()->Scale(glm::vec3(0.5f, 0.5f, 0.5f));

			scene->SetMainCamera(camera);
			scene->AddGameObject(plane);

			for (int i = 0; i < NumberofLights; i++)
				scene->AddGameObject(lights[i]);	

			Renderer::SetScene(scene);

			Engine::GameWindow()->SetVsync(true);
	});

	Input::OnKeyPressed.Subcribe([&lights, scene](Keycode keycode)
	{
		switch (keycode)
		{
			case Keycode::Alpha0: scene->Contain(lights[0]) ? scene->RemoveGameObject(lights[0]) : scene->AddGameObject(lights[0]); break;
			case Keycode::Alpha1: scene->Contain(lights[1]) ? scene->RemoveGameObject(lights[1]) : scene->AddGameObject(lights[1]); break;
			case Keycode::Alpha2: scene->Contain(lights[2]) ? scene->RemoveGameObject(lights[2]) : scene->AddGameObject(lights[2]); break;
			case Keycode::Alpha3: scene->Contain(lights[3]) ? scene->RemoveGameObject(lights[3]) : scene->AddGameObject(lights[3]); break;
			case Keycode::Alpha4: scene->Contain(lights[4]) ? scene->RemoveGameObject(lights[4]) : scene->AddGameObject(lights[4]); break;
			case Keycode::Alpha5: scene->Contain(lights[5]) ? scene->RemoveGameObject(lights[5]) : scene->AddGameObject(lights[5]); break;
			case Keycode::Alpha6: scene->Contain(lights[6]) ? scene->RemoveGameObject(lights[6]) : scene->AddGameObject(lights[6]); break;
			case Keycode::Alpha7: scene->Contain(lights[7]) ? scene->RemoveGameObject(lights[7]) : scene->AddGameObject(lights[7]); break;
			case Keycode::Alpha8: scene->Contain(lights[8]) ? scene->RemoveGameObject(lights[8]) : scene->AddGameObject(lights[8]); break;
			case Keycode::Alpha9: scene->Contain(lights[9]) ? scene->RemoveGameObject(lights[9]) : scene->AddGameObject(lights[9]); break;
		}
	});

	

	Engine::OnUpdate.Subcribe([&]() 
	{ 
		if (Input::IfKeyPressed(Keycode::F1))
			Engine::GameWindow()->SetVsync(!Engine::GameWindow()->IsVsyncEnabled());
	});

	Engine::OnFixedUpdate.Subcribe([&]()
	{
		for (int i = 0; i < NumberofLights; i++)
		{
			float x = glm::cos(fireFlies[i].angle.x) * fireFlies[i].range.x;
			float y = glm::sin(fireFlies[i].angle.y) * fireFlies[i].range.y;
			float z = glm::sin(fireFlies[i].angle.z) * fireFlies[i].range.z;

			fireFlies[i].angle += fireFlies[i].speed;

			lights[i]->GetTransform()->SetPosition(glm::vec3(x, y, z));
		}
	});

	Engine::Start();

	return 0;
}