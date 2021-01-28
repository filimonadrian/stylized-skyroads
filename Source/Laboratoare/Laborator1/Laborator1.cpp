#include "Laborator1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include <time.h>

using namespace std;

string randomObject;
// for background change: press f
// for random object: press c
// hold LEFT_SHIFT and press W A S D Q E to move the object(continuos move)
// hold LEFT_CTRL and press W A S D Q E to mvoe the object one position


// Order of function calling can be seen in "Source/Core/World.cpp::LoopUpdate()"
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/World.cpp

Laborator1::Laborator1()
{
}

Laborator1::~Laborator1()
{
}

void Laborator1::Init()
{
	// Load a mesh from file into GPU memory
	{
		Mesh* mesh = new Mesh("box");
		mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");

		Mesh* mesh2 = new Mesh("sphere");
		mesh2->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");

		Mesh* mesh3 = new Mesh("teapot");
		mesh3->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "teapot.obj");

		meshes[mesh->GetMeshID()] = mesh;
		meshes[mesh2->GetMeshID()] = mesh2;
		meshes[mesh3->GetMeshID()] = mesh3;

	}
}

void Laborator1::FrameStart()
{

}

void Laborator1::Update(float deltaTimeSeconds)
{
	glm::ivec2 resolution = window->props.resolution;

	// sets the clear color for the color buffer
	if (keyPressed) {
		glClearColor(255, 100, 0, 2);
	}
	else {
		glClearColor(0, 0, 0, 1);
	}

	// clears the color buffer (using the previously set color) and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);

	// render the object
	RenderMesh(meshes["box"], glm::vec3(1, 0.5f, 0), glm::vec3(0.5f));

	// render the object again but with different properties
	RenderMesh(meshes["box"], glm::vec3(-1, 0.5f, 0));

	// render a new sphere
	RenderMesh(meshes["sphere"], glm::vec3(2, 1, 0), glm::vec3(1));

	// render a new teapot
	RenderMesh(meshes["teapot"], glm::vec3(-2, 1, 0), glm::vec3(0.5f));

	// render a random object
	RenderMesh(meshes[randomObject], glm::vec3(0, 2, 0), glm::vec3(0.5f));

	// render object that will move
	RenderMesh(meshes["sphere"], glm::vec3(x, y, z), glm::vec3(0.5f));

}

void Laborator1::FrameEnd()
{
	DrawCoordinatSystem();
}

// Read the documentation of the following functions in: "Source/Core/Window/InputController.h" or
// https://github.com/UPB-Graphics/Framework-EGC/blob/master/Source/Core/Window/InputController.h

void Laborator1::OnInputUpdate(float deltaTime, int mods)
{
	if (!window->KeyHold(GLFW_KEY_LEFT_CONTROL) && window->KeyHold(GLFW_KEY_LEFT_SHIFT)) {
		moveObject(deltaTime, 2);
	}
};

void Laborator1::OnKeyPress(int key, int mods)
{
	vector<string> random_objects;
	random_objects.push_back("box");
	random_objects.push_back("sphere");
	random_objects.push_back("teapot");
	
	if (window->KeyHold(GLFW_KEY_LEFT_CONTROL)) {
		moveObject(1, 1);
	} else {
		// add key press for backround color
		if (key == GLFW_KEY_F) {
			keyPressed = (keyPressed == true) ? false : true;

		} // add key press for random changing objects
		else if (key == GLFW_KEY_C) {
			srand(time(NULL));
			int r = rand() % 3;
			randomObject = random_objects[r];
		}
	}
};

void Laborator1::moveObject(float deltaTime, int speed) {
	if (window->KeyHold(GLFW_KEY_W)) {
		z = z - deltaTime * speed;
	}
	if (window->KeyHold(GLFW_KEY_S)) {
		z = z + deltaTime * speed;
	}
	if (window->KeyHold(GLFW_KEY_D)) {
		x = x + deltaTime * speed;
	}
	if (window->KeyHold(GLFW_KEY_A)) {
		x = x - deltaTime * speed;
	}
	if (window->KeyHold(GLFW_KEY_Q)) {
		y = y - deltaTime * speed;
	}
	if (window->KeyHold(GLFW_KEY_E)) {
		y = y + deltaTime * speed;
	}
}

void Laborator1::OnKeyRelease(int key, int mods)
{
	// add key release event
};

void Laborator1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
	// add mouse move event
};

void Laborator1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button press event
};

void Laborator1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Laborator1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
	// treat mouse scroll event
}

void Laborator1::OnWindowResize(int width, int height)
{
	// treat window resize event
}
