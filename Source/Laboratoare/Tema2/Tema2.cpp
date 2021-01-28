#include "Tema2.h"
#include <Core/Engine.h>
#include <windows.h>

using namespace std;

Player player(2.0f, 2.5f, 0);
std::vector<Platform> platforms(168);
std::vector<Tetrahedron> tetra(100);
const string textureLoc = "Source/Laboratoare/Tema2/Textures/";
CombustibilBar* combustibilBar;

Tema2::Tema2() {
}

Tema2::~Tema2() {
}

void Tema2::Init() {
	renderCameraTarget = false;

	camera = new CameraTema2::Camera();
	camera->Set(glm::vec3(2, 4.7f, 3), glm::vec3(2, 1.5f, -2), glm::vec3(0, 1, 0));
	Platform p;
	Tetrahedron t;
	AddMeshToList(player.createPlayer("player"));
	AddMeshToList(p.createPlatform("platform"));
	AddMeshToList(t.createTetrahedron("tetrahedron"));

	Mesh* background = new Mesh("background");
	background->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");
	AddMeshToList(background);

	// Load textures
	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "platform_texture.jpg").c_str(), GL_CLAMP_TO_BORDER);
		mapTextures["ground"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "tetra_text1.jpg").c_str(), GL_REPEAT);
		mapTextures["tetra"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "player_text.jpg").c_str(), GL_REPEAT);
		mapTextures["player"] = texture;
	}

	{
		Texture2D* texture = new Texture2D();
		texture->Load2D((textureLoc + "back.jpg").c_str(), GL_REPEAT);
		mapTextures["background"] = texture;
	}

	combustibilBar = new CombustibilBar();
	clockTime = std::clock();

	/* INITIALIZAREA DE PLATFORME */
	for (int i = 0; i < platforms.size(); i++) {
		int aux = i % platformsPerTour;
		switch (aux) {
		case 0:
			platforms[i].x = 0.0f;
			platforms[i].color = BLUE;

			break;
		case 1:
			platforms[i].x = 2.0f;
			platforms[i].color = BLUE;
			break;
		case 2:
			platforms[i].x = 4.0f;
			platforms[i].color = BLUE;
			break;
		}
	}

	for (int i = 0; i < tetra.size() / 2; i++) {
		tetra[i].x = -3;
		tetra[i].z = (-3) * i;
	}

	int c = 0;
	for (int i = tetra.size() / 2; i < tetra.size(); i++) {
		tetra[i].x = 6;
		tetra[i].z = (-3) * c;
		c++;
	}

	projectionMatrix = glm::perspective(RADIANS(60), window->props.aspectRatio, 0.01f, 200.0f);
	{
		Shader* shader = new Shader("ShaderTema2");
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/VertexShader.glsl", GL_VERTEX_SHADER);
		shader->AddShader("Source/Laboratoare/Tema2/Shaders/FragmentShader.glsl", GL_FRAGMENT_SHADER);
		shader->CreateAndLink();
		shaders[shader->GetName()] = shader;
	}
}


