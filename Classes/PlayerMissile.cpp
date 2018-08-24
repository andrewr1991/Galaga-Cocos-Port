#include "PlayerMissile.h"

PlayerMissile::PlayerMissile(Scene *scene, const int &missileTag)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	playerMissileSprite = Sprite::create("C:/Projects/test/Resources/TileGameResources/player_missile.png");

	playerMissileSprite->setScale(SPRITE_SCALE);
	playerMissileSprite->setPosition(OFFSCREEN_X, OFFSCREEN_Y);

	PhysicsBody *playerMissileBody = PhysicsBody::createBox(playerMissileSprite->getContentSize());
	playerMissileBody->setGroup(-1);
	playerMissileBody->setCollisionBitmask(PLAYER_MISSILE_BITMASK);
	playerMissileBody->setContactTestBitmask(true);
	playerMissileBody->setTag(missileTag);

	playerMissileSprite->setPhysicsBody(playerMissileBody);

	scene->addChild(playerMissileSprite, PLAYER_MISSILE_Z_ORDER);
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
