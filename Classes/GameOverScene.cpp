#include "MenuMainScene.h"
#include "Constants.h"
#include "LoadingGameScene.h"
#include "PlayingScene.h"
#include "GameOverScene.h"
#include "SoundManager.h"

bool GameOverScene::init(void)
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

		// Game over label sprite
		CCSprite *gameOverLabel = CCSprite::spriteWithFile("shared/game_over_label.png");
		gameOverLabel->setPosition(ccp(240, 250));
		this->addChild(gameOverLabel);

		// Game over text sprite
		CCSprite *gameOverText = CCSprite::spriteWithFile("main_menu/menu_game_over_text.png");
		gameOverText->setPosition(ccp(145, 145));
		this->addChild(gameOverText);

		///////////////////////////////////////////////////////////////////////////////
		// Play Again Button
		CCMenuItemImage *playAgainItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_game_over_play_again_button_released.png", // normal
			"main_menu/menu_game_over_play_again_button_pressed.png", // selected
			"main_menu/menu_game_over_play_again_button_released.png", // disabled
			this,
			menu_selector(GameOverScene::playAgainButtonPressed));

		playAgainItem->setPosition(ccp(62, 35));
		CCMenu* playAgainMenu = CCMenu::menuWithItems(playAgainItem, NULL);
		playAgainMenu->setPosition(CCPointZero);
		addChild(playAgainMenu);
		///////////////////////////////////////////////////////////////////////////////

		///////////////////////////////////////////////////////////////////////////////
		// Main Menu Button
		CCMenuItemImage *menuItem = CCMenuItemImage::itemFromNormalImage(
			"main_menu/menu_game_over_menu_button_released.png", // normal
			"main_menu/menu_game_over_menu_button_pressed.png", // selected
			"main_menu/menu_game_over_menu_button_released.png", // disabled
			this,
			menu_selector(GameOverScene::menuButtonPressed));

		menuItem->setPosition(ccp(417, 35));
		CCMenu* menuMenu = CCMenu::menuWithItems(menuItem, NULL);
		menuMenu->setPosition(CCPointZero);
		addChild(menuMenu);
		///////////////////////////////////////////////////////////////////////////////

#ifdef FREE_VERSION
		///////////////////////////////////////////////////////////////////////////////
		// Buy Full Version Button
		CCMenuItemImage *buyFullVersionItem = CCMenuItemImage::itemFromNormalImage(
			"shared/buy_full_version_label.png", // normal
			"shared/buy_full_version_label.png", // selected
			"shared/buy_full_version_label.png", // disabled
			this,
			menu_selector(GameOverScene::buyFullVersionButtonPressed));
		
		buyFullVersionItem->setPosition(ccp(480-56.5, 320-56.5));
		CCMenu* buyFullVersionMenu = CCMenu::menuWithItems(buyFullVersionItem, NULL);
		buyFullVersionMenu->setPosition(CCPointZero);
		addChild(buyFullVersionMenu);
		///////////////////////////////////////////////////////////////////////////////
#endif
		// init vars
		m_playingScene = new PlayingScene();
		m_playedTooMuch = false;

        bRet = true;
    } while (0);

    return bRet;
}

#ifdef FREE_VERSION
void GameOverScene::buyFullVersionButtonPressed(CCObject* pSender)
{
	CCLog("GameOverScene: buyFullVersion");
	//NSString *iTunesLink = @"http://phobos.apple.com/WebObjects/MZStore.woa/wa/viewSoftware?id=384946158&mt=8";
	//[[UIApplication sharedApplication] openURL:[NSURL URLWithString:iTunesLink]];
}
#endif


void GameOverScene::playAgainButtonPressed(CCObject* pSender)
{
	CCLog("GameOverScene:playAgainButtonPressed");
	goToPlayAgain();
}

void GameOverScene::goToPlayAgain(void)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
	int gameWasStarted = CCUserDefault::sharedUserDefault()->getIntegerForKey("gameWasStarted");
	gameWasStarted++;
	CCUserDefault::sharedUserDefault()->setIntegerForKey("gameWasStarted", gameWasStarted);
#endif

	SoundManager::sharedSoundManager()->playSoundFxTap();
	m_playingScene->reset();
	CCDirector::sharedDirector()->popScene();  // remove gameover scene and replace playing scene	
}

void GameOverScene::menuButtonPressed(CCObject* pSender)
{
	CCLog("GameOverScene: menuButtonPressed");
	goToMainMenu();
}

void GameOverScene::goToMainMenu(void)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	CCDirector::sharedDirector()->popScene();  // remove gameover scene and replace playing scene
	MenuMainScene* menuMainScene=MenuMainScene::node();
	SoundManager::sharedSoundManager()->playSoundMusicMenu();
	CCDirector::sharedDirector()->replaceScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, menuMainScene, ccWHITE));
}


GameOverScene::~GameOverScene()
{
	CCLog("GameOverScene: destructor");
#if 0
	if (m_playingScene)
		delete m_playingScene;
#endif
}