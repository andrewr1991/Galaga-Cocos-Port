#pragma once

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
using namespace std;

class PlayerMissile
{
private:
	Sprite *playerMissileSprite;
	int playerMissileSpeed = 1200;
	float playerMissileY;
	Size visibleSize;
	Vec2 origin;
	bool missileActive = false;

public:
	PlayerMissile(Scene *scene, const int &missileTag);
	Sprite *getMissileSprite();
	void fireMissile(const float &delta);
	void setMissileActive(bool active);
	bool getMissileActive();
	void setMissilePosition(const float &x, const float &y);
	Vec2 getMissilePosition();
};