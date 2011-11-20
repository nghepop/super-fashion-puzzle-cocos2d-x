#include "MenuMainScene.h"
#include "CreditsScene.h"
#include "ScoresScene.h"
#include "HowToPlayScene.h"
#include "OptionsScene.h"
//#include "ContinueGameScene.h"
#include "SoundManager.h"
#include "LoadingGameScene.h"
#include "Constants.h"

// on "init" you need to initialize your instance
bool MenuMainScene::init()
{
    bool bRet = false;
    do 
    {
        /////////////////////
        // super init first
        /////////////////////

        CC_BREAK_IF(! CCScene::init());

        // Get window size for resolution independent placement
        CCSize size = CCDirector::sharedDirector()->getWinSize();

		// Get background
		CCSprite *background=CCSprite::spriteWithFile("shared/shared_blue_background.pvr");
		background->setPosition(ccp(size.width/2, size.height/2));	// center it
		this->addChild(background);

		///////////////////////////////////////////////////////////////////////////////
		// sun_lights texture - make a moving background
		m_sun_lights_texture = CCTextureCache::sharedTextureCache()->addImage("shared/shared_sun_lights.png");

		// Create 2 sprites with the same texture for animated effect
		// 1: 
		CCSprite* sun_light_clock_wise_sprite = CCSprite::spriteWithTexture(m_sun_lights_texture);
		sun_light_clock_wise_sprite->setScale(2.0);
		sun_light_clock_wise_sprite->setPosition(ccp(240, 0));
		sun_light_clock_wise_sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(BACKGROUND_MENU_ROTATION_TIME, 360)));
		this->addChild(sun_light_clock_wise_sprite);
		// 2:
		CCSprite* sun_light_counter_clock_wise_sprite = CCSprite::spriteWithTexture(m_sun_lights_texture);
		sun_light_counter_clock_wise_sprite->setScale(2.0);
		sun_light_counter_clock_wise_sprite->setPosition(ccp(240, 0));
		sun_light_counter_clock_wise_sprite->runAction(CCRepeatForever::actionWithAction(CCRotateBy::actionWithDuration(BACKGROUND_MENU_ROTATION_TIME, -360)));
		this->addChild(sun_light_counter_clock_wise_sprite);

		// arc sprite
		CCSprite* arc= CCSprite::spriteWithFile("main_menu/menu_main_light_arch.png");	// pvr doesn't show the alpha
		arc->setPosition(ccp(240,160));
		this->addChild(arc);
		
		///////////////////////////////////////////////////////////////////////////////
		// how to HOW TO PLAY button
		CCMenuItemImage *howToPlayItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_main_how_to_play_button_released.png", // normal
			"main_menu/menu_main_how_to_play_button_pressed.png", // selected
			"main_menu/menu_main_how_to_play_button_pressed.png", // disabled
			this,
			menu_selector(MenuMainScene::howToPlayButtonPressed));

		//howToPlayItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));	<<=== NEED TO MAKE RESOLUTION INDEPENDENT
		howToPlayItem->setPosition(ccp(240, 72));

		///////////////////////////////////////////////////////////////////////////////
		// PLAY button
		CCMenuItemImage *playItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_main_play_button_released.png", // normal
			"main_menu/menu_main_play_button_pressed.png", // selected
			"main_menu/menu_main_play_button_pressed.png", // disabled
			this,
			menu_selector(MenuMainScene::playButtonPressed));

		// playItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));
		playItem->setPosition(ccp(240, 110));

		///////////////////////////////////////////////////////////////////////////////
		// SCORES button
		CCMenuItemImage *scoresItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_main_scores_button_released.png", // normal
			"main_menu/menu_main_scores_button_pressed.png", // selected
			"main_menu/menu_main_scores_button_pressed.png", // disabled
			this,
			menu_selector(MenuMainScene::scoresButtonPressed));

		// playItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));
		scoresItem->setPosition(ccp(240, 30));

		///////////////////////////////////////////////////////////////////////////////
		// OPTIONS button
		CCMenuItemImage *optionsItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_main_options_button_released.png", // normal
			"main_menu/menu_main_options_button_pressed.png", // selected
			"main_menu/menu_main_options_button_pressed.png", // disabled
			this,
			menu_selector(MenuMainScene::optionsButtonPressed));

		// playItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));
		optionsItem->setPosition(ccp(142, 30));

		///////////////////////////////////////////////////////////////////////////////
		// CREDITS button
		CCMenuItemImage *creditsItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_main_credits_button_released.png", // normal
			"main_menu/menu_main_credits_button_pressed.png", // selected
			"main_menu/menu_main_credits_button_pressed.png", // disabled
			this,
			menu_selector(MenuMainScene::creditsButtonPressed));

		// playItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 239, 47));
		creditsItem->setPosition(ccp(334, 30));


