#include <NolEngine.h>

using namespace Nol;

void Bar(Nol::Window* window, Keycode keycode)
{
	if (keycode == Keycode::Escape)
		window->Close();
}

int main()
{
	std::vector<float> cubeVertices = {
     /*   Position    */   /*    Normal    */    /*Texture*/
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,   0.0f,  0.0f, -1.0f,   0.0f,  0.0f,

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
	 0.5f,  0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,   1.0f,  0.0f,  0.0f,   0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,   1.0f,  0.0f,  0.0f,   1.0f,  0.0f,

	 /*   Position    */   /*    Normal    */    /*Texture*/
	-0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,   0.0f, -1.0f,  0.0f,   0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,   0.0f, -1.0f,  0.0f,   0.0f,  1.0f,

	 /*   Position    */   /*    Normal    */    /*Texture*/
	-0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,   0.0f,  1.0f,  0.0f,   0.0f,  1.0f };

	Vertex topLeft;
	topLeft.Position = glm::vec3(-1.0f, 1.0f, 0.0f);
	topLeft.Normal   = glm::vec3(0.0f, 0.0f, 1.0f);

	Vertex bottomLeft;
	bottomLeft.Position = glm::vec3(-1.0f, -1.0f, 0.0f);
	bottomLeft.Normal   = glm::vec3(0.0f, 0.0f, 1.0f);

	Vertex topRight;
	topRight.Position = glm::vec3(1.0f, 1.0f, 0.0f);
	topRight.Normal   = glm::vec3(0.0f, 0.0f, 1.0f);

	Vertex bottomRight;
	bottomRight.Position = glm::vec3(1.0f, -1.0f, 0.0f);
	bottomRight.Normal   = glm::vec3(0.0f, 0.0f, 1.0f);

	std::vector<Vertex> planeVertices = { topLeft, topRight, bottomLeft, bottomRight };

	Log::Init();

	Window* win1 = new Window("First", 800, 600);
	win1->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	win1->Update();

	Texture wallTexture("./resource/textures/wall.jpg");
	Shader testShader("./resource/shaders/TestShader.gl");
	Shader lightSourceShader("./resource/shaders/LightSource.gl");

	Mesh cubeMesh(cubeVertices, { wallTexture });
	Mesh planeMesh(planeVertices, { 0, 1, 2, 1, 2, 3 }, { });
	
	MeshRenderer cubeMeshRenderer(cubeMesh, testShader);
	MeshRenderer lightMeshRenderer(cubeMesh, lightSourceShader);
	MeshRenderer planeMeshRenderer(planeMesh, testShader);

	std::shared_ptr<GameObject> plane = std::make_shared<GameObject>();
	plane->AddComponent<MeshRenderer>(planeMeshRenderer);
	plane->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, -2.0f));
	plane->GetTransform()->Scale(glm::vec3(5.0f, 5.0f, 5.0f));
	plane->GetComponent<MeshRenderer>()->SetUniformsFn([](const Shader& shader)
	{
		shader.SetUniform4f("uColor", glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	});

	std::shared_ptr<Light> light = std::make_shared<Light>();
	light->AddComponent<MeshRenderer>(lightMeshRenderer);
	light->GetTransform()->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->GetComponent<MeshRenderer>()->SetUniformsFn([&light](const Shader& shader)
	{
		shader.SetUniform4f("uColor", light->Color());
	});

	std::shared_ptr<GameObject> cube = std::make_shared<GameObject>("Cube");
	cube->AddComponent<MeshRenderer>(cubeMeshRenderer);
	cube->GetTransform()->Rotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 4.0f));

	std::shared_ptr<Scene> scene = std::make_shared<Scene>("Example");
	scene->SetLight(light);
	scene->SetCamera(camera);
	//scene->AddGameObject(cube);
	scene->AddGameObject(light);
	scene->AddGameObject(plane);
	
	Renderer renderer(scene);

	win1->OnUpdate.Subcribe([&](Window* window) 
	{ 
		if (Input::IfKeyDown(Keycode::A))
			camera->GetTransform()->Translate(glm::vec3(-0.001f, 0.0f, 0.0f));
		else if (Input::IfKeyDown(Keycode::D))
			camera->GetTransform()->Translate(glm::vec3(0.001f, 0.0f, 0.0f));

		if (Input::IfKeyDown(Keycode::W))
			camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, -0.001f));
		else if (Input::IfKeyDown(Keycode::S))
			camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 0.001f));

		if (Input::IfKeyPressed(Keycode::P))
			light->SetColor(glm::vec4(0.9f, 0.3f, 0.3f, 1.0f));

		//cube->GetTransform()->Rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));

		float lightPosX = glm::cos(Time::Now()) * 2.0f;
		float lightPosZ = glm::sin(Time::Now()) * 2.0f;

		light->GetTransform()->SetPosition(glm::vec3(lightPosX, 0.0f, lightPosZ));

		renderer.Update();
	});

	while (!win1->IsClosed())
	{
		win1->Update();
	}

	Test::PressAnykey();

	return 0;
}