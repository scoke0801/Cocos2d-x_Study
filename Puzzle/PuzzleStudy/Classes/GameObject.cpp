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
