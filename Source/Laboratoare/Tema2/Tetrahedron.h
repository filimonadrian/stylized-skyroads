#pragma once

#include <Component\SimpleScene.h>
#include <Core/Engine.h>
#include "Limits.h"
#include <Laboratoare\Tema2\Transform3D.h>

class Tetrahedron {
public:
	float x = 4.0f, y = 4, z = 0;
	
	float minY = 2, maxY = 4;
	bool ascending = 0;
	glm::mat4 modelMatrix;

public:
	Tetrahedron();
	Tetrahedron::Tetrahedron(float x, float y, float z);
	Mesh* Tetrahedron::createTetrahedron(std::string name);
	~Tetrahedron();
	Mesh* GetTetrahedron();
	Mesh* tetrahedron;
	void Tetrahedron::move(float deltaTimeSeconds);

};