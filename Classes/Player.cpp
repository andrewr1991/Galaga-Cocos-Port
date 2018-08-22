#include "Player.h"

Player::Player(Scene *scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	playerSprite = Sprite::create("C:/Projects/test/Resources/TileGameResources/player.png");

	playerSprite->setScale(0.5);
	playerSprite->setPosition(visibleSize.width / 2, visibleSize.height / 7);

	playerX = playerSprite->getPositionX();

	PhysicsBody *playerBody = PhysicsBody::createBox(playerSprite->getContentSize());
	playerBody->setCollisionBitmask(PLAYER_BITMASK);
	playerBody->setContactTestBitmask(TRUE);

	playerSprite->setPhysicsBody(playerBody);

	scene->addChild(playerSprite, 1);
}

Sprite* Player::getPlayerSprite()
{
	return playerSprite;
}

void Player::movePlayer(const float &delta)
{
	playerX += (delta * playerSpeed);
	playerSprite->setPositionX(playerX);
}

Vec2 Player::getPosition()
{
	return playerSprite->getPosition();
}