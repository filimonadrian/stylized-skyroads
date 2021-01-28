#include "Player.h"


Player::Player() {
}

Mesh* Player::createPlayer(std::string name) {

	Mesh* mesh = new Mesh(name);
	mesh->LoadMesh(RESOURCE_PATH::MODELS + "Primitives", "sphere.obj");

	return mesh;
}

Player::Player(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

Player::~Player() {
}

Mesh* Player::GetPlayer() {
	return player;
}

void Player::move(float deltaTimeSeconds) {

	/* daca player-ul este in urcare si inca nu a ajuns la inaltimea maxima, urca in continuare
	 * daca a ajuns la inaltimea maxima, seteaza flagul pentru coborare
	 */
	if (ascension == 1) {
		if (y < MAX_HEIGHT_JUMP) {
			y += GRAV_ACC / 2 * deltaTimeSeconds;
		}
		else {
			ascension = 0;
		}
		/* daca este in coborare si inca nu a ajuns pe pamant, coboara incet
		 * altfel daca ajuns pe pamant, seteaza flagul de player.isBack
		 */
	}
	else {
		if (y > ground) {
			y -= GRAV_ACC / 2 * deltaTimeSeconds;
		}
		else {
			isBack = 1;
		}
	}

}