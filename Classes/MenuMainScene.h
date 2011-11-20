#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
class MenuMainScene :
	public CCScene
{
public:
	MenuMainScene(void){};
	~MenuMainScene(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    LAYER_NODE_FUNC(MenuMainScene);
	// button callbacks
	void howToPlayButtonPressed(CCObject* pSender);
	void playButtonPressed(CCObject* pSender);
	void scoresButtonPressed(CCObject* pSender);
	void optionsButtonPressed(CCObject* pSender);
	void creditsButtonPressed(CCObject* pSender);
#ifdef FREE_VERSION
	void buyFullVersionButtonPressed(CCObject* pSender);
#endif

public:
	void onEnter(void);
	void onExit(void);
	void onEnterTransitionDidFinish(void);

private: 
	CCTexture2D* m_sun_lights_texture;
};
