#pragma once
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
class OptionsScene :
	public CCScene
{
public:
	OptionsScene(void){};
	~OptionsScene(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    LAYER_NODE_FUNC(OptionsScene);
	// button callbacks
	void okButtonPressed(CCObject* pSender);
	void rightBoardRadioButtonSelected(CCObject* pSender);
	void leftBoardRadioButtonSelected(CCObject* pSender);

	void onEnter(void);
	void onExit(void);
	void onEnterTransitionDidFinish(void);

	void setPopAtExit(void);
	
	bool m_pop_at_exit;
};
