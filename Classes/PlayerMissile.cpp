#include "PlayerMissile.h"

PlayerMissile::PlayerMissile(Scene *scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	playerMissileSprite = Sprite::create("C:/Projects/test/Resources/TileGameResources/player_missile.png");

	playerMissileSprite->setScale(0.5);
	playerMissileSprite->setPosition(1000, 1000);

	//playerMissileY = playerMissileSprite->getPositionY();
	scene->addChild(playerMissileSprite, 0);
}

Sprite* PlayerMissile::getMissileSprite()
{
	return playerMissileSprite;
}

void PlayerMissile::fireMissile(const float &delta)
{
	playerMissileY += (delta * playerMissileSpeed);
	playerMissileSprite->setPositionY(playerMissileY);
}

void PlayerMissile::setMissileActive(bool active)
{
	missileActive = active;
}

bool PlayerMissile::getMissileActive()
{
	return missileActive;
}

void PlayerMissile::setMissilePosition(const float &x, const float &y)
{
	playerMissileY = y;
	playerMissileSprite->setPosition(x, y);
}

Vec2 PlayerMissile::getMissilePosition()
{
	return playerMissileSprite->getPosition();
}
