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
	return GameScene::create();
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

	// Create 6 player missiles
	for (int i = 0; i < 6; i++)
	{
		PlayerMissile *playerMissile = new PlayerMissile(this);
		playerMissiles.push_back(playerMissile);
	}

	auto eventListener = EventListenerKeyboard::create();

	Director::getInstance()->getOpenGLView()->setIMEKeyboardState(true);

	eventListener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event *event)
	{
		if (find(keys.begin(), keys.end(), keyCode) == keys.end())
		{
			keys.push_back(keyCode);
		}
	};

	eventListener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event *event)
	{
		keys.erase(find(keys.begin(), keys.end(), keyCode));
	};

	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);

	this->scheduleUpdate();
	
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
	if (isKeyPressed(EventKeyboard::KeyCode::KEY_D) || isKeyPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW))
	{
		// Pass positive 'delta' value to move player to the right
		player->movePlayer(delta);
	}

	// Logic for moving the player to the left
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
}

Vec2 GameScene::cubicBezier(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3, float t, Vec2& pFinal)
{
	pFinal.x = pow((1 - t), 3) * p0.x +
		pow((1 - t), 2) * 3 * t * p1.x +
		(1 - t) * 3 * t * t * p2.x +
		t * t * t * p3.x;

	pFinal.y = pow((1 - t), 3) * p0.y +
		pow((1 - t), 2) * 3 * t * p1.y +
		(1 - t) * 3 * t * t * p2.y +
		t * t * t * p3.y;

	return pFinal;
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
