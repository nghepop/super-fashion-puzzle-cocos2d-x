#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
class CreditsScene :
	public CCScene
{
public:
	CreditsScene(void){};
	~CreditsScene(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    LAYER_NODE_FUNC(CreditsScene);

	// button callbacks
	void sendFeedbackButtonPressed(CCObject* pSender);
	void okButtonPressed(CCObject* pSender);

	void onEnter(void);
	void onExit(void);
	void onEnterTransitionDidFinish(void);


private: 
	CCTexture2D* m_rectangle_lights_texture;
};
