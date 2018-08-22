#pragma once
#ifndef __PLAYER_MISSILE_SCENE_H__
#define __PLAYER_MISSILE_SCENE_H__

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
using namespace std;

class PlayerMissile
{
private:
	Sprite *playerMissileSprite;
	const int playerMissileSpeed = 1200;
	float playerMissileY;
	Size visibleSize;
	Vec2 origin;
	bool missileActive = false;

public:
	PlayerMissile(Scene *scene);
	Sprite *getMissileSprite();
	void fireMissile(const float &delta);
	void setMissileActive(bool active);
	bool getMissileActive();
	void setMissilePosition(const float &x, const float &y);
	Vec2 getMissilePosition();
};
#endif __PLAYER_MISSILE_SCENE_H__