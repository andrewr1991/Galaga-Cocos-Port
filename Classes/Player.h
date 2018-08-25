#pragma once

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
using namespace std;

class Player
{
private:
	Sprite *playerSprite;
	const int playerSpeed = 200;
	float playerX = 10.0;
	Size visibleSize;
	Vec2 origin;
	int lives = 0;

public:
	Player(Scene *scene);
	Sprite *getPlayerSprite();
	void movePlayer(const float &delta);
	Vec2 getPosition();
};