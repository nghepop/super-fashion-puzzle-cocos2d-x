#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
class ScoresScene :
	public CCScene
{
public:
	ScoresScene(void){};
	~ScoresScene(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    LAYER_NODE_FUNC(ScoresScene);
	// button callbacks
	void okButtonPressed(CCObject* pSender);
	void resetLocalButtonPressed(CCObject* pSender);

	void onEnter(void);
	void onExit(void);
	void onEnterTransitionDidFinish(void);
};
