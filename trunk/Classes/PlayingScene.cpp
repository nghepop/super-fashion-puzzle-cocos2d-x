#include "PlayingScene.h"
#include "GameOverScene.h"
#include "PauseScene.h"
#include "TimeBar.h"
#include "Constants.h"
#include "SoundManager.h"

bool PlayingScene::init(void)
{
    bool bRet = false;
    do 
    {
        // super init first
        CC_BREAK_IF(! CCScene::init());

        // Get window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();

#if 1
		// board
		m_board = new Board(); //[[Board alloc] initWithPlayingScene:self];
		m_board->initWithPlayingScene(this);
		m_board->setPosition(ccp(480-320*0.5,160));
		addChild(m_board);
#endif		
		// background girls

		m_backgroundGirls = new BackgroundGirls();
		m_backgroundGirls->init();
		m_backgroundGirls->setPosition(ccp(125*0.5, 160));
		this->addChild(m_backgroundGirls);

		// add time bar
		m_timeBar = new TimeBar(); //::initWithPlayingScene(this);
		m_timeBar->autorelease();
		m_timeBar->initWithPlayingScene(this);
		m_timeBar->setPosition( ccp(125+35*0.5, 160) );
		addChild(m_timeBar);

		// score and level label
		m_score_and_level_sprite = CCSprite::spriteWithFile("game/level_and_score_texture.png");
		m_score_and_level_sprite->setPosition(ccp(120*0.5,45*0.5));
		addChild(m_score_and_level_sprite);
	
		///////////////////////////////////////////////////////////////////////////////
		// pause button
		CCMenuItemImage *pauseItem = CCMenuItemImage::itemFromNormalImage(
			"game/pause_button_released.png", // normal
			"game/pause_button_pressed.png", // selected
			"game/pause_button_released.png", // disabled
			this,
			menu_selector(PlayingScene::pauseButtonPressed));

		pauseItem->setPosition(CCPointZero);
		m_pauseMenu = CCMenu::menuWithItems(pauseItem, NULL);
		m_pauseMenu->setPosition(ccp(20, 300));
		addChild(m_pauseMenu);
#if 0
		// level label
		m_levelLabel=[[UIntegerLabel alloc] initWithFontSize:15 Offset:1 FontName:@"Helvetica" ForegroundColor:ccWHITE BackgroundColor:ccBLACK];
		[m_levelLabel setUInteger:1];
        m_levelLabel.position=ccp(36, 32);
        [self addChild:m_levelLabel];
		
		// score label
		m_scoreLabel=[[UIntegerLabel alloc] initWithFontSize:15 Offset:1 FontName:@"Helvetica" ForegroundColor:ccWHITE BackgroundColor:ccBLACK];
		[m_scoreLabel setUInteger:0];
        m_scoreLabel.position =  ccp(36, 14);
        [self addChild:m_scoreLabel];
	
		// ready sprite
		m_readySprite=[[CCSprite spriteWithFile:@"ready_texture.png"] retain];
		m_readySprite.visible=NO;
		[self addChild: m_readySprite];
#endif

		// gameover sprite
		m_gameOverSprite=CCSprite::spriteWithFile("shared/game_over_label.png");
		m_gameOverSprite->setIsVisible(true);
		m_gameOverSprite->retain();
		m_gameOverSprite->setPosition(ccp(240,250));
		addChild(m_gameOverSprite);
		
#if 0
		// used for girl transition
		m_girlTransition=[[CCSprite spriteWithFile:@"change_girl_transition.pvr"] retain];
		m_girlTransition.visible=NO;
		m_girlTransition.position=ccp(240,160);
		[m_girlTransition setOpacity:0];
		[self addChild:m_girlTransition];
#endif
		
		// game layout
		checkGameLayout();
		
		// start the game and start both FSMs
		reset();

        bRet = true;
    } while (0);

    return bRet;

}

void PlayingScene::pauseButtonPressed(CCObject* pSender)
{
	SoundManager::sharedSoundManager()->playSoundFxTap();
	if (m_state==PLAYING) changeGameState(PAUSED);
}

/*!
Reset all game components in order to start a new game.
*/
void PlayingScene::reset(void)
{
	m_backgroundGirls->setGirlNumber(0);
	//[m_board reset];
	//[m_board regenerate:0];
	m_timeBar->reset();
	//[m_levelLabel setUInteger:0];
	//[m_scoreLabel setUInteger:0];
	m_gameOverSprite->setIsVisible(false);
	//m_readySprite.position=ccp(-m_readySprite.textureRect.size.width*0.5, 150);
	m_playedTooMuch = false;
	
	// vars for "game" FSM
	m_state = READY; // STARTING_STATE_GS;
	
	changeGameState(PLAYING);	// SKIP THE READY FOR NOW
}

/*!
Used by Board. 
*/
unsigned int PlayingScene::getLevel(void)
{
	// return m_levelLabel->getUInteger());
	return 0;
}
void PlayingScene::readySequenceFinished(CCObject* pSender)
{
	changeGameState(PLAYING);
}

