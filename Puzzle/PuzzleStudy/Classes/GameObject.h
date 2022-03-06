#pragma once

#include "Defines.h"


#define GET_SET_DEFINE(typeName, funcName, varName) typeName Get##funcName() { return varName;}\
	void Set##funcName(typeName var){ varName = var; }\
	typeName varName;


class CGameObject : public cocos2d::Sprite
{
public:
	CGameObject();
	~CGameObject();
	
protected:
	static CGameObject* create(const std::string& fileName, const cocos2d::Rect& rect);

public:
	static CGameObject* Create(int type);

	GET_SET_DEFINE(int, Type, m_nType); 
};
