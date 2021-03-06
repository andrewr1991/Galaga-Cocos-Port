/****************************************************************************
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/

#include "GameScene.h"
#include "SimpleAudioEngine.h"

Scene* GameScene::createScene()
{
	Scene *scene = Scene::createWithPhysics();

	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vect(0, 0));

	auto layer = GameScene::create();
	scene->addChild(layer);

	return scene;
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	player = new Player(this);
	enemy = new Enemy(this);
	gameHUD = new GameHUD(this);

	// Create 6 player missiles
	for (int missileTag = 0; missileTag < NUM_PLAYER_MISSILES; missileTag++)
	{
		PlayerMissile *playerMissile = new PlayerMissile(this, missileTag);
		playerMissiles.push_back(playerMissile);
	}

	auto eventListenerKeyboard = EventListenerKeyboard::create();

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	eventListenerKeyboard->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event)
	{
		if (find(keys.begin(), keys.end(), keyCode) == keys.end())
		{
			keys.push_back(keyCode);
		}
	};

	eventListenerKeyboard->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event)
	{
		keys.erase(find(keys.begin(), keys.end(), keyCode));
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListenerKeyboard, this);

	this->scheduleUpdate();

	auto eventContactListener = EventListenerPhysicsContact::create();
	eventContactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventContactListener, this);

	initPosition.set(200, 200);
	endPosition.set(250, 700);

	p0.setPoint(400.0, 800.0);
	p1.setPoint(386.0, 663.0);
	p2.setPoint(50.0, 700.0);
	p3.setPoint(50.0, 450.0);
	t = 0.0;

	enemy->setEnemyPosition(p0);

	return true;
}

bool GameScene::isKeyPressed(EventKeyboard::KeyCode keyCode)
{
	if (find(keys.begin(), keys.end(), keyCode) != keys.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void GameScene::update(float delta)
{
	Node::update(delta);

	totalGameTime += delta;

	// Logic for moving the player to the right
	// Also give the option to use D or right arrow to move right
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) || isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		// Pass positive 'delta' value to move player to the right
		player->movePlayer(delta);
	}

	// Logic for moving the player to the left
	// Also give the option to use A or left arrow to move left
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_A) || isKeyPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW))
	{
		// Pass negative 'delta' value to move player to the left
		player->movePlayer(-delta);
	}

	// Logic for firing a player missile
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_SPACE) && ((totalGameTime - spaceLastPressed) >= 0.3))
	{
		playerMissiles[missileCounter]->setMissilePosition(player->getPosition().x, player->getPosition().y);
		playerMissiles[missileCounter]->setMissileActive(true);
		spaceLastPressed = totalGameTime;
		missileCounter++;

		if (missileCounter >= 6)
		{
			missileCounter = 0;
		}
	}

	// If missileActive is true, the missile will fly
	for (int i = 0; i < 6; i++)
	{
		if (playerMissiles[i]->getMissileActive())
		{
			playerMissiles[i]->fireMissile(delta);
		}
	}

	if ((round(enemy->getPosition().y) > round(p3.y)) && enemy->getMode() == 0)
	{
		enemy->flyIn(p0, p1, p2, p3, t);
		t += 0.005;
	}

	else if ((round(enemy->getPosition().y) == round(p3.y)) && enemy->getMode() == 0)
	{
		enemy->setMode(1);
		t = 0;
		p0.set(50.0, 450.0);
		p1.set(50.0, 250.0);
		p2.set(300.0, 250.0);
		p3.set(300.0, 500.0);
	}

	if ((round(enemy->getPosition().x) < round(p3.x)) && enemy->getMode() == 1)
	{
		enemy->flyIn(p0, p1, p2, p3, t);
		t += 0.005;
	}

	else if ((round(enemy->getPosition().x) == round(p3.x)) && enemy->getMode() == 1)
	{
		enemy->setMode(2);
	}

	if (enemy->getMode() == 2)
	{
		enemy->goToFormation(delta, p3, endPosition);
	}
}

bool GameScene::onContactBegin(PhysicsContact &contact)
{
	PhysicsBody *a = contact.getShapeA()->getBody();
	PhysicsBody *b = contact.getShapeB()->getBody();

	if ((a->getCollisionBitmask() == PLAYER_MISSILE_BITMASK && b->getCollisionBitmask() == ENEMY_BITMASK) ||
		(a->getCollisionBitmask() == ENEMY_BITMASK && b->getCollisionBitmask() == PLAYER_MISSILE_BITMASK))
	{
		for (int i = 0; i < NUM_PLAYER_MISSILES; i++)
		{
			if (a->getTag() == i || b->getTag() == i)
			{
				playerMissiles[i]->setMissileActive(false);
				playerMissiles[i]->setMissilePosition(OFFSCREEN_X, OFFSCREEN_Y);
			}
		}
	}

	if ((a->getCollisionBitmask() == PLAYER_BITMASK && b->getCollisionBitmask() == ENEMY_BITMASK) ||
		(a->getCollisionBitmask() == ENEMY_BITMASK && b->getCollisionBitmask() == PLAYER_BITMASK))
	{
		//this->removeChild(gameHUD->getLifeSprites().back());
		//this->removeChild(enemy->getEnemySprite());
	}

	return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}
