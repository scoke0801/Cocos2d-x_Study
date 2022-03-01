#pragma once

#include "cocos2d.h"
#include "Defines.h"

//USING_NS_CC;

class GameLayer : public cocos2d::Layer
{
public:
	bool init();

	static cocos2d::Scene* scene();

	CREATE_FUNC(GameLayer);


public:
	void InitObjects();

private:
	cocos2d::Size m_winSize;
	cocos2d::Sprite* m_pBoard[ROW_COUNT][COL_COUNT];
};

