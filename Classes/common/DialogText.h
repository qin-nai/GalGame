#pragma once
#include "cocos2d.h"

class DialogText : public cocos2d::Scene{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
private:
	void DialogImg(const char* ImgURL);
};
