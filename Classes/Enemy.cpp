#include "Enemy.h"

Enemy::Enemy(Scene *scene)
{
	Mode mode = flyIn;

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	enemySprite = Sprite::create("C:/Projects/test/Resources/TileGameResources/yellow_blue_enemy.png");

	enemySprite->setScale(SPRITE_SCALE);
	enemySprite->setPosition(100, 200);

	PhysicsBody *enemyBody = PhysicsBody::createBox(enemySprite->getContentSize());
	enemyBody->setCollisionBitmask(ENEMY_BITMASK);
	enemyBody->setContactTestBitmask(true);

	enemySprite->setPhysicsBody(enemyBody);
	
	scene->addChild(enemySprite, ENEMY_Z_ORDER);
}

Sprite* Enemy::getEnemySprite(void)
{
	return enemySprite;
}

void Enemy::moveEnemy(const float &delta)
{
	enemyX += (delta * enemySpeed);
	enemySprite->setPositionX(enemyX);
}

Vec2 Enemy::getPosition(void)
{
	return enemySprite->getPosition();
}

void Enemy::goToFormation(const float &delta, const Vec2 &initPosition, const Vec2 &endPosition)
{
	if (enemySprite->getPosition().x <= endPosition.x)
	{
		enemyPosition.x += (delta * enemySpeed);

		// Calculate slope
		float m = (endPosition.y - initPosition.y) / (endPosition.x - initPosition.x);
		enemyPosition.y = (m * enemyPosition.x) - (m * initPosition.x) + initPosition.y;
		//positionFinal.x = ((y - initPosition.y) + (m * initPosition.x)) / m;

		enemySprite->setPosition(enemyPosition);
	}
}

void Enemy::setEnemyPosition(const Vec2 &position)
{
	enemyPosition = position;
	enemySprite->setPosition(enemyPosition);
}