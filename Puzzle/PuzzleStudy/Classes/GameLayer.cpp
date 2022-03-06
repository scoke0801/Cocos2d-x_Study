#include "GameLayer.h"
#include "MyLogger.h"
bool GameLayer::init()
{
	if (Layer::init() == false) {
		return false;
	} 
	m_winSize = cocos2d::Director::getInstance()->getWinSize();

	InitObjects();

	return true;
}

cocos2d::Scene* GameLayer::scene()
{
	cocos2d::Scene* pScene = cocos2d::Scene::create();

	GameLayer* pLayer = GameLayer::create();
	pScene->addChild(pLayer);

	return pScene;
}

void GameLayer::InitObjects()
{
	cocos2d::Sprite* pBackGroundSprite = cocos2d::Sprite::create("Background.png");
	pBackGroundSprite->setPosition(cocos2d::Vec2{ 0,0 });
	pBackGroundSprite->setAnchorPoint(cocos2d::Vec2{ 0.0f,0.0f });
	addChild(pBackGroundSprite, ICAST(zOrder::zBackground));

	std::string objectsNames[OBJECT_TYPE_COUNT] = {
		"Blue.png",
		"Brown.png",
		"Green.png",
		"Pink.png",
		"Purple.png",
		"Red.png",
		"Yellow.png"
	};

	for (UINT y = 0; y < ROW_COUNT; ++y) { 

		for (UINT x = 0; x < COL_COUNT; ++x) {
			int nType = rand() % OBJECT_TYPE_COUNT;
			cocos2d::Sprite* pGameObject = cocos2d::Sprite::create(objectsNames[nType]);

			// ³»¸² 
			pGameObject->setPosition( Common::ComputeXY(x,y) );
			pGameObject->setAnchorPoint({ 0.0f, 1.0f });

			m_pBoard[y][x] = pGameObject;

			addChild(pGameObject, ICAST(zOrder::zGameObject));
		}
	}

	DebugLog(SetLogMsg("TEST"));
}
