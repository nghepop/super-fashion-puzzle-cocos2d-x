#ifndef __backgroundgirls_h__   
#define __backgroundgirls_h__ 

#include "cocos2d.h"

using namespace cocos2d;

class BackgroundGirls :
	public CCNode
{
public:
	BackgroundGirls(void){};
	~BackgroundGirls(void);

	void onEnter(void);
	void onExit(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	//static cocos2d::CCScene* scene(void);
	// implement the "static node()" method manually
	//LAYER_NODE_FUNC(BackgroundGirls);

	void setGirlNumber( unsigned int );
	void incrementGirl(void);

	// CCMutableArray<CCSpriteFrame*> *m_pobFrames;
	CCMutableArray<CCTexture2D*> *m_spriteSheetTextures;
	CCMutableArray<CCRepeatForever*> *m_differentGirlsActions;
	unsigned int m_currentGirlNumber;
	CCSprite* m_girlSprite;
};

#endif