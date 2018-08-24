#pragma once

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
using namespace std;

class Enemy
{
private:
	Sprite *enemySprite;
	const int enemySpeed = 200;
	float enemyX = 10.0;
	Size visibleSize;
	Vec2 origin;

public:
	Enemy(Scene *scene);
	Sprite *getEnemySprite();
	void moveEnemy(const float &delta);
	Vec2 getPosition();
};