void PlayingScene::timeUp(void )
{
	changeGameState(GAME_OVER);
}

void PlayingScene::playedTooMuch(void )
{
	m_playedTooMuch = true;
	changeGameState(GAME_OVER);
}

/*!
Called after game over animation
*/
void PlayingScene::gameOverAnmationFinished(void)
{
	changeGameState(ENDING_STATE_GS);
}

void PlayingScene::onEnter(void)
{
	CCLog("PlayingScene onEnter");
	CCScene::onEnter();
}

void PlayingScene::onEnterTransitionDidFinish(void)
{
	CCLog("PlayingScene: transition did finish");
	CCScene::onEnterTransitionDidFinish();
}

void PlayingScene::onExit(void)
{
	CCLog("PlayingScene onExit");
	CCScene::onExit();
}
void PlayingScene::onEnterGameState(GameState state) 
{
	if (state==STARTING_STATE_GS) 
	{

	} else if (state==READY) 
	{
#if 0
		// an animation with 3 parts, and eventually a method call (in order to transitate to next state) 
#define READY_FIRST_STAGE_DURATION 1.5
#define READY_SECOND_STAGE_DURATION 0.5
#define READY_THIRD_STAGE_DURATION 0.5
		
		// part 1
		id auxFirstAction = [CCSpawn actions:
							 //[CCRotateBy actionWithDuration:READY_FIRST_AND_THIRD_STAGE_DURATION angle: 360],
							 [CCEaseElasticOut actionWithAction:[CCMoveTo actionWithDuration:READY_FIRST_STAGE_DURATION position:ccp(240,200)]],
							 //CCEaseElasticOut CCEaseBounceOut CCEaseBackOut
							 //[CCMoveTo actionWithDuration:READY_FIRST_STAGE_DURATION position:ccp(240,200)],
							 [CCFadeIn actionWithDuration:READY_FIRST_STAGE_DURATION],
							 nil];
		
		id firstAction = [CCSequence actions:
						  auxFirstAction,
						  [CCCallFunc actionWithTarget:self selector:@selector(playReadySoundFX:)], 
						  nil];
		
		// part 2, formed by 2 parts
		id auxAction = [CCScaleBy actionWithDuration: READY_SECOND_STAGE_DURATION*0.5 scale:1.4];
		id auxAction2 = [CCSequence actions:auxAction,[auxAction reverse], nil];
		id secondAction=[CCEaseSineInOut actionWithAction:auxAction2];
		
		// part 3
		id thirdAction = [CCSpawn actions:
						  [CCEaseBackIn actionWithAction:[CCMoveTo actionWithDuration:READY_THIRD_STAGE_DURATION position:ccp(480+m_readySprite.textureRect.size.width*0.5, 250)]],
						  [CCFadeOut actionWithDuration:READY_THIRD_STAGE_DURATION],
						  nil];
		
		// final animation or action
		id finalAction = [CCSequence actions:
						  [CCShow action],
						  firstAction, 
						  secondAction, 
						  thirdAction, 
						  [CCHide action],
						  //[CCPlace actionWithPosition:ccp(-m_readySprite.textureRect.size.width*0.5, 150)],
						  [CCCallFunc actionWithTarget:self selector:@selector(readySequenceFinished:)],
						  nil];
		
		[m_readySprite runAction:finalAction];
#endif		
	} 
	else if (state==PLAYING) 
	{
		SoundManager::sharedSoundManager()->playSoundMusicGame();
		
	}
	else if (state==PAUSED)
	{
		// SoundManager::sharedSoundManager()->stopBackgroundMusic();
		
	} 
	else if (state==PAUSE_BY_LOCK) 
	{
		
		
	} 
	else if (state==GAME_OVER) 
	{
		m_gameOverSprite->setPosition(ccp(240, 320+m_gameOverSprite->getTextureRect().size.height *0.5));
		SoundManager::sharedSoundManager()->playSoundFxGameOver();
		
	} 
	else if (state==ENDING_STATE_GS) 
	{
		
	} 
	else 
	{
		CCLog("Unknown Game state onEnterGameState.");
	}
}

void PlayingScene::onExitGameState(GameState state) 
{
	if (state==STARTING_STATE_GS) 
	{
		
	} 
	else if (state==READY) 
	{
		
	} 
	else if (state==PLAYING) 
	{
		SoundManager::sharedSoundManager()->stopBackgroundMusic();
		
	} 
	else if (state==PAUSED) 
	{
		
	} else if (state==PAUSE_BY_LOCK) 
	{
		
	} else if (state==GAME_OVER) 
	{
		m_timeBar->deactivate();
		
	} else if (state==ENDING_STATE_GS) 
	{
		m_gameOverSprite->setIsVisible(false);
		
	} else {
		CCLog("Unknown Game state onExitGameState.");
	}
} 


