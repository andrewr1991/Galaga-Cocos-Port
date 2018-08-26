#include "Enemy.h"

Enemy::Enemy(Scene *scene)
{
	mode = Mode::flyInMode;

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

void Enemy::flyIn(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3, float t)
{
	enemyPosition.x = pow((1 - t), 3) * p0.x +
		pow((1 - t), 2) * 3 * t * p1.x +
		(1 - t) * 3 * t * t * p2.x +
		t * t * t * p3.x;

	enemyPosition.y = pow((1 - t), 3) * p0.y +
		pow((1 - t), 2) * 3 * t * p1.y +
		(1 - t) * 3 * t * t * p2.y +
		t * t * t * p3.y;

	enemySprite->setPosition(enemyPosition);
}

void Enemy::goToFormation(const float &delta, const Vec2 &initPosition, const Vec2 &endPosition)
{
	if (enemySprite->getPosition().x >= endPosition.x)
	{
		enemyPosition.x -= (delta * enemySpeed);

		// Calculate slope
		float m = (endPosition.y - initPosition.y) / (endPosition.x - initPosition.x);

		// Calculate new y position based on the changing x as shown above
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

int Enemy::getMode()
{
	return mode;
}

void Enemy::setMode(int mode)
{
	switch (mode)
	{
	case 0:
		this->mode = flyInMode;
		break;

	case 1:
		this->mode = goToFormationMode;
		break;

	case 2:
		this->mode = stayInFormationMode;
		break;

	default:
		CCLOG("Error. Must choose a valid mode");
		break;
	}
}