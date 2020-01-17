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
#include <Unit/Obj.h>
#include <Unit/Player.h>

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
	MAX
};


class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	void update(float delta)override;
	void SetSceneType(SceneType sceneType);
	void SetNextFloor(bool flag);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
	// 関数
	void SetEnemy(EnemyMoveAI moveAI, EnemyAttackAI attackAI);
	void ColTest();
	bool ChangeFloor();

	// 変数	
	cocos2d::Layer* uiBglayer;
	cocos2d::Layer* MenuBglayer;
	cocos2d::Layer* charBglayer;
	cocos2d::Layer* flontBglayer;
	cocos2d::Layer* backBglayer;

	int _zOrderUI;		// UIのLayer
	int _zOrderMenu;	// MenuのLayer
	int _zOrderBack;	// 一番後ろのzorder
	int _zOrderChar;	// ｷｬﾗのzorder
	int _zOrderFlont;	// 一番前のzorder

	SceneType _sceneType;

	std::unique_ptr<OPRT_state>_inputState;
	std::unique_ptr<GameMap>_gameMap;

	// 仮
	cocos2d::Sprite* mapObj;
	bool flag;
	int selectCnt;				//　PC操作用
	Ability retAbility[3];		// ability一時格納用
	bool _nextFloor;			// 次のフロアへ行くか
	int _floorNum;
};

#endif // __HELLOWORLD_SCENE_H__
