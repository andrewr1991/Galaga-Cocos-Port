#pragma once

#include "cocos2d.h"
#include "Definitions.h"

USING_NS_CC;
using namespace std;

class GameHUD
{
private:
	vector <Sprite*> lifeSprites;
	Size visibleSize;
	Vec2 origin;
	float lifeSpriteX = 0.0;
	float xPadding = 0.0;
	int yPadding = 5;

public:
	GameHUD(Scene *scene);
	vector<Sprite*> getLifeSprites();
};