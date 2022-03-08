#include "GameLayer.h" 
#include "GameObject.h"

bool GameLayer::init()
{
	if (Layer::init() == false) {
		return false;
	} 
	m_winSize = cocos2d::Director::getInstance()->getWinSize();

	//cocos2d::Director::getInstance()->getEventDispatcher()->setEnabled(true);
	StartGame();  

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
	if ( true == m_bTouchStarted) {
		return false;
	}
	  
	if (!touch) {
		return false;
	}

	cocos2d::Point pt= touch->getLocationInView();

	m_nStartX = Common::ComputeBoardX(pt.x);
	m_nStartY = Common::ComputeBoardY(pt.y);
	if (m_nStartX < 0 || m_nStartX >= COL_COUNT) {
		return false;
	}
	if (m_nStartY < 0 || m_nStartY >= ROW_COUNT) {
		return false;
	}

	//m_pBoard[m_nStartY][m_nStartX]->setVisible(!m_pBoard[m_nStartY][m_nStartX]->isVisible());
	Utils::DebugLog(Utils::string_format("x : %f, y : %f, BX : %d, BY : %d\n", pt.x, pt.y, m_nStartX, m_nStartY));
	return m_bTouchStarted = true;
}

void GameLayer::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (false == m_bTouchStarted) {
		return;
	}
	cocos2d::Point pt = touch->getLocationInView();

	int nBoardX = Common::ComputeBoardX(pt.x);
	int nBoardY = Common::ComputeBoardY(pt.y);

	if (m_nStartX != nBoardX || m_nStartY != nBoardY) {
		if (IsAdjacent(m_nStartX, m_nStartY, nBoardX, nBoardY)) {
			SwapObjects(m_nStartX, m_nStartY, nBoardX, nBoardY);
		}
	}
	//DebugLog("Touch-Moved");
}

void GameLayer::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{
	if (false == m_bTouchStarted) {
		return;
	}

	
	m_bTouchStarted = false;
	//DebugLog("Touch-Ended");
}

void GameLayer::onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* unused_event)
{ 
}

bool GameLayer::IsAdjacent(int x1, int y1, int x2, int y2)
{
	return (abs(x1 - x2) + abs(y1 - y2)) == 1;
}

void GameLayer::SwapObjects(int x1, int y1, int x2, int y2)
{
	CGameObject* pTemp = m_pBoard[y1][x1];

	m_pBoard[y1][x1] = m_pBoard[y2][x2];
	m_pBoard[y2][x2] = pTemp;

	//m_pBoard[y1][x1]->setPosition(Common::ComputeXY(x1, y1));
	//m_pBoard[y2][x2]->setPosition(Common::ComputeXY(x2, y2));

	m_pBoard[y1][x1]->SetTargetBoardX(x1);
	m_pBoard[y1][x1]->SetTargetBoardY(y1);
	m_pBoard[y2][x2]->SetTargetBoardX(x2);
	m_pBoard[y2][x2]->SetTargetBoardY(y2);

	m_pBoard[y1][x1]->ProcessSliding();
	m_pBoard[y2][x2]->ProcessSliding();
}

void GameLayer::StartGame()
{
	srand((unsigned int)time(NULL));

	m_bTouchStarted = false;

	cocos2d::Sprite* pBackGroundSprite = cocos2d::Sprite::create("Background.png");
	pBackGroundSprite->setPosition(cocos2d::Vec2{ 0,0 });
	pBackGroundSprite->setAnchorPoint(cocos2d::Vec2{ 0.0f,0.0f });
	addChild(pBackGroundSprite, ICAST(zOrder::zBackground));

	bool bDebugDraw = true; 
	//bDebugDraw = false;
	if(bDebugDraw)
	{
		for (size_t y = 0; y < ROW_COUNT; ++y) {
			int ySize = m_winSize.height / ROW_COUNT;
			int xSize = m_winSize.width / COL_COUNT;
			for (size_t x = 0; x < COL_COUNT; ++x) {

				auto draw = DrawNode::create();
				draw->drawLine(Point(x * xSize, 0), Point(x * xSize, m_winSize.height), Color4F::RED);
				addChild(draw, ICAST(zOrder::zGameObject) + 1);

				draw = DrawNode::create();
				draw->drawLine(Point(0, y * ySize), Point(m_winSize.width, y * ySize), Color4F::RED);
				addChild(draw, ICAST(zOrder::zGameObject) + 1);
			}
		}
	}

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
	 
}
