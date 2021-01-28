#include "Tetrahedron.h"


Tetrahedron::Tetrahedron() {
}

Mesh* Tetrahedron::createTetrahedron(std::string name) {

	Mesh* mesh = new Mesh(name);
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");

	return mesh;
}

Tetrahedron::Tetrahedron(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Tetrahedron::~Tetrahedron() {
}

Mesh* Tetrahedron::GetTetrahedron() {
	return tetrahedron;
}
