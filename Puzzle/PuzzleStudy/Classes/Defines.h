#pragma once

#include "cocos2d.h" 

constexpr int APP_WIDTH = 480;
constexpr int APP_HEIGHT = 800;

constexpr int ROW_COUNT = 8;
constexpr int COL_COUNT = 8;
constexpr int MAX_ROW_COUNT = 10;

constexpr int OBJECT_TYPE_COUNT = 7;

constexpr int OBJECT_WIDTH = 96;
constexpr int OBJECT_HEIGHT = 96;

class Common {
public:
	static float ComputeX(float x);
	static float ComputeY(float y);

	static cocos2d::Point ComputeXY(float x, float y);

	static int ComputeBoardX(float x);
	static int ComputeBoardY(float y); 
};

template< typename type_>
inline int ICAST(type_ val) {
	return static_cast<int>(val);
}
