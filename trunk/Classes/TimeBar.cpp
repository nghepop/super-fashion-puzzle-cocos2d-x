#include "PlayingScene.h"
#include "Constants.h"
#include "TimeBar.h"

// init when a game is restored from a saved file
TimeBar* TimeBar::initWithPlayingScene(PlayingScene* playingScene) 
{
//	if( (self=[super init] )) 
	{	
		// background
		CCSprite* background = CCSprite::spriteWithFile("game/time_bar_background.png");
		addChild(background);

		// time bar
		m_timeBarSprite = CCSprite::spriteWithFile("game/time_bar.png");
		m_timeBarSprite->setPosition(ccp(0,0));
		addChild(m_timeBarSprite);
		
		// foreground
		CCSprite* foreground = CCSprite::spriteWithFile("game/time_foreground.png");
		addChild(foreground);
		
		// setup time and time bar sprite
		m_duration = TIMEBAR_DURATION_IN_EASY_MODE;
		m_leftTime = m_duration;
		m_playingScene = playingScene;
	}

	TimeBar* pLayer = new TimeBar();
	if (pLayer)
	{
		pLayer->autorelease();
		return pLayer;
	}
	CC_SAFE_DELETE(pLayer);
	return NULL;
}

void TimeBar::setDuration( float duration)
{
	m_duration = duration;
	if (m_leftTime > m_duration) 
		m_leftTime = m_duration;
}

void TimeBar::activate(void) 
{
	m_isActivated=true;
}

void TimeBar::deactivate(void) 
{
	m_isActivated=false;
}

void TimeBar::onEnter(void)
{
	CCLog("TimeBar onEnter");
	schedule( schedule_selector(TimeBar::update) );
	CCNode::onEnter();
}

void TimeBar::onExit(void)
{
	CCLog("TimeBar onExit");
	unschedule( schedule_selector(TimeBar::update) );
	CCNode::onExit();
}

// m_timeBar position is in relationship with m_timeLeft and MAX_TIME
// When there is no time left, timeUp method s called in PlayingScene object
void TimeBar::update(cocos2d::ccTime dt)
{	
	if (!m_isActivated) return;

	m_leftTime = m_leftTime-dt;

	if (m_leftTime < 0) 
		m_leftTime = 0;

	// factor 1 -> posy=0 (you see a full bar)
	// factor 0 -> posy=-320 (time bar is down, not showed)
	float factor = m_leftTime/m_duration;
	m_timeBarSprite->setPosition(ccp(0, factor*320-320));

	if (m_leftTime==0) 
	{
		m_isActivated=false;
		// notify to PlayingGame
		m_playingScene->timeUp();
	}
}

void TimeBar::addSomeTime(float amount) 
{
	m_leftTime = m_leftTime+amount;
	if (m_leftTime > m_duration) 
		m_leftTime = m_duration;
}

void TimeBar::removeSomeTime(float amount) 
{
	m_leftTime = m_leftTime-amount;
	if (m_leftTime<0) m_leftTime=0;
}

/*!
 called when user selects "play again"
 */
void TimeBar::reset(void)
{
	m_isActivated = false;
	m_leftTime = TIMEBAR_DURATION_IN_EASY_MODE;
	m_timeBarSprite->setPosition(ccp(0, 0));
}


TimeBar::~TimeBar(void)
{
	CCLog("TimeBar deconstructor");
	//CC_SAFE_RELEASE(m_timeBarSprite);
}
