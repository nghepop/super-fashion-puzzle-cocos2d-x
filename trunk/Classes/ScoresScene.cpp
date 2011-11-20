#include "ScoresScene.h"
#include "MenuMainScene.h"
#include "SoundManager.h"
//#include "CCRadioMenu.h"
#include "Constants.h"


// on "init" you need to initialize your instance
bool ScoresScene::init()
{
    bool bRet = false;
    do 
    {
        // super init first
        CC_BREAK_IF(! CCScene::init());

        // Get window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();

		// Get background
		CCSprite *background=CCSprite::spriteWithFile("shared/shared_pink_background.pvr");
		this->addChild(background);
		background->setPosition(ccp(size.width/2, size.height/2));	// center it

		// foreground
		CCSprite *foreground=CCSprite::spriteWithFile("main_menu/menu_scores_foreground.png");
		this->addChild(foreground);
		foreground->setPosition(ccp(size.width/2, size.height/2));	// center it

		///////////////////////////////////////////////////////////////////////////////
		// OK button
		CCMenuItemImage *okItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_scores_ok_pink_wide_button_released.png", // normal
			"main_menu/menu_scores_ok_pink_wide_button_pressed.png", // selected
			"main_menu/menu_scores_ok_pink_wide_button_pressed.png", // disabled
			this,
			menu_selector(ScoresScene::okButtonPressed));

		//howToPlayItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));	<<=== NEED TO MAKE RESOLUTION INDEPENDENT
		okItem->setPosition(ccp(337, 33));

		///////////////////////////////////////////////////////////////////////////////
		// reset local scores button
		CCMenuItemImage *resetLocalItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_scores_reset_local_button_released.png", // normal
			"main_menu/menu_scores_reset_local_button_pressed.png", // selected
			"main_menu/menu_scores_reset_local_button_pressed.png", // disabled
			this,
			menu_selector(ScoresScene::resetLocalButtonPressed));

		// playItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));
		resetLocalItem->setPosition(ccp(147, 33));


		////////////////////////////////////////////////////////////////////////////
		// Add buttons to menu
		CCMenu* pMenu = CCMenu::menuWithItems(okItem, resetLocalItem,  NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

        bRet = true;
    } while (0);

    return bRet;
}

void ScoresScene::onEnter(void)
{
	CCLog("ScoresScene onEnter");
	CCScene::onEnter();
}

void ScoresScene::onEnterTransitionDidFinish(void)
{
	CCLog("ScoresScene: transition did finish");
	CCScene::onEnterTransitionDidFinish();
}

void ScoresScene::onExit(void)
{
	CCLog("ScoresScene onExit");
	CCScene::onExit();
}

// OK - return to main menu scene
void ScoresScene::okButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	MenuMainScene* menuMainScene = MenuMainScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));

}

// Reset Local scores
void ScoresScene::resetLocalButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	MenuMainScene* menuMainScene = MenuMainScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));
}

ScoresScene::~ScoresScene(void)
{
	CCLog("ScoresScene deconstructor");
}
