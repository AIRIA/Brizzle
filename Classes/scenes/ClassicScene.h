﻿#ifndef _CLASSICSCENE_H_
#define _CLASSICSCENE_H_

#include "base/BaseScene.h"
#include "components/PauseMenu.h"
#include "components/Bird.h"

class ForbiddenLayer;
class ClassicScene:public BaseScene
{
private:
    BaseSprite *pauseSpr;
    float totalSeconds;
    float passSeconds;
    void progressUpdate(float del);
    CCNode *progressNode;
    CCLabelAtlas *scoreLabel;
    void __initBackground();
    void __initPauseSprite();
    void __createBird();
    void __ready();
    void __start();
    void __startHandler(CCNode *node);
    void __showScore(CCObject *data);
    PauseMenu *m_pPauseMenu;
public:
    CCSpriteBatchNode *m_pBirdBatchNode;
    /* 消除个数在3个以上的时候显示小鸟特效所在的层 */
    ForbiddenLayer *effectLayer;

    CCNode *m_pScoreNode;
    virtual void loadAssets();
    virtual bool init();
    CREATE_FUNC(ClassicScene);
    virtual void onEnter();
    virtual void onExit();
	ClassicScene():m_pPauseMenu(NULL),totalSeconds(120.0f),passSeconds(0.0f) {
	};
selector:
    /* 背景木头移动完毕后的回调函数 */
    void __woodMoveCall();
    /* 延时后 把背景木头的透明度设置为不透明 */
    void __delayCall(CCNode *node);
    /* 显示暂停按钮 */
    void __showPauseMenu(CCObject *pSender);
    /* 继续游戏 */
    void __resumeGame(CCObject *pSender);
    /* 显示退出确认框的时候调度 */
    void __onExitShow(CCObject *pSender);
    /* 时间奖励 */
    void __timeReward(CCObject *obj);

	void __quitHandler(CCObject *pSender);

	void __restartHandler(CCObject *pSender);
	void __adsReceivedHandler(CCObject *pSender);
	void __adsSpendHandler(CCObject *pSender);

};


#endif // !_CLASSICSCENE_H_
