
#ifndef __pausescene_h__   
#define __pausescene_h__ 

#include "cocos2d.h"

using namespace cocos2d;

class PauseScene :
	public CCScene
{
public:
	PauseScene(void){};
	~PauseScene(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    LAYER_NODE_FUNC(PauseScene);

	// button callbacks
	void resumeButtonPressed(CCObject* pSender);
	void optionsButtonPressed(CCObject* pSender);
	void menuButtonPressed(CCObject* pSender);
	void howToPlayButtonPressed(CCObject* pSender);

	void onEnter(void);
	void onExit(void);
	void onEnterTransitionDidFinish(void);

	PlayingScene* m_playingScene; // used to inform it that pause is going to be resumed just before finishing this object

};

#endif
