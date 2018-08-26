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
	enum Mode 
	{ 
	flyIn = 0, 
	toFormation = 1, 
	stayInFormation = 2
	};
	Vec2 enemyPosition;

public:
	Enemy(Scene *scene);
	Sprite *getEnemySprite();
	void moveEnemy(const float &delta);
	Vec2 getPosition();
	void goToFormation(const float &delta, const Vec2 &initPosition, const Vec2 &endPosition);
	void setEnemyPosition(const Vec2 &position);
};