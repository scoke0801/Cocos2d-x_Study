#include "GameLayer.h" 
#include "GameObject.h"
 
bool GameLayer::init()
{
	if (Layer::init() == false) {
		return false;
	} 
	m_winSize = cocos2d::Director::getInstance()->getWinSize();

	//cocos2d::Director::getInstance()->getEventDispatcher()->setEnabled(true);
	InitObjects();  

	auto listener = cocos2d::EventListenerTouchOneByOne::create(); 
	listener->setSwallowTouches(true); 

	listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
	listener->onTouchCancelled = CC_CALLBACK_2(GameLayer::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//cocos2d::Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this); 
	return true;
}

cocos2d::Scene* GameLayer::scene()
{
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	GameLayer* pLayer = GameLayer::create();
	pScene->addChild(pLayer);

	return pScene;
}

bool GameLayer::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (!touch) {
		return false;
	}

	cocos2d::Point pt= touch->getLocationInView();

	int boardX = Common::ComputeBoardX(pt.x);
	int boardY = Common::ComputeBoardY(pt.y);
	if (boardX < 0 || boardX >= COL_COUNT) {
		return false;
	}
	if (boardY < 0 || boardY >= ROW_COUNT) {
		return false;
	}
	m_pBoard[boardY][boardX]->setVisible(!m_pBoard[boardY][boardX]->isVisible());
	DebugLog(string_format("x : %f, y : %f, BX : %d, BY : %d\n", pt.x, pt.y, boardX, boardY));
	return true;
}

void GameLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	//DebugLog("Touch-Moved");
}

void GameLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	//DebugLog("Touch-Ended");
}

void GameLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	DebugLog("Touch-Cancelled");
}

void GameLayer::InitObjects()
{
	cocos2d::Sprite* pBackGroundSprite = cocos2d::Sprite::create("Background.png");
	pBackGroundSprite->setPosition(cocos2d::Vec2{ 0,0 });
	pBackGroundSprite->setAnchorPoint(cocos2d::Vec2{ 0.0f,0.0f });
	addChild(pBackGroundSprite, ICAST(zOrder::zBackground));

	 
	for (UINT y = 0; y < ROW_COUNT; ++y) { 

		for (UINT x = 0; x < COL_COUNT; ++x) {
			int nType = rand() % OBJECT_TYPE_COUNT; 

			CGameObject* pGameObject = CGameObject::Create(nType);
			m_pBoard[y][x] = pGameObject;

			pGameObject->setPosition( Common::ComputeXY(x,y) );
			pGameObject->setAnchorPoint({ 0.0f, 1.0f });

			addChild(pGameObject, ICAST(zOrder::zGameObject));
		}
	}

	DebugLog(SetLogMsg("TEST"));
}