void Tema2::FrameStart() {
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema2::generatePlatforms(glm::mat4 modelMatrix) {
	/* simulez o matrice de platforme */
	for (int i = 0; i < platforms.size(); i = i + platformsPerTour) {
		// daca platforma nu este folosita
		if (platforms[i].ready) {
			int j;
			// daca este prima data cand se porneste jocul
			if (started == 1) {
				/* generez primele platformsPerTour platforme la pozitia intiala,
				* si pe restul tindand cont de cele 3 generate
				* altfel generez doar tinand cont de celelalte platforme
				*/
				started = 0;
				for (j = i; j < platformsPerTour; j++) {
					platforms[j].generatePlatform(modelMatrix, platformStartPos, true);
				}
				continue;
			}

			/* altfel trebuie sa le generez in functie de ultima platforma generata
			* edge case-ul ar fi ca prima platforma va trebui sa ia datele de la ultima
			*/
			for (j = i; j < i + platformsPerTour; j++) {
				int randomNum = rand() % 5;
				/* daca este prima platforma, va trebui sa iau datele de la ultimele platforme generate */
				if (i == 0) {
					// z-ul ultimei plaftorme randate - lungimea platformei
					Platform frontPlatform = platforms[platforms.size() - platformsPerTour + j];
					platforms[j].generatePlatform(modelMatrix, frontPlatform.z - (0.5 * frontPlatform.scaleZ), false);
					/* altfel trebuie sa iau datele de la platformele de dinaintea mea*/
				}
				else {
					Platform frontPlatform = platforms[j - platformsPerTour];
					// z-ul ultimei plaftorme randate - lungimea platformei
					platforms[j].generatePlatform(modelMatrix, frontPlatform.z - (0.5 * frontPlatform.scaleZ), false);
				}
			}
			break;
		}
	}
}

void Tema2::Update(float deltaTimeSeconds) {



	modelMatrix = glm::mat4(1);

	for (int i = 0; i < tetra.size(); i++) {
		tetra[i].move(deltaTimeSeconds);
		RenderMesh(meshes["tetrahedron"], shaders["ShaderTema2"], tetra[i].modelMatrix, GREEN, mapTextures["tetra"], nullptr);
	}

	modelMatrix *= Transform3D::Translate(0, 0, 0);
	modelMatrix *= Transform3D::Scale(150, 150, 150);
	RenderMesh(meshes["background"], shaders["ShaderTema2"], modelMatrix, GRAY, mapTextures["background"], nullptr);

	modelMatrix = glm::mat4(1);
	generatePlatforms(modelMatrix);
	modelMatrix = glm::mat4(1);

	score += deltaTimeSeconds * 10;
	std::cout << "Score is : " << score << endl;

	if (gameOver == 1) {
		std::cout << "GAME OVER! Score is: " << score << std::endl;
		Sleep(1000);
		exit(0);
	}

	duration = (std::clock() - clockTime) / (double)CLOCKS_PER_SEC;
	if (duration >= 3 && blockSpeed == 1) {
		speed = 9;
		blockSpeed = 0;
	}

	RenderPlatforms(deltaTimeSeconds);
	/*  */
	int currentPlatform = checkCollision();
	if (currentPlatform >= 0 || player.isBack == 0) {
		platformPowerups(currentPlatform);
		RenderPlayer(deltaTimeSeconds);
	} else {
		player.y -= deltaTimeSeconds * 3;
		RenderPlayer(deltaTimeSeconds);
	}

}

/* return position of platform */
int Tema2::checkCollision() {
	player.onPlatform = false;
	int currentPlatform = -1;
	for (int i = 0; i < platforms.size(); i++) {
		float dist_squared = 0.5 * 0.5;

		if (((player.x - (player.height / 2)) <= platforms[i].x + 0.5 &&
			 (player.x + (player.height / 2)) >= platforms[i].x - 0.5) &&

			((player.y - player.height / 2) <= platforms[i].y + (0.5 * 0.1) &&
			 (player.y + 0.5) >= platforms[i].y - (0.5 * .1)) &&

			((player.z - player.height / 2) <= platforms[i].z + (0.5 * platforms[i].scaleZ) &&
			 (player.z + 0.5) >= platforms[i].z - (0.5 * platforms[i].scaleZ))) {
			player.onPlatform = true;
			currentPlatform = i;
		}
	}
	return currentPlatform;
}

void Tema2::platformPowerups(int currentPlatform) {

	if (player.onPlatform) {
		if (platforms[currentPlatform].color == RED) {
			speed = 0;
			gameOver = 1;
			playerDeformation = 1;
		
		} else if (platforms[currentPlatform].color == YELLOW) {

			gas -= (25.0 / 100.0) * gas;
			playerDeformation = 1;
		
		} else if (platforms[currentPlatform].color == ORANGE) {
			
			blockSpeed = 1;
			speed = 10;
			clockTime = std::clock();
			playerDeformation = 1;
		
		} else if (platforms[currentPlatform].color == GREEN) {
			
			gas += (25.0 / 100.0) * 40;

			if (gas > 40) {
				gas = 40;
			}
			playerDeformation = 1;
		}
		else if (platforms[currentPlatform].color == BLUE) {
			
			playerDeformation = 0;
		}

		platforms[currentPlatform].color = VIOLET;

	} else {
		playerDeformation = 0;
	}
}

void Tema2::RenderPlatforms(float deltaTimeSeconds) {

	/* daca platformele sunt */
	for (int i = 0; i < platforms.size(); i++) {
		
		if (!platforms[i].ready) {
			platforms[i].move(deltaTimeSeconds, speed);
			if (platforms[i].z < PLATFORM_DESTRUCTION) {
				RenderMesh(meshes["platform"], shaders["ShaderTema2"], platforms[i].modelMatrix, platforms[i].color, mapTextures["ground"], nullptr);
			}
		}
	}

	modelMatrix = glm::mat4(1);

	/* check gas */
	gas -= deltaTimeSeconds * speed / 20;
	if (gas <= 0) {
		gas = 0;
		speed = 0;
	}

	if (combustibilPos.w == 15) {
		modelMatrix *= Transform3D::Translate(combustibilPos.x, combustibilPos.y, combustibilPos.z);
		modelMatrix *= Transform3D::RotateOX(combustibilPos.w);
		modelMatrix *= Transform3D::Scale(0.01f, 0.01f, 0.01f);
		RenderMesh(combustibilBar->GetCombustibilBar(), shaders["ShaderTema2"], modelMatrix, GREEN, nullptr, nullptr);

		modelMatrix *= Transform3D::Scale(gas, 1, 1);
		RenderMesh(combustibilBar->GetPowerLine(), shaders["ShaderTema2"], modelMatrix, GRAY, nullptr, nullptr);
	}
	else {
		modelMatrix *= Transform3D::Translate(4, 3.32, 3.12);
		modelMatrix *= Transform3D::RotateOY(45);
		modelMatrix *= Transform3D::RotateOX(3);
		modelMatrix *= Transform3D::Scale(0.01f, 0.01f, 0.01f);
		RenderMesh(combustibilBar->GetCombustibilBar(), shaders["ShaderTema2"], modelMatrix, GREEN, nullptr, nullptr);

		modelMatrix *= Transform3D::Scale(gas, 1, 1);
		RenderMesh(combustibilBar->GetPowerLine(), shaders["ShaderTema2"], modelMatrix, GRAY, nullptr, nullptr);
	}
}

void Tema2::RenderPlayer(float deltaTimeSeconds) {
	/* move player */
	player.move(deltaTimeSeconds);

	/* daca playerul nu a cazul de pe plaforma, il randez normal */
	if (player.y >= 2) {

		modelMatrix = glm::mat4(1);
		rotateAngle -= deltaTimeSeconds * speed;
		modelMatrix *= Transform3D::Translate(player.x, player.y, player.z);
		modelMatrix *= Transform3D::RotateOX(rotateAngle);

		RenderMesh(meshes["player"], shaders["ShaderTema2"], modelMatrix, glm::vec3(1, 1, 0), mapTextures["player"], nullptr);
	/* altfel il scalez cu 0.1 si il las sa cada, setez flagul de gameOver */
	} else {
		modelMatrix = glm::mat4(1);
		rotateAngle -= deltaTimeSeconds * speed;
		modelMatrix *= Transform3D::Translate(player.x, player.y, player.z);
		modelMatrix *= Transform3D::Scale(0.5f, 0.2f, 0.8f);
		modelMatrix *= Transform3D::RotateOX(rotateAngle);

		RenderMesh(meshes["player"], shaders["ShaderTema2"], modelMatrix, glm::vec3(1, 1, 0), mapTextures["player"], nullptr);
		gameOver = 1;
	}
}

void Tema2::FrameEnd() {
	// DrawCoordinatSystem(camera->GetViewMatrix(), projectionMatrix);
}

void Tema2::RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Texture2D *texture1, Texture2D* texture2) {
	if (!mesh || !shader || !shader->GetProgramID())
		return;

	glUseProgram(shader->program);
	if (mesh == meshes["player"]) {
		if (playerDeformation == 1 || blockSpeed == 1) {
			GLint deformation = glGetUniformLocation(shader->GetProgramID(), "deformation");
			glUniform1i(deformation, 1);
		} else {
			GLint deformation = glGetUniformLocation(shader->GetProgramID(), "deformation");
			glUniform1i(deformation, 2);
		}

	} else if (mesh == meshes["tetrahedron"]) {
		glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), true);
		GLint deformation = glGetUniformLocation(shader->GetProgramID(), "deformation");
		glUniform1i(deformation, 0);
	} else {
		GLint deformation = glGetUniformLocation(shader->GetProgramID(), "deformation");
		glUniform1i(deformation, 0);
		glUniform3fv(glGetUniformLocation(shader->program, "object_color"), 1, glm::value_ptr(color));
		glUniform1i(glGetUniformLocation(shader->program, "mix_textures"), false);

	}

	GLint modelLocation = glGetUniformLocation(shader->GetProgramID(), "Model");
	glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(modelMatrix));

	GLint viewLocation = glGetUniformLocation(shader->GetProgramID(), "View");
	glm::mat4 viewMatrix = camera->GetViewMatrix();
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));

	GLint projLocation = glGetUniformLocation(shader->GetProgramID(), "Projection");
	glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
	glUniformMatrix4fv(projLocation, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	if (texture1) {
		// activate texture location 0
		glActiveTexture(GL_TEXTURE0);
		// bind the texture ID
		glBindTexture(GL_TEXTURE_2D, texture1->GetTextureID());
		// send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_1"), 0);
	}

	if (texture2) {
		//activate texture location 1
		glActiveTexture(GL_TEXTURE1);
		//TODO : Bind the texture2 ID
		glBindTexture(GL_TEXTURE_2D, texture2->GetTextureID());
		//TODO : Send texture uniform value
		glUniform1i(glGetUniformLocation(shader->program, "texture_2"), 1);
	}

	glBindVertexArray(mesh->GetBuffers()->VAO);
	glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_SHORT, 0);
}


