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
#pragma once

#include "cocos2d.h"
#include "Player.h"
#include "PlayerMissile.h"
#include "Definitions.h"
#include "Enemy.h"
#include "HUD.h"
#include <vector>

USING_NS_CC;
using namespace std;

class GameScene : public Scene
{
private:
	//static Scene *scene;
	Vec2 p0;
	Vec2 p1;
	Vec2 p2;
	Vec2 p3;
	float t;
	vector<EventKeyboard::KeyCode> keys;
	Player *player;
	Enemy *enemy;
	vector<PlayerMissile*> playerMissiles;
	GameHUD *gameHUD;
	float totalGameTime = 0.0;
	float spaceLastPressed = 0.0;
	int missileCounter = 0;

public:
    static Scene* createScene();

    virtual bool init();

	bool isKeyPressed(EventKeyboard::KeyCode code);
	virtual void update(float delta) override;

	Vec2 cubicBezier(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3, float t, Vec2& pFinal);
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);

	bool onContactBegin(PhysicsContact &contact);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};
