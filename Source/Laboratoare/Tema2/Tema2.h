#pragma once

#include <vector>
#include <iostream>
#include <Component/SimpleScene.h>
#include <Laboratoare\Tema2\LabCamera.h>
#include <Laboratoare\Tema2\Transform3D.h>
#include <vector>
#include <cstdio>
#include <ctime>
#include "Player.h"
#include <cmath>
#include "Platform.h"
#include <Component/SimpleScene.h>
#include <Core/GPU/Mesh.h>
#include <string>

#include "CombustibilBar.h"
#include "Limits.h"
#include "Tetrahedron.h"

#define MAX_HEIGHT_JUMP 4


class Tema2 : public SimpleScene
{
public:
	Tema2();
	~Tema2();
	void Init();

	glm::vec3 RED = glm::vec3(1, 0, 0);
	glm::vec3 YELLOW = glm::vec3(1, 1, 0);
	glm::vec3 ORANGE = glm::vec3(1, 0.6f, 0);
	glm::vec3 GREEN = glm::vec3(0, 1, 0);
	glm::vec3 BLUE = glm::vec3(0, 0, 1);
	glm::vec3 VIOLET = glm::vec3(0.3f, 0.2f, 0.3f);
	glm::vec3 GRAY = glm::vec3(0.5f, 0.5f, 0.5f);

	glm::vec4 combustibilPos = glm::vec4(1.05, 3, 2.1, 15);

	GLfloat xCameraCoord = 0, yCameraCoord = 0;

private:
	void FrameStart();
	void Update(float deltaTimeSeconds);
	int Tema2::checkCollision();
	void Tema2::platformPowerups(int currentPlatform);
	void Tema2::RanderPlatforms(float deltaTimeSeconds);
	void RanderPlayer(float deltaTimeSeconds);
	void Tema2::generatePlatforms(glm::mat4 modelMatrix);

	void FrameEnd();
	void RenderMesh(Mesh* mesh, Shader* shader, const glm::mat4& modelMatrix, const glm::vec3& color, Texture2D* texture1, Texture2D* texture2);
	void OnInputUpdate(float deltaTime, int mods);
	void OnKeyPress(int key, int mods);
	void OnKeyRelease(int key, int mods);
	void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY);
	void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods);
	void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods);
	void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY);
	void OnWindowResize(int width, int height);

protected:
	CameraTema2::Camera* camera;
	bool renderCameraTarget;


	float speed = 0.0f;
	int blockSpeed = 0;
	int firstPerson = 1;
	bool gameOver = 0;
	float gas = 37.5;
	float rotateAngle = 0.0f;
	double duration = 0, score = 0;
	std::clock_t clockTime;
	int playerDeformation = 0;
	int started = 1;
	int platformsPerTour = 3;
	int platformStartPos = 1;
	glm::mat4 projectionMatrix;
	glm::mat4 modelMatrix;
	bool projectionType;

};