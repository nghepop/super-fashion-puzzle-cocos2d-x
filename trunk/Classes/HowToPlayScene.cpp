#include "HowToPlayScene.h"
#include "MenuMainScene.h"
#include "SoundManager.h"
#include "Constants.h"

// on "init" you need to initialize your instance
bool HowToPlayScene::init()
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

		// spot_lights sprite continuously moving
		CCSprite* spot_lights_sprite = CCSprite::spriteWithFile("shared/shared_spot_lights.png");
		spot_lights_sprite->setScale(2.0);
		spot_lights_sprite->setPosition(ccp(400, 360));
		spot_lights_sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(BACKGROUND_ROTATION_TIME, -360)));
		this->addChild(spot_lights_sprite);

		///////////////////////////////////////////////////////////////////////////////
		// how to OK button
		CCMenuItemImage *okItem = CCMenuItemImage::itemFromNormalImage(
			"shared/shared_ok_pink_released.png", // normal
			"shared/shared_ok_pink_pressed.png", // selected
			"shared/shared_ok_pink_pressed.png", // disabled
			this,
			menu_selector(HowToPlayScene::okButtonPressed));

		//howToPlayItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));	<<=== NEED TO MAKE RESOLUTION INDEPENDENT
		okItem->setPosition(ccp(240, 43)); //<<=== NEED TO MAKE RESOLUTION INDEPENDENT

		///////////////////////////////////////////////////////////////////////////////
		// LEFT button
		CCMenuItemImage *leftArrowItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_how_to_play_left_arrow_released.png", // normal
			"main_menu/menu_how_to_play_left_arrow_pressed.png", // selected
			"main_menu/menu_how_to_play_left_arrow_pressed.png", // disabled
			this,
			menu_selector(HowToPlayScene::leftArrowButtonPressed));

		// playItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));
		leftArrowItem->setPosition(ccp(150, 43));

		///////////////////////////////////////////////////////////////////////////////
		// RIGHT button
		CCMenuItemImage *rightArrowItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_how_to_play_right_arrow_released.png", // normal
			"main_menu/menu_how_to_play_right_arrow_pressed.png", // selected
			"main_menu/menu_how_to_play_right_arrow_pressed.png", // disabled
			this,
			menu_selector(HowToPlayScene::rightArrowButtonPressed));

		// playItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));
		rightArrowItem->setPosition(ccp(480-150, 43));

		////////////////////////////////////////////////////////////////////////////
		// Add all buttons to menu
		CCMenu* pMenu = CCMenu::menuWithItems(okItem, leftArrowItem, rightArrowItem,  NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

		m_pop_at_exit=false;
		
        bRet = true;
    } while (0);

    return bRet;
}

void HowToPlayScene::setPopAtExit(void)
{
	m_pop_at_exit = true;
}

void HowToPlayScene::onEnter(void)
{
	CCLog("HowToPlayScene onEnter");
	CCScene::onEnter();
}

void HowToPlayScene::onEnterTransitionDidFinish(void)
{
	CCLog("HowToPlayScene: transition did finish");
	CCScene::onEnterTransitionDidFinish();
}

void HowToPlayScene::onExit(void)
{
	CCLog("HowToPlayScene onExit");
	CCScene::onExit();
}

// OK - return to main menu scene
void HowToPlayScene::okButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();

	// called from pause menu
	if (m_pop_at_exit) 
	{
		CCDirector::sharedDirector()->popScene();
	}
	else	// called from the main menu
	{
		MenuMainScene* menuMainScene = MenuMainScene::node();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));
	}
}

// LEFT arrow
void HowToPlayScene::leftArrowButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	MenuMainScene* menuMainScene = MenuMainScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));
}

// RIGHT arrow
void HowToPlayScene::rightArrowButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	MenuMainScene* menuMainScene = MenuMainScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));
}

HowToPlayScene::~HowToPlayScene(void)
{
	CCLog("HowToPlayScene deconstructor");
}