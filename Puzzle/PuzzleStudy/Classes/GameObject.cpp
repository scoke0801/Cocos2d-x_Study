#include "GameObject.h"

CGameObject::CGameObject()
    : m_nType(0)
{ 
}

CGameObject::~CGameObject()
{
}

CGameObject* CGameObject::create(const std::string& fileName, const cocos2d::Rect& rect)
{
    CGameObject* pSprite = new CGameObject();
    if (pSprite && pSprite->initWithFile(fileName, rect)) {
        pSprite->autorelease();
        return pSprite;
    }

    CC_SAFE_DELETE(pSprite);

    return nullptr;
}

CGameObject* CGameObject::Create(int type)
{
    std::string objectsNames[OBJECT_TYPE_COUNT] = {
           "Blue.png",
           "Brown.png",
           "Green.png",
           "Pink.png",
           "Purple.png",
           "Red.png",
           "Yellow.png"
    };

    if (type < 0 || type >= OBJECT_TYPE_COUNT) {
        return nullptr;
    }


    CGameObject* pGameObject = CGameObject::create(objectsNames[type].c_str(), { 0.0f, 0.0f,  OBJECT_WIDTH, OBJECT_HEIGHT });
    pGameObject->SetType(type);

    return pGameObject;
}

void CGameObject::ProcessSliding()
{
    Point position = getPosition();

    m_nPrevBoardX = Common::ComputeBoardX(position.x);
    m_nPrevBoardY = MAX_ROW_COUNT - Common::ComputeBoardY(position.y);

    Point targetPosition = Common::ComputeXY(m_nTargetBoardX, m_nTargetBoardY);

   // RotateBy* pRotateBy = RotateBy::create(1.0f, 360.0f);
    MoveBy* pMoveBy = MoveBy::create(0.1f, { targetPosition.x - position.x, targetPosition.y - position.y });
     
    FiniteTimeAction* pAction = Sequence::create(pMoveBy,
        CallFunc::create(CC_CALLBACK_0(CGameObject::SlidingCompleteHandler, this))
        , NULL);

    runAction(pAction);
}

void CGameObject::SlidingCompleteHandler()
{
    Utils::DebugLog("SlidingCompleteHandler");
}
