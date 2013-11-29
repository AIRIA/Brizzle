﻿#include "Bird.h"
#include "managers/SoundManager.h"
#include "managers/ShareManager.h"
#include "util/PuzzleUtil.h"

void Bird::onEnter()
{
    CCSprite::onEnter();
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this,m_iTouchPriority,false);
}

Bird * Bird::create( short type )
{
    Bird *bird = new Bird();
    CCString *name = CCString::createWithFormat("box0%d_normal_00@2x.png",type);
    if(bird&&bird->initWithSpriteFrameName(name->getCString()))
    {
        bird->birdType = type;
        bird->autorelease();
        CCArray *frames = CCArray::create();
        CCString *blinkFrame = CCString::createWithFormat("box0%d_normal_02@2x.png",type);
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(blinkFrame->getCString()));
        frames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name->getCString()));
        CCAnimation *animation = CCAnimation::createWithSpriteFrames(frames,0.2f);
        bird->blinkAct = CCAnimate::create(animation);
        bird->blink();
        return bird;
    }
    return NULL;
}
/* 小鸟眨眼的action 在回调函数中 循环调用*/
void Bird::blink()
{
    float delaySec = rand()%10+2.0f;
    CCDelayTime *delayTime = CCDelayTime::create(delaySec);
    CCCallFunc *callfunc = CCCallFunc::create(this,callfunc_selector(Bird::blink));
    runAction(CCSequence::create(delayTime,blinkAct,callfunc,NULL));
}

void Bird::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	ShareManager *sm = ShareManager::shareManager();
	sm->isChanging=false;
	/*if(sm->sedBird!=NULL)
	{
		sm->fstBird = NULL;
		sm->sedBird = NULL;
	}*/
    if(_isContainPoint(pTouch))
    {
        BaseSprite::ccTouchEnded(pTouch,pEvent);
    }

}

void Bird::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
    if(_isContainPoint(pTouch)&&isMoving==false&&ShareManager::shareManager()->isChanging==false)
    {
        __recordBird();
        BaseSprite::ccTouchMoved(pTouch,pEvent);
    }
}

bool Bird::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{

    bool res = BaseSprite::ccTouchBegan(pTouch,pEvent);
    if(res)
    {
        CCLog("began event");
        SoundManager::shareSoundManager()->playEffect("sounds/SFX/Bird_droped.mp3");
        CCActionInterval *scaleIn = CCScaleBy::create(0.2f,0.7f,1.2f);
        CCActionInterval *scaleBack = CCEaseElasticOut::create(CCScaleTo::create(0.6f,0.9f,0.9f));
        CCSequence *scaleSeq = CCSequence::create(scaleIn,scaleBack,NULL);
        runAction(scaleSeq);
        ShareManager *sm = ShareManager::shareManager();
        if(isMoving==false)
        {
            __recordBird();
        }
    }
    return true;
}

void Bird::__recordBird()
{
    ShareManager *sm = ShareManager::shareManager();
    Bird *first = sm->fstBird;
    Bird *second = sm->sedBird;
    if(first==NULL)
    {
        sm->fstBird = this;
        CCLog("first");
    }
    else if(second==NULL&&first!=this)
    {
        sm->sedBird = this;
        int fbRow = first->row;
        int fbCol = first->col;
        /*
         如果点击了第二个小鸟后 要判断是不是同一行或者同一列 相邻的小鸟
        */
        bool sameRowNeighbor = fbRow==row?abs(fbCol-col)==1:false;
        bool sameColNeighbor = fbCol==col?abs(fbRow-row)==1:false;
        if(sameColNeighbor||sameRowNeighbor)
        {
			ShareManager::shareManager()->isChanging=true;
            PuzzleUtil::instance()->changeBirdPosition();
        }
        CCLog("second");
    }
}


