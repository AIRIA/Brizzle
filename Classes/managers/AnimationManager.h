﻿#ifndef _ANIMATINMANAGER_H_
#define _ANIMATINMANAGER_H_

#include "common/common_header.h"

class AnimationManager:CCObject
{
private:
	static AnimationManager *_instance;
public:
	static AnimationManager *shareManager();
	void addAnimation(const char *prefix,const char *animationName,int began,int end,float fps);
};

#endif // !_ANIMATINMANAGER_H_
