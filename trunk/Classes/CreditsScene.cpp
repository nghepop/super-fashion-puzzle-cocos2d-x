#include "CreditsScene.h"
#include "MenuMainScene.h"
#include "Constants.h"
#include "SoundManager.h"

// on "init" you need to initialize your instance
bool CreditsScene::init()
{
    bool bRet = false;
    do 
    {
        // super init first
        CC_BREAK_IF(! CCScene::init());

        // Get window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();
		
		// Get background 512x512 for pvr
		CCSprite *background=CCSprite::spriteWithFile("shared/shared_blue_background.pvr");

		this->addChild(background);

		// Center the background on the screen
		background->setPosition(ccp(size.width/2, size.height/2));	// center it

		CCSprite *foreground=CCSprite::spriteWithFile("main_menu/menu_credits_foreground.png");

		this->addChild(foreground);

		// Center the background on the screen
		foreground->setPosition(ccp(size.width/2, size.height/2));	// center it

		///////////////////////////////////////////////////////////////////////////////
		// sun_lights texture - make a moving background
		m_rectangle_lights_texture = CCTextureCache::sharedTextureCache()->addImage("shared/shared_rectangle_lights.png");

		// 1:  3 sprites with the same texture
		CCSprite* rectangle_1_light_clock_wise_sprite = CCSprite::spriteWithTexture(m_rectangle_lights_texture);
		rectangle_1_light_clock_wise_sprite->setScale(1.0);
		rectangle_1_light_clock_wise_sprite->setPosition(ccp(0, 100));
		rectangle_1_light_clock_wise_sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(BACKGROUND_ROTATION_TIME, -360)));
		this->addChild(rectangle_1_light_clock_wise_sprite);
		// 2:
		CCSprite* rectangle_2_light_clock_wise_sprite = CCSprite::spriteWithTexture(m_rectangle_lights_texture);
		rectangle_2_light_clock_wise_sprite->setScale(1.0);
		rectangle_2_light_clock_wise_sprite->setPosition(ccp(350, -70));
		rectangle_2_light_clock_wise_sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(BACKGROUND_ROTATION_TIME, -360)));
		this->addChild(rectangle_2_light_clock_wise_sprite);
		// 3:
		CCSprite* rectangle_3_light_clock_wise_sprite = CCSprite::spriteWithTexture(m_rectangle_lights_texture);
		rectangle_3_light_clock_wise_sprite->setScale(1.0);
		rectangle_3_light_clock_wise_sprite->setPosition(ccp(480, 360));
		rectangle_3_light_clock_wise_sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(BACKGROUND_ROTATION_TIME, -360)));
		this->addChild(rectangle_3_light_clock_wise_sprite);

		// OK button
		CCMenuItemImage *okItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_credits_ok_blue_button_released.png", // normal
			"main_menu/menu_credits_ok_blue_button_pressed.png", // selected
			"main_menu/menu_credits_ok_blue_button_pressed.png", // disabled
			this,
			menu_selector(CreditsScene::okButtonPressed));

		//howToPlayItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));	<<=== NEED TO MAKE RESOLUTION INDEPENDENT
		okItem->setPosition(ccp(360, 42));

		///////////////////////////////////////////////////////////////////////////////
		// FEEDBACK button
		CCMenuItemImage *sendFeedbackItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_credits_send_feedback_button_released.png", // normal
			"main_menu/menu_credits_send_feedback_button_pressed.png", // selected
			"main_menu/menu_credits_send_feedback_button_pressed.png", // disabled
			this,
			menu_selector(CreditsScene::sendFeedbackButtonPressed));

		// playItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));
		sendFeedbackItem->setPosition(ccp(160, 42));

		////////////////////////////////////////////////////////////////////////////
		// Add buttons to menu
		CCMenu* pMenu = CCMenu::menuWithItems(okItem, sendFeedbackItem,  NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

        bRet = true;
    } while (0);

    return bRet;
}

// FEEDBACK - Send to URL
void CreditsScene::sendFeedbackButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	MenuMainScene* menuMainScene = MenuMainScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));

}

// OK - return to main menu scene
void CreditsScene::okButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	MenuMainScene* menuMainScene = MenuMainScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));
}

void CreditsScene::onEnter(void)
{
	CCLog("CreditsScene onEnter");
	CCScene::onEnter();
}

void CreditsScene::onEnterTransitionDidFinish(void)
{
	CCLog("CreditsScene: transition did finish");
	CCScene::onEnterTransitionDidFinish();
}

void CreditsScene::onExit(void)
{
	CCLog("CreditsScene onExit");
	CCScene::onExit();
}

CreditsScene::~CreditsScene(void)
{
	CCLog("CreditsScene deconstructor");
	CCTextureCache::sharedTextureCache()->removeTexture(m_rectangle_lights_texture);
}