void Tema2::OnInputUpdate(float deltaTime, int mods) {
	// move the camera only if MOUSE_RIGHT button is pressed
	float cameraSpeed = 2.0f;

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		if (window->KeyHold(GLFW_KEY_W)) {
			// translate the camera forward
			camera->TranslateForward(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_A)) {
			// translate the camera to the left
			camera->TranslateRight(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_S)) {
			// translate the camera backwards
			camera->TranslateForward(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_D)) {
			// translate the camera to the right
			camera->TranslateRight(deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_Q)) {
			// translate the camera down
			camera->TranslateUpword(-deltaTime * cameraSpeed);
		}

		if (window->KeyHold(GLFW_KEY_E)) {
			// translate the camera up
			camera->TranslateUpword(deltaTime * cameraSpeed);
		}
	} else {
		if (window->KeyHold(GLFW_KEY_W)) {
			if (speed <= PLATFORM_MAX_SPEED && blockSpeed == 0 && gameOver == 0)
				speed += deltaTime * 10;
		}
	}

}

void Tema2::OnKeyPress(int key, int mods) {

	if (!window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {

		if (key == GLFW_KEY_A) {
			if (player.x == 2) {
				player.x = 0;
			}
			else if (player.x == 4) {
				player.x = 2;
			}
		}

		if (key == GLFW_KEY_D) {
			if (player.x == 0) {
				player.x = 2;
			} else if (player.x == 2) {
				player.x = 4;
			}
		}
		if (key == GLFW_KEY_S) {
			if (speed >= .02f && blockSpeed == 0 && gameOver == 0)
				speed -= 1;
		}

		if (key == GLFW_KEY_SPACE) {
			if (player.isBack == 1 && player.y >= 2 && speed > 0.01f) {
				player.ascension = 1;
				player.isBack = 0;
			} else if (player.y < 2) {
				speed = 0;
			}

		}
	}
	if (key == GLFW_KEY_C) {
		if (firstPerson == 1) {
			camera->Set(glm::vec3(5, 4, 3), glm::vec3(0, 1, -2), glm::vec3(0, 1, 0));
			firstPerson = 0;
			combustibilPos = glm::vec4(5, 3, 2.1, 20);

		}
		else {
			// camera->Set(glm::vec3(player.x, player.y, player.z - 0.5), glm::vec3(2, 2, -2), glm::vec3(0, 1, 0));
			firstPerson = 1;
			// combustibilPos = glm::vec4(1.05, 3, 2.1, 15);

		}
	}

}

void Tema2::OnKeyRelease(int key, int mods) {
	// add key release event
}

void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
	// add mouse move event

	if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT)) {
		float sensivityOX = 0.001f;
		float sensivityOY = 0.001f;

		if (window->GetSpecialKeyState() == 0) {
			renderCameraTarget = false;
			// rotate the camera in First-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			xCameraCoord = sensivityOX * -deltaY;
			yCameraCoord = sensivityOY * -deltaX;

			camera->RotateFirstPerson_OX(sensivityOX * -deltaY);
			camera->RotateFirstPerson_OY(sensivityOY * -deltaX);
		}

		if (window->GetSpecialKeyState() && GLFW_MOD_CONTROL) {
			renderCameraTarget = true;
			// rotate the camera in Third-person mode around OX and OY using deltaX and deltaY
			// use the sensitivity variables for setting up the rotation speed
			camera->RotateThirdPerson_OX(sensivityOX * -deltaY);
			camera->RotateThirdPerson_OY(sensivityOY * -deltaX);
		}

	}
}

void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
	// add mouse button press event
}

void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
	// add mouse button release event
}

void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
}

void Tema2::OnWindowResize(int width, int height) {
}