#include "LoadingGameScene.h"
#include "PlayingScene.h"
#include "Constants.h"
#include "SoundManager.h"

// on "init" you need to initialize your instance
bool LoadingGameScene::init()
{
    bool bRet = false;
    do 
    {
        // super init first
        CC_BREAK_IF(! CCScene::init());

        // Get window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();

		// Get background
		CCSprite *background=CCSprite::spriteWithFile("loading/loading_screen.pvr");

		this->addChild(background);

		// Center the background on the screen
		background->setPosition(ccp(size.width/2, size.height/2));	// center it

        bRet = true;
    } while (0);

    return bRet;
}

void LoadingGameScene::onEnter()
{
	CCLog("LoadingScene onEnter");
	CCScene::onEnter();
}

void LoadingGameScene::onEnterTransitionDidFinish()
{
	CCLog("LoadingScene: transition did finish");
	schedule(schedule_selector(LoadingGameScene::update));
	CCScene::onEnterTransitionDidFinish();
}

void LoadingGameScene::onExit()
{
	//SoundManager::sharedSoundManager()->stopSoundMusicMenu();
	CCLog("LoadingScene onExit");
	CCScene::onExit();
}


void LoadingGameScene::update(cocos2d::ccTime dt)
{
	unschedule(schedule_selector(LoadingGameScene::update));
	PlayingScene* playingScene = PlayingScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, playingScene));
}

LoadingGameScene::~LoadingGameScene(void)
{
	CCLog("LoadingScene decontructor");
}