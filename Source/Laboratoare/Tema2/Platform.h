#pragma once
#include <Component\SimpleScene.h>
#include <Core/Engine.h>
#include <string>
#include <include/glm.h>
#include <Core/GPU/Mesh.h>
#include <iostream>
#include <random>
#include <Laboratoare\Tema2\Transform3D.h>
#include "Random.h"
#include "Limits.h"


class Platform {

public:
	float x = 0.0f, y = 2.0f, z = 4.0f;
	float speedup = 0;
	
	glm::vec3 color;
	
	float time = 0;

	bool hit = false;
	bool ready = true;

	float height = 0, width = 0, length = 0;
	float baseWidth = 1.0f, baseHeight = 0.1f, baseLength = 2.0f;

	float scaleX = 1, scaleY = 0.1f, scaleZ = 1.0f;

	glm::mat4 modelMatrix = glm::mat4(1);


public:
	Platform();
	Platform(float x, float y, float z);
	Platform(float x, float y, float z, float scaleZ, glm::vec3 color);

	~Platform();
	Mesh* Platform::createPlatform(std::string name);
	void Platform::reset();
	void Platform::generatePlatform(glm::mat4 modelMatrix, float lastStart, bool firstRound);
	void Platform::move(float deltaTimeSeconds, float speed);

};