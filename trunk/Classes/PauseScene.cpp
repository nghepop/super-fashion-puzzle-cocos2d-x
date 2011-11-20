#include "PlayingScene.h"
#include "PauseScene.h"
#include "HowToPlayScene.h"
#include "OptionsScene.h"
#include "MenuMainScene.h"
#include "Constants.h"
#include "SoundManager.h"

// on "init" you need to initialize your instance
bool PauseScene::init()
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

		// spot_lights sprite continuously moving
		CCSprite* spot_lights_sprite = CCSprite::spriteWithFile("shared/shared_spot_lights.png");
		spot_lights_sprite->setScale(2.0);
		spot_lights_sprite->setPosition(ccp(400, 360));
		spot_lights_sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(BACKGROUND_ROTATION_TIME, -360)));
		this->addChild(spot_lights_sprite);

		// Get foreground
		CCSprite *foreground=CCSprite::spriteWithFile("in_game_menu/menu_pause_foreground.png");
		this->addChild(foreground);
		// Center the background on the screen
		foreground->setPosition(ccp(size.width/2, size.height/2));	// center it

		///////////////////////////////////////////////////////////////////////////////
		// Resume Button
		CCMenuItemImage *resumeItem = CCMenuItemImage::itemFromNormalImage(
			"in_game_menu//menu_pause_resume_button_released.png", // normal
			"in_game_menu//menu_pause_resume_button_pressed.png", // selected
			"in_game_menu//menu_pause_resume_button_released.png", // disabled
			this,
			menu_selector(PauseScene::resumeButtonPressed));

		//okItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));	<<=== NEED TO MAKE RESOLUTION INDEPENDENT
		resumeItem->setPosition(ccp(240, 211));
		CCMenu* resumeMenu = CCMenu::menuWithItems(resumeItem, NULL);
		resumeMenu->setPosition(CCPointZero);
		addChild(resumeMenu);
		///////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////
		// How to Play Button
		CCMenuItemImage *howToPlayItem = CCMenuItemImage::itemFromNormalImage(
			"in_game_menu//menu_pause_how_to_play_button_released.png", // normal
			"in_game_menu//menu_pause_button_how_to_play_pressed.png", // selected
			"in_game_menu//menu_pause_how_to_play_button_released.png", // disabled
			this,
			menu_selector(PauseScene::howToPlayButtonPressed));

		howToPlayItem->setPosition(ccp(240, 156));
		CCMenu* howToPlayMenu = CCMenu::menuWithItems(howToPlayItem, NULL);
		howToPlayMenu->setPosition(CCPointZero);
		addChild(howToPlayMenu);
		///////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////
		// Options Button
		CCMenuItemImage *optionsItem = CCMenuItemImage::itemFromNormalImage(
			"in_game_menu//menu_pause_options_button_released.png", // normal
			"in_game_menu//menu_pause_options_button_pressed.png", // selected
			"in_game_menu//menu_pause_resume_button_released.png", // disabled
			this,
			menu_selector(PauseScene::optionsButtonPressed));

		optionsItem->setPosition(ccp(240, 101));
		CCMenu* optionsMenu = CCMenu::menuWithItems(optionsItem, NULL);
		optionsMenu->setPosition(CCPointZero);
		addChild(optionsMenu);
		///////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////
		// Menu Button
		CCMenuItemImage *menuItem = CCMenuItemImage::itemFromNormalImage(
			"in_game_menu//menu_pause_menu_button_released.png", // normal
			"in_game_menu//menu_pause_menu_button_pressed.png", // selected
			"in_game_menu//menu_pause_menu_button_released.png", // disabled
			this,
			menu_selector(PauseScene::menuButtonPressed));

		menuItem->setPosition(ccp(240, 43));
		CCMenu* menuMenu = CCMenu::menuWithItems(menuItem, NULL);
		menuMenu->setPosition(CCPointZero);
		addChild(menuMenu);
		///////////////////////////////////////////////////////////////////////////////

		m_playingScene = NULL;

        bRet = true;
    } while (0);

    return bRet;
}

void PauseScene::onEnter(void)
{
	CCLog("PauseScene onEnter");
	CCScene::onEnter();
}

void PauseScene::onEnterTransitionDidFinish(void)
{
	CCLog("PauseScene: transition did finish");
	CCScene::onEnterTransitionDidFinish();
}

void PauseScene::onExit(void)
{
	CCLog("PauseScene onExit");
	CCScene::onExit();
}

void PauseScene::resumeButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	CCDirector::sharedDirector()->popScene();
	m_playingScene->onResume();
}

void PauseScene::optionsButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	OptionsScene* optionsScene=OptionsScene::node();
	optionsScene->setPopAtExit();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, optionsScene, ccWHITE));
}

void PauseScene::menuButtonPressed(CCObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
	MenuMainScene* menuMainScene=MenuMainScene::node();
	SoundManager::sharedSoundManager()->playSoundMusicMenu();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));
}

void PauseScene::howToPlayButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	HowToPlayScene* howToPlayScene=HowToPlayScene::node();
	CCDirector::sharedDirector()->pushScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, howToPlayScene, ccWHITE));
}

PauseScene::~PauseScene(void)
{
	CCLog("PauseScene deconstructor");
}