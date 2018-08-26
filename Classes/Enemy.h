#pragma once

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
using namespace std;

class Enemy
{
private:
	Sprite *enemySprite;
	const int enemySpeed = 50;
	float enemyX = 10.0;
	Size visibleSize;
	Vec2 origin;
	enum Mode 
	{ 
	flyInMode = 0, 
	goToFormationMode = 1, 
	stayInFormationMode = 2
	};
	Mode mode;
	Vec2 enemyPosition;

public:
	Enemy(Scene *scene);
	Sprite *getEnemySprite();
	void moveEnemy(const float &delta);
	Vec2 getPosition();
	void flyIn(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3, float t);
	void goToFormation(const float &delta, const Vec2 &initPosition, const Vec2 &endPosition);
	void setEnemyPosition(const Vec2 &position);
	int getMode();
	void setMode(int mode);
};