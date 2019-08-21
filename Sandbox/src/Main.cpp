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

	GameObject* plane = new GameObject();
	plane->AddComponent<MeshRenderer>(planeMeshRenderer);
	plane->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, -3.0f));
	plane->GetTransform()->Scale(glm::vec3(5.0f, 5.0f, 5.0f));

	Light* light = new Light(LightType::PointLight);
	light->AddComponent<MeshRenderer>(lightMeshRenderer);
	light->SetColor(glm::vec3(1.0f, 0.0f, 0.0f));
	light->GetTransform()->Rotate(180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	light->GetTransform()->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light->GetComponent<MeshRenderer>()->SetUniformsFn([&light](const Shader& shader)
	{
		shader.SetUniformVec4("uColor", light->Color());
	});

	Light* light2 = new Light(LightType::PointLight);
	light2->AddComponent<MeshRenderer>(lightMeshRenderer);
	light2->SetColor(glm::vec3(1.0f, 1.0f, 1.0f));
	light2->GetTransform()->Rotate(180.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	light2->GetTransform()->Scale(glm::vec3(0.1f, 0.1f, 0.1f));
	light2->GetComponent<MeshRenderer>()->SetUniformsFn([&light2](const Shader& shader)
	{
		shader.SetUniformVec4("uColor", light2->Color());
	});

	GameObject* cube = new GameObject("Cube");
	cube->AddComponent<MeshRenderer>(cubeMeshRenderer);
	cube->GetTransform()->Rotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	Camera* camera = new Camera();
	camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 5.0f));

	std::shared_ptr<Scene> scene = std::make_shared<Scene>("Example");
	scene->SetMainCamera(camera);
	//scene->AddGameObject(cube);
	scene->AddGameObject(light2);
	scene->AddGameObject(light);
	
	scene->AddGameObject(plane);
	
	Renderer renderer(scene);

	Test::LoadModel("./resource/models/scene.fbx");

	win1->OnUpdate.Subcribe([&](Window* window) 
	{ 
		if (Input::IfKeyDown(Keycode::A))
			light->GetTransform()->Translate(glm::vec3(-0.001f, 0.0f, 0.0f));
		else if (Input::IfKeyDown(Keycode::D))
			light->GetTransform()->Translate(glm::vec3(0.001f, 0.0f, 0.0f));

		if (Input::IfKeyDown(Keycode::W))
			camera->GetTransform()->Rotate(0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
		else if (Input::IfKeyDown(Keycode::S))
			camera->GetTransform()->Rotate(-0.1f, glm::vec3(1.0f, 0.0f, 0.0f));
			
		if (Input::IfKeyPressed(Keycode::Alpha1))
			scene->RemoveGameObject(light);
		else if (Input::IfKeyDown(Keycode::Alpha2))
			light->SetType(LightType::SpotLight);
		else if (Input::IfKeyDown(Keycode::Alpha3))
			light->SetType(LightType::DirectionalLight);

		cube->GetTransform()->Rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));

		float lightPosX = glm::cos(Time::Now()) * 2.0f;
		float lightPosZ = glm::sin(Time::Now()) * 2.0f;

		light->GetTransform()->SetPosition(glm::vec3(lightPosX, 0.0f, lightPosZ));
		light2->GetTransform()->SetPosition(glm::vec3(-lightPosX, 0.0f, -lightPosZ));

		renderer.Update();
	});

	while (!win1->IsClosed())
	{
		win1->Update();
	}

	Test::PressAnykey();

	return 0;
}