void PlayingScene::changeGameState( GameState state  )
{
	onExitGameState(m_state);

	if (m_state==STARTING_STATE_GS && state==READY) 
	{
		
	} 
	else if (m_state==READY && state==PLAYING) 
	{
		// m_readySprite->setIsVisible(false);
		m_timeBar->activate();
	
	} 
	else if (m_state==PLAYING && state==PAUSED) 
	{
		m_timeBar->deactivate();
		PauseScene* pauseScene = PauseScene::node();
		pauseScene->m_playingScene = this;
		CCDirector::sharedDirector()->pushScene(CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, pauseScene, ccWHITE));
		
	} 
	else if (m_state==PAUSED && state==PLAYING) 
	{
		m_timeBar->activate();
	
	} 
	else if (m_state==PLAYING && state==PAUSE_BY_LOCK) 
	{
		m_timeBar->deactivate();
		// PauseScene* pauseScene=[PauseScene node];
		//pauseScene.m_playingScene=self;
		//[[CCDirector sharedDirector] pushScene:pauseScene];
		
	} 
	else if (m_state==PAUSE_BY_LOCK && state==PLAYING) 
	{
		m_timeBar->activate();
	
	} 
	else if (m_state==PLAYING && state==GAME_OVER) 
	{
		#define GAME_OVER_ANIMATION_DURATION 1.5
		
		CCActionInterval* actionWithBounce = CCEaseBounceOut::actionWithAction(CCMoveTo::actionWithDuration(GAME_OVER_ANIMATION_DURATION, ccp(240,250)));

		CCActionInterval* finalAction = (CCActionInterval *) CCSequence::actions
			(
			CCShow::action(),
			CCSpawn::actions
			(
				actionWithBounce,
				CCFadeIn::actionWithDuration(GAME_OVER_ANIMATION_DURATION),
				NULL
			),
			CCCallFunc::actionWithTarget(this, callfunc_selector(PlayingScene::gameOverAnmationFinished)),
			NULL
			);

		m_gameOverSprite->runAction(finalAction);

		
	} 
	else if (m_state==GAME_OVER && state==ENDING_STATE_GS) 
	{
		GameOverScene* gameOverScene = GameOverScene::node();
		gameOverScene->m_playedTooMuch = m_playedTooMuch;
		//[gameOverScene setCurrentScore:[m_scoreLabel getUInteger]];
		//gameOverScene.m_level=[m_levelLabel getUInteger];
		gameOverScene->m_playingScene = this;
		//[self end]
		CCDirector::sharedDirector()->pushScene( (CCTransitionFade::transitionWithDuration(TRANSITION_DURATION, gameOverScene, ccWHITE)) );
	} 
	else 
	{
		CCLog("Unknown transition in Game object.");
		exit(1);
	}
	m_state=state;
	onEnterGameState(state);
}

/*!
Used by board.
*/
bool PlayingScene::isPlaying(void)
{
	return m_state==PLAYING;
}

// called when resume button in pause menu is pressed
void PlayingScene::onResume(void)
{
	CCLog("PlayingScene::onResume");	
	checkGameLayout();
	changeGameState(PLAYING);
}


/*!
Re-layout game components.
Called at start up and after options menu was used.
*/
void PlayingScene::checkGameLayout(void)
{
#if (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
	bool boardAtTheLeft = CCUserDefault::sharedUserDefault()->getBoolForKey("boardAtTheLeft");
	if (boardAtTheLeft) 
	{
		 //m_board.position=ccp(320*0.5,160);
		m_backgroundGirls->setPosition(ccp(480-125*0.5, 160));
		m_timeBar->setPosition(ccp(480-125-35*0.5, 160));
		m_score_and_level_sprite->setPosition(ccp(480-120*0.5-5,45*0.5));
		m_pauseMenu->setPosition(ccp(480-20, 300));
		//m_levelLabel->setPosition(ccp(480-89, 32));
		//m_scoreLabel->setPosition(ccp(480-89, 14));
	}
	else 
	{ // board at the right
		// m_board.position=ccp(480-320*0.5,160);
		m_backgroundGirls->setPosition(ccp(125*0.5, 160));
		m_timeBar->setPosition(ccp(125+35*0.5, 160));
		m_score_and_level_sprite->setPosition(ccp(120*0.5,45*0.5));
		m_pauseMenu->setPosition(ccp(20, 300));
		//m_levelLabel->setPosition(ccp(36, 32));
		//m_scoreLabel->setPosition(ccp(36, 14));
	}
#endif
}

PlayingScene::~PlayingScene()
{

	CCLog("deallocating PlayingScene.");
	//CC_SAFE_RELEASE(m_backgroundGirls);
	//CC_SAFE_RELEASE(m_timeBar);
	
#if 0
	CC_SAFE_RELEASE(m_pauseMenu);
	CC_SAFE_RELEASE(m_gameOverSprite);
	//CC_SAFE_RELEASE(m_readySprite);
	//CC_SAFE_RELEASE(m_scoreLabel);
	//CC_SAFE_RELEASE(m_levelLabel);
	CC_SAFE_RELEASE(m_score_and_level_sprite);
	//CC_SAFE_RELEASE(m_board);
	//CC_SAFE_RELEASE(m_girlTransition);
#endif
}
