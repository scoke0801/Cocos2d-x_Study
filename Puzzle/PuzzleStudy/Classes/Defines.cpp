#include "Defines.h" 

float Common::ComputeX(float x)
{
    return floorf(x * (APP_WIDTH / COL_COUNT));
}

float Common::ComputeY(float y)
{
    return cocos2d::Director::getInstance()->getWinSize().height - floorf(y * (APP_HEIGHT / (ROW_COUNT + 4))) - OBJECT_HEIGHT;
}

cocos2d::Point Common::ComputeXY(float x, float y)
{
    return cocos2d::Point(ComputeX(x), ComputeY(y));
}

int Common::ComputeBoardX(float x)
{
    return static_cast<int>(x / floorf((APP_WIDTH / COL_COUNT)));
}

int Common::ComputeBoardY(float y)
{
    return static_cast<int>(y / floorf((APP_HEIGHT / (ROW_COUNT + 4))));
}
