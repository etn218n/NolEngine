#include <NolEngine.h>

using namespace Nol;

void Bar(Nol::Window* window, Keycode keycode)
{
	if (keycode == Keycode::Escape)
		window->Close();
}

int main()
{
	std::vector<float> vertices = {
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

	Log::Init();

	Window* win1 = new Window("First", 800, 600);
	win1->SetBackgroundColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));

	win1->Update();

	Texture wallTexture("./resource/textures/wall.jpg");
	Shader testShader("./resource/shaders/TestShader.gl");
	Shader lightSourceShader("./resource/shaders/LightSource.gl");

	Mesh mesh(vertices, { wallTexture });
	
	MeshRenderer meshRenderer(mesh, testShader);
	MeshRenderer lightMeshRenderer(mesh, lightSourceShader);

	std::shared_ptr<Light> pointLight = std::make_shared<Light>();
	pointLight->AddComponent<MeshRenderer>(lightMeshRenderer);
	pointLight->GetTransform()->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	pointLight->GetComponent<MeshRenderer>()->SetUniformsFn([&pointLight](const Shader& shader)
	{
		shader.SetUniform4f("uColor", pointLight->Color());
	});

	std::shared_ptr<GameObject> cube = std::make_shared<GameObject>("Cube");
	cube->AddComponent<MeshRenderer>(meshRenderer);
	cube->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 0.0f));
	cube->GetTransform()->Rotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	std::shared_ptr<GameObject> cube2 = std::make_shared<GameObject>("Cube2");
	cube2->AddComponent<MeshRenderer>(meshRenderer);
	cube2->GetTransform()->Translate(glm::vec3(0.0f, 1.0f, -5.0f));

	std::shared_ptr<Camera> camera = std::make_shared<Camera>();
	camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 4.0f));

	std::shared_ptr<Scene> scene = std::make_shared<Scene>("Example");
	scene->SetLight(pointLight);
	scene->SetCamera(camera);
	scene->AddGameObject(cube);
	scene->AddGameObject(cube2);
	scene->AddGameObject(pointLight);
	
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
			pointLight->SetColor(glm::vec4(0.9f, 0.3f, 0.3f, 1.0f));

		//cube->GetTransform()->Rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));

		float lightPosX = glm::cos(Time::Now()) * 2.0f;
		float lightPosZ = glm::sin(Time::Now()) * 2.0f;

		pointLight->GetTransform()->SetPosition(glm::vec3(lightPosX, 0.0f, lightPosZ));

		renderer.Update();
	});

	while (!win1->IsClosed())
	{
		win1->Update();
	}

	Test::PressAnykey();

	return 0;
}