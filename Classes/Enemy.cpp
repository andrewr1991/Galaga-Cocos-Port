#include "Enemy.h"

Enemy::Enemy(Scene *scene)
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	enemySprite = Sprite::create("C:/Projects/test/Resources/TileGameResources/yellow_blue_enemy.png");

	enemySprite->setScale(SPRITE_SCALE);
	enemySprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	PhysicsBody *enemyBody = PhysicsBody::createBox(enemySprite->getContentSize());
	enemyBody->setCollisionBitmask(ENEMY_BITMASK);
	enemyBody->setContactTestBitmask(true);

	enemySprite->setPhysicsBody(enemyBody);
	
	scene->addChild(enemySprite, ENEMY_Z_ORDER);
}

Sprite* Enemy::getEnemySprite()
{
	return enemySprite;
}

void Enemy::moveEnemy(const float &delta)
{
	enemyX += (delta * enemySpeed);
	enemySprite->setPositionX(enemyX);
}

Vec2 Enemy::getPosition()
{
	return enemySprite->getPosition();
}