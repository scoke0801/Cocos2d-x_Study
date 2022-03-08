#pragma once

#include "cocos2d.h"
#include "Defines.h"

//USING_NS_CC;
class CGameObject;

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

	bool IsAdjacent(int x1, int y1, int x2, int y2);
	void SwapObjects(int x1, int y1, int x2, int y2);

public:
	CREATE_FUNC(GameLayer);


public:
	void StartGame();

private:
	cocos2d::Size m_winSize;
	CGameObject* m_pBoard[ROW_COUNT][COL_COUNT];

	bool m_bTouchStarted; 
	int m_nStartX;
	int m_nStartY;
};

