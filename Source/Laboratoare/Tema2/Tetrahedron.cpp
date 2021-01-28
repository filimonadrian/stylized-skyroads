#include "Tetrahedron.h"


Tetrahedron::Tetrahedron() {

}

Mesh* Tetrahedron::createTetrahedron(std::string name) {

		Mesh* mesh = new Mesh(name);

		std::vector<VertexFormat> vertices =
		{
			VertexFormat(glm::vec3(0, 0, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(0,0)),//0

			VertexFormat(glm::vec3(1, 0, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(1,0)),//1

			VertexFormat(glm::vec3(0, 0, 1),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(0,1)),//2

			VertexFormat(glm::vec3(0, 1, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(0,1)),//3

			VertexFormat(glm::vec3(0, 0, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(0,0)),//4

			VertexFormat(glm::vec3(1, 0, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(1,0)),//5

			VertexFormat(glm::vec3(0, 0, 1),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(1,0)),//6

			VertexFormat(glm::vec3(0, 1, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(0,1)),//7

			VertexFormat(glm::vec3(0, 0, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(0,0)),//8


			VertexFormat(glm::vec3(1, 0, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(1,1)),//9

			VertexFormat(glm::vec3(0, 0, 1),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(0,0)),//10

			VertexFormat(glm::vec3(0, 1, 0),
						 glm::vec3(0.2, 0.2, 0.2),
						 glm::vec3((rand() % 100) / 100.0, (rand() % 100) / 100.0, (rand() % 100) / 100.0),
						 glm::vec2(0.5,1)),//11

		};

		std::vector<unsigned short> indices =
		{
			0, 1, 2,
			3, 4, 5,
			7, 8, 6,
			11, 9, 10

		};


		mesh->InitFromData(vertices, indices);
		
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

void Tetrahedron::move(float deltaTimeSeconds) {
	
	this->modelMatrix = glm::mat4(1);
	
	if (this->ascending) {
		this->y += deltaTimeSeconds * 2;
	} else {
		this->y -= deltaTimeSeconds * 2;
	}

	if (this->y <= this->minY) {
		this->ascending = 1;

	} else if (this->y >= this->maxY) {
		this->ascending = 0;
	}

	modelMatrix *= Transform3D::Translate(x, y, z);
	modelMatrix *= Transform3D::Scale(1, 1, 1);

}