#include "HUD.h"

GameHUD::GameHUD(Scene *scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	for (int lifeSprite = 0; lifeSprite < NUM_PLAYER_LIVES; lifeSprite++)
	{
		lifeSprites.push_back(Sprite::create("C:/Projects/test/Resources/TileGameResources/player.png"));

		lifeSprites.back()->setScale(LIFE_SPRITE_SCALE);
		lifeSprites.back()->setPosition(visibleSize.width / 2, (lifeSprites.back()->getContentSize().height / 2.5) - 10);

		scene->addChild(lifeSprites.back(), PLAYER_LIVES_Z_ORDER);
	}
	CCLOG("%f\n", lifeSprites[0]->getPosition().y);
}

vector<Sprite*> GameHUD::getLifeSprite()
{
	return lifeSprites;
}