#include "OptionsScene.h"
#include "MenuMainScene.h"
#include "CCRadioMenu.h"
#include "Constants.h"
#include "SoundManager.h"
//#include "FacebookManager.h"


// on "init" you need to initialize your instance
bool OptionsScene::init()
{
    bool bRet = false;
    do 
    {
        // super init first
        CC_BREAK_IF(! CCScene::init());

        // Get window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();

		// Get background
		CCSprite *background = CCSprite::spriteWithFile("shared/shared_pink_background.pvr");
		this->addChild(background);
		// Center the background on the screen
		background->setPosition(ccp(size.width/2, size.height/2));	// center it

		// Get foreground
		CCSprite *foreground=CCSprite::spriteWithFile("main_menu/menu_options_foreground.png");
		this->addChild(foreground);
		// Center the background on the screen
		foreground->setPosition(ccp(size.width/2, size.height/2));	// center it

		// spot_lights sprite continuously moving
		CCSprite* spot_lights_sprite = CCSprite::spriteWithFile("shared/shared_spot_lights.png");
		spot_lights_sprite->setScale(2.0);
		spot_lights_sprite->setPosition(ccp(400, 360));
		spot_lights_sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(BACKGROUND_ROTATION_TIME, -360)));
		this->addChild(spot_lights_sprite);

		///////////////////////////////////////////////////////////////////////////////
		// OK Button
		CCMenuItemImage *okItem = CCMenuItemImage::itemFromNormalImage(
			"shared/shared_ok_pink_released.png", // normal
			"shared/shared_ok_pink_pressed.png", // selected
			"shared/shared_ok_pink_pressed.png", // disabled
			this,
			menu_selector(OptionsScene::okButtonPressed));

		//okItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));	<<=== NEED TO MAKE RESOLUTION INDEPENDENT
		okItem->setPosition(ccp(240, 43));
		CCMenu* okMenu = CCMenu::menuWithItems(okItem, NULL);
		okMenu->setPosition(CCPointZero);
		addChild(okMenu);

		///////////////////////////////////////////////////////////////////////////////
		// Radio Buttons right
		CCMenuItem *menuItem1 = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_options_layout_right_off.png", // normal
			"main_menu/menu_options_layout_right_on.png", // selected
			"main_menu/menu_options_layout_right_off.png", // disabled
			this,
			menu_selector(OptionsScene::rightBoardRadioButtonSelected));

		//menuItem1->setPosition(ccp(240, 110));

		///////////////////////////////////////////////////////////////////////////////
		// Radio buttons left
		CCMenuItem *menuItem2 = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_options_layout_left_off.png", // normal
			"main_menu/menu_options_layout_left_on.png", // selected
			"main_menu/menu_options_layout_left_off.png", // disabled
			this,
			menu_selector(OptionsScene::leftBoardRadioButtonSelected));

		//menuItem2->setPosition(ccp(240, 30));

		CCRadioMenu* radioMenu = CCRadioMenu::radioMenuWithItems(menuItem1, menuItem2, NULL);
		radioMenu->setPosition(ccp(240, 146));
		radioMenu->alignItemsHorizontally();

		// where is board, right or left?
#if (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
		bool boardAtTheLeft = CCUserDefault::sharedUserDefault()->getBoolForKey("boardAtTheLeft");
		if (boardAtTheLeft) 
		{
			radioMenu->setSelectedRadioItem(menuItem2);
			menuItem2->selected();
		} 
		else 
		{
			radioMenu->setSelectedRadioItem(menuItem1);
			menuItem1->selected();
		}
#endif
		addChild(radioMenu);
		
		// init vars
		m_pop_at_exit=false;

        bRet = true;
    } while (0);

    return bRet;
}

void OptionsScene::setPopAtExit(void)
{
	m_pop_at_exit = true;
}

void OptionsScene::onEnter(void)
{
	CCLog("OptionsScene onEnter");
	CCScene::onEnter();
}

void OptionsScene::onEnterTransitionDidFinish(void)
{
	CCLog("OptionsScene: transition did finish");
	CCScene::onEnterTransitionDidFinish();
}

void OptionsScene::onExit(void)
{
	CCLog("OptionsScene onExit");
	CCScene::onExit();
}

void OptionsScene::okButtonPressed(CCObject* pSender)
{
	//SoundManager::sharedSoundManager()->playSoundFxTap();
	// called from pause menu
	if (m_pop_at_exit) 
	{
		CCDirector::sharedDirector()->popScene();
	}
	else // called from main menu
	{
		MenuMainScene* menuMainScene=MenuMainScene::node();
		CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));
	}
}

void OptionsScene::rightBoardRadioButtonSelected(CCObject* pSender)
{
	//[[NSUserDefaults standardUserDefaults] setBool:NO forKey:@"boardAtTheLeft"];
	//[[NSUserDefaults standardUserDefaults] synchronize];
#if (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
	CCUserDefault::sharedUserDefault()->setBoolForKey("boardAtTheLeft", false);
#endif
}

void OptionsScene::leftBoardRadioButtonSelected(CCObject* pSender)
{
	//[[NSUserDefaults standardUserDefaults] setBool:YES forKey:@"boardAtTheLeft"];
	//[[NSUserDefaults standardUserDefaults] synchronize];
#if (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
	CCUserDefault::sharedUserDefault()->setBoolForKey("boardAtTheLeft", true);
#endif
}


OptionsScene::~OptionsScene(void)
{
	CCLog("OptionsScene deconstructor");

}