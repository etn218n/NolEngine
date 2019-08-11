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
	//Window* win2 = new Window("Second", 200, 200);

	win1->Update();

	Texture wallTexture("./resource/textures/wall.jpg");
	Shader testShader("./resource/shaders/TestShader.gl");

	Mesh mesh(vertices, { wallTexture });
	
	MeshRenderer meshRenderer(mesh);

	GameObject* cube = new GameObject();
	cube->AddComponent<MeshRenderer>(meshRenderer);
	cube->GetTransform()->Rotate(45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

	Camera* camera = new Camera();
	camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 4.0f));

	Scene scene("Example", camera);
	scene.AddGameObject(cube);

	win1->OnUpdate = [&]() 
	{ 
		if (Input::IfKeyDown(Keycode::A))
			camera->GetTransform()->Translate(glm::vec3(-0.001f, 0.0f, 0.0f));
		else if (Input::IfKeyDown(Keycode::D))
			camera->GetTransform()->Translate(glm::vec3(0.001f, 0.0f, 0.0f));

		if (Input::IfKeyDown(Keycode::W))
			camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, -0.001f));
		else if (Input::IfKeyDown(Keycode::S))
			camera->GetTransform()->Translate(glm::vec3(0.0f, 0.0f, 0.001f));

		cube->GetTransform()->Rotate(0.01f, glm::vec3(0.0f, 1.0f, 0.0f));

		scene.Render();
	};

	while (!win1->IsClosed())
	{
		win1->Update();
	}

	Test::PressAnykey();

	return 0;
}