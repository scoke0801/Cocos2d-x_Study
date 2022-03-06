#pragma once

#include "cocos2d.h"
#include "Defines.h"

//USING_NS_CC;

class GameLayer : public cocos2d::Layer
{
	enum class zOrder {
		zBackground = 0,
		zGameObject = 1,
	};
public:
	bool init();

	static cocos2d::Scene* scene();

	
public:
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) override; 
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event) override; 
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event) override; 
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event) override;

public:
	CREATE_FUNC(GameLayer);


public:
	void InitObjects();

private:
	cocos2d::Size m_winSize;
	cocos2d::Sprite* m_pBoard[ROW_COUNT][COL_COUNT];
};

