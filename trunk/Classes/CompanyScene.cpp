
#include "CompanyScene.h"
#include "SoundManager.h"
#include "MenuMainScene.h"
#include "Constants.h"

// on "init" you need to initialize your instance
bool CompanyScene::init()
{
    bool bRet = false;
    do 
    {
        // super init first
        CC_BREAK_IF(! CCScene::init());

        // Get window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();

		// Get background 512x512 for pvr
		CCSprite *company=CCSprite::spriteWithFile("logo/shinobigames_logo.pvr");
		// CCSprite *company=CCSprite::spriteWithFile("shinobigames_logo.png");

		this->addChild(company);

		// Center the background on the screen
		company->setPosition(ccp(size.width/2, size.height/2));	// center it

        bRet = true;
    } while (0);

    return bRet;
}

CCScene* CompanyScene::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // Create our Scene
        scene = CCScene::node();
        CC_BREAK_IF(! scene);

        // Create and Add the CompanyScene Layer
        CompanyScene *layer = CompanyScene::node();
        CC_BREAK_IF(! layer);
        scene->addChild(layer);

    } while (0);

    return scene;
}

void CompanyScene::update(cocos2d::ccTime dt)
{
	unschedule(schedule_selector(CompanyScene::update));
	MenuMainScene* menuMainScene=MenuMainScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene));
}

void CompanyScene::onEnter()
{
	CCLog("CompanyScene onEnter");
	CCScene::onEnter();
}

void CompanyScene::onEnterTransitionDidFinish()
{
	CCLog("CompanyScene: transition did finish");

	// run sound manager (that forces sound loading, it takes a while)
	SoundManager::sharedSoundManager()->showVersion();

	// Start the CompanyScene stepping
	schedule(schedule_selector(CompanyScene::update));
	CCScene::onEnterTransitionDidFinish();
}

void CompanyScene::onExit()
{
	CCLog("CompanyScene onExit");
	SoundManager::sharedSoundManager()->playSoundMusicMenu();
	CCScene::onExit();
}

CompanyScene::~CompanyScene(void)
{
	CCLog("CompanyScene deconstructor");
}