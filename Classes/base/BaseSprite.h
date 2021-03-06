﻿#ifndef _BASESPRITE_H_
#define _BASESPRITE_H_

#include "common/common_header.h"

class BaseSprite:public CCSprite,public CCTargetedTouchDelegate
{
protected:
	bool _isContainPoint(CCTouch *touch);
private:
    bool m_bTouchEnable;
    CCObject *m_pTargetBegan;
    SEL_MenuHandler beganHandler;
    CCObject *m_pTargetMove;
    SEL_MenuHandler moveHandler;
    CCObject *m_pTargetEnded;
    SEL_MenuHandler endedHandler;
public:
	bool m_bSwallow;
    int m_iTouchPriority;
    static BaseSprite *createSpriteWithFrameName(const char *frameName);
    static BaseSprite *create(const char *fileName);
    virtual void onEnter();
    virtual void onExit();
    BaseSprite();
    void setTargetBegan(CCObject *target,SEL_MenuHandler sel);
    void setTargetMove(CCObject *target,SEL_MenuHandler sel);
    void setTargetEnded(CCObject *target,SEL_MenuHandler sel);
    void setTouchEnabled(bool enable);
    void setTouchPriority(int proirity);
	//void setIsSwallow(bool swallow);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
};

#endif // !_BASESPRITE_H_
