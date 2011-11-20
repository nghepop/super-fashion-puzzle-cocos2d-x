
#ifndef __timebar_h__   
#define __timebar_h__ 

#include "cocos2d.h"

class PlayingScene;

using namespace cocos2d;

class TimeBar :
	public CCNode
{
public:
	TimeBar(void){};
	~TimeBar(void);
	
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    //virtual bool init();  
	TimeBar* initWithPlayingScene(PlayingScene* playingScene);
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    //LAYER_NODE_FUNC(TimeBar);

// void dealloc;
void update(cocos2d::ccTime dt);
void activate(void);
void deactivate(void);
void reset(void);
void setDuration( float duration);
void addSomeTime(float amount);
void removeSomeTime(float amount);
void onEnter(void);
void onExit(void);

private:
	float m_leftTime;
	CCSprite* m_timeBarSprite;
	bool m_isActivated;
	PlayingScene* m_playingScene;
	float m_duration;

};

#endif
