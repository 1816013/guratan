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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include <input/OPRT_state.h>
#include <obj/Obj.h>
#include <obj/Player.h>
#include <obj/Enemy.h>
#include <obj/Weapon.h>
#include "ui//CocosGUI.h"

enum class Z_ORDER_TYPE
{
	BACK,
	CHAR,
	FLONT,
	UI,
	MENU,
	MAX
};

enum class SceneType
{
	GAME,
	MENU,
	LOADING,
	MAX
};


class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
	~GameScene();

    virtual bool init();
	void update(float delta)override;
	void SetSceneType(SceneType sceneType);
	void SetNextFloor(bool flag);

	int _floorNum;
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
	// ä÷êî
	void SetEnemy(EnemyType enemyType);
	void ColTest();
	bool ChangeFloor();
	void ChangeSceneType(SceneType sceneType);

	// ïœêî	
	cocos2d::Layer* uiBglayer;
	cocos2d::Layer* MenuBglayer;
	cocos2d::Layer* charBglayer;
	cocos2d::Layer* flontBglayer;
	cocos2d::Layer* backBglayer;

	int _zOrderUI;		// UIÇÃLayer
	int _zOrderMenu;	// MenuÇÃLayer
	int _zOrderBack;	// àÍî‘å„ÇÎÇÃzorder
	int _zOrderChar;	// ∑¨◊ÇÃzorder
	int _zOrderFlont;	// àÍî‘ëOÇÃzorder

	SceneType _sceneType;

	std::unique_ptr<OPRT_state>_inputState;
	std::unique_ptr<GameMap>_gameMap;

	// âº
	cocos2d::Sprite* selectSp;
	cocos2d::ui::Button* selectButton[3];
	cocos2d::Sprite* mapObj;
	bool flag;
	int selectCnt;				//
	AbilityPair retAbility[3];		// abilityàÍéûäiî[óp
	ChargeType retCharge[3];	// chargeTypeàÍéûäiî[óp
	bool _nextFloor;			// éüÇÃÉtÉçÉAÇ÷çsÇ≠Ç©
};

#endif // __HELLOWORLD_SCENE_H__