#ifdef FREE_VERSION
		CCSprite* superFashionPuzzle = CCSprite::spriteWithFile("main_menu/menu_main_super_fashion_puzzle_lite.png");
		superFashionPuzzle->setPosition(ccp(240,205));
#else
		CCSprite* superFashionPuzzle = CCSprite::spriteWithFile("main_menu/menu_main_super_fashion_puzzle.png");
		superFashionPuzzle->setPosition(ccp(240,205));
#endif
		this->addChild(superFashionPuzzle);
		
#ifdef FREE_VERSION

		///////////////////////////////////////////////////////////////////////////////
		// BUY FULL VERSION button
		CCMenuItemImage *buyFullVersionItem = CCMenuItemImage::itemFromNormalImage(
			"shared//buy_full_version_label.png", // normal
			"shared//buy_full_version_label.png", // selected
			"shared//buy_full_version_label.png", // disabled
			this,
			menu_selector(MenuMainScene::buyFullVersionButtonPressed));

		buyFullVersionItem->setPosition(ccp(480-56.5, 320-56.5));

		////////////////////////////////////////////////////////////////////////////
		// Add ALL buttons to menu
		CCMenu* pMenu = CCMenu::menuWithItems(howToPlayItem, playItem, scoresItem, optionsItem, creditsItem, buyFullVersionItem,  NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

#else
		////////////////////////////////////////////////////////////////////////////
		// Add ALL buttons to menu
		CCMenu* pMenu = CCMenu::menuWithItems(howToPlayItem, playItem, scoresItem, optionsItem, creditsItem,  NULL);
		pMenu->setPosition(CCPointZero);
		this->addChild(pMenu, 1);

#endif

        bRet = true;
    } while (0);

    return bRet;
}

#ifdef FREE_VERSION
void MenuMainScene::buyFullVersionButtonPressed(CCObject* pSender)
{
	CCLog("buyFullVersion");
	//NSString *iTunesLink = @"http://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=384946158&mt=8";
	//[[UIApplication sharedApplication] openURL:[NSURL URLWithString:iTunesLink]];
}
#endif

void MenuMainScene::howToPlayButtonPressed(CCObject* pSender)
{
	HowToPlayScene* howToPlayScene = HowToPlayScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, howToPlayScene, ccWHITE));
}

void MenuMainScene::playButtonPressed(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
	// increment number of played games
	// NSInteger gameWasStarted=[[NSUserDefaults standardUserDefaults] integerForKey:@"gameWasStarted"];
	int gameWasStarted = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameWasStarted");
	gameWasStarted++;
	// [[NSUserDefaults standardUserDefaults] setInteger:gameWasStarted forKey:@"gameWasStarted"];
	CCUserDefault::sharedUserDefault()->setIntegerForKey("gameWasStarted", gameWasStarted);
	// [[NSUserDefaults standardUserDefaults] synchronize];
#endif	
	SoundManager::sharedSoundManager()->playSoundFxTap();
	SoundManager::sharedSoundManager()->stopBackgroundMusic();
	
	// LoadingGameScene* loadingGameScene=[LoadingGameScene node];
	LoadingGameScene* loadingGameScene = LoadingGameScene::node();

	//[[CCDirector sharedDirector] replaceScene: [CCTransitionFade transitionWithDuration:TRANSITION_DURATION scene:loadingGameScene withColor:ccWHITE]];
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, loadingGameScene, ccWHITE));
}

void MenuMainScene::scoresButtonPressed(CCObject* pSender)
{
	ScoresScene* scoresScene=ScoresScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, scoresScene, ccWHITE));
}

void MenuMainScene::optionsButtonPressed(CCObject* pSender)
{
	OptionsScene* optionsScene=OptionsScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, optionsScene, ccWHITE));
}

void MenuMainScene::creditsButtonPressed(CCObject* pSender)
{
	CreditsScene* creditsScene=CreditsScene::node();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, creditsScene, ccWHITE));
}

void MenuMainScene::onEnter()
{
	CCLog("MenuMainScene onEnter");
	CCScene::onEnter();
}

void MenuMainScene::onEnterTransitionDidFinish()
{
	CCLog("MenuMainScene onEnterTransitionDidFinish");
	CCScene::onEnterTransitionDidFinish();
}

void MenuMainScene::onExit()
{
	CCLog("MenuMainScene onExit");
	CCScene::onExit();
}

MenuMainScene::~MenuMainScene(void)
{
	CCLog("MenuMainScene deconstructor");
	CCTextureCache::sharedTextureCache()->removeTexture(m_sun_lights_texture);
}