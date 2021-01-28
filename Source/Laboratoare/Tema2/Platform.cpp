#include "Platform.h"


Platform::Platform() {
}

Platform::~Platform() {
}

Platform::Platform(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Platform::Platform(float x, float y, float z, float scaleZ, glm::vec3 color) {
	this->x = x;
	this->y = y;
	this->z = z;
	this->scaleZ = scaleZ;
	this->color = color;
}


Mesh* Platform::createPlatform(std::string name) {

	Mesh* platform = new Mesh(name);
	platform->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "box.obj");

	return platform;
}

void Platform::reset() {
	ready = true;
	z = -100;
	scaleZ = 1;
}

void Platform::generatePlatform(glm::mat4 modelMatrix, float lastStart, bool firstRound) {

	this->modelMatrix = modelMatrix;
	
	/* generate a random NUM*/
	int randomDist = generateInt(4, 7);

	// generate a random color for platform
	int aux_color = generateInt(0, 4);

	if (this->ready) {

		// make this platform unavailable
		this->ready = false;
		// generate start position

		if (firstRound) {
			this->z = 0.2f;
			this->scaleZ = 7;

		}
		else {
			this->z = lastStart - randomDist;
			this->scaleZ = generateInt(2, 7); // aux_color + 2;

			switch (aux_color) {
			case RED_code:
				this->color = glm::vec3(1, 0, 0);
				break;
			case YELLOW_code:
				this->color = glm::vec3(1, 1, 0);
				break;
			case ORANGE_code:
				this->color = glm::vec3(1, 0.6, 0);
				break;
			case GREEN_code:
				this->color = glm::vec3(0, 1, 0);
				break;
			case BLUE_code:
				this->color = glm::vec3(0, 0, 1);
				break;
			case VIOLET_code:
				this->color = glm::vec3(0.3f, 0.2f, 0.3f);
				break;
			}

			this->width = baseWidth * this->scaleX;
			this->height = baseHeight * this->scaleY;
			this->length = baseLength * this->scaleZ;

			// this->modelMatrix *= glm::translate(this->modelMatrix, glm::vec3(this->x, this->y, this->z));
			// this->modelMatrix *= glm::scale(this->modelMatrix, glm::vec3(this->scaleX, this->scaleY, this->scaleZ));
		}
	}
}

void Platform::move(float deltaTimeSeconds, float speed) {

	if (ready) {
		return;
	}
	// update the speed for platforms
	// this->speedup = speed;
	// if the platform is not on screen, regenerate it with new sizes
	if (this->z > PLATFORM_DESTRUCTION) {
		reset();
		// ready = true;
		return;

	} else {
		
		this->z += deltaTimeSeconds * speed;
		this->modelMatrix = glm::mat4(1);
		// move the platform 

		this->modelMatrix *= Transform3D::Translate(this->x, this->y, this->z);
		this->modelMatrix *= Transform3D::Scale(this->scaleX, this->scaleY, this->scaleZ);

		// this->modelMatrix *= glm::scale(this->modelMatrix, glm::vec3(this->scaleX, this->scaleY, this->scaleZ));
	}

}