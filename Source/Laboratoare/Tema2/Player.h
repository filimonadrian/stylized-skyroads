#pragma once

#include <Component\SimpleScene.h>
#include <Core/Engine.h>
#include "Limits.h"

class Player {
public:
	float x = 2.0f, y = 2.5f, z = 0.0f;

	int ascension = 0;
	int isBack = 0;

	float ground = 2.5f;
	float height = 1.0f;
	float width = 1.0f;

	float jumpDiff = 20;
	float speedup = 5;
	float time = 0;

	bool onPlatform = true;
	bool inJump = false;


public:
	Player();
	Player::Player(float x, float y, float z);
	Mesh* Player::createPlayer(std::string name);
	~Player();
	Mesh* GetPlayer();
	Mesh* player;
	void Player::move(float deltaTimeSeconds);

};