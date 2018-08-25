#include "HUD.h"

GameHUD::GameHUD(Scene *scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	// 2.5 is used here to compensate for the scaling of the sprite by LIFE_SPRITE_SCALE (0.4)
	// 4.5 is used here because I just want half of the height or width of the sprite as opposed to using 2.5 to get the full, scaled height or width
	for (int lifeSprite = 0; lifeSprite < NUM_PLAYER_LIVES; lifeSprite++)
	{
		lifeSprites.push_back(Sprite::create("C:/Projects/test/Resources/TileGameResources/player.png"));

		lifeSprites.back()->setScale(LIFE_SPRITE_SCALE);
		lifeSprites.back()->setPosition(lifeSprites.back()->getContentSize().width / 4.5 + xPadding, 
			                           ((lifeSprites.back()->getContentSize().height / 2.5) - lifeSprites.back()->getContentSize().height / 4.5) + yPadding);

		xPadding += (lifeSprites.back()->getContentSize().width / 2.5);

		scene->addChild(lifeSprites.back(), PLAYER_LIVES_Z_ORDER);
	}
}

vector<Sprite*> GameHUD::getLifeSprites()
{
	return lifeSprites;
}