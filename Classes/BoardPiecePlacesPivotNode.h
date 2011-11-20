#ifndef __boardpieceplacespivotnode_h__   
#define __boardpieceplacespivotnode_h__ 

#include "cocos2d.h"

using namespace cocos2d;

class BoardPiecePlacesPivotNode :
	public CCNode, public CCRGBAProtocol
{
public:
	BoardPiecePlacesPivotNode(void);
	~BoardPiecePlacesPivotNode(void);
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

	CCMutableArray<CCObject *> *m_boardPiecePlaces;

};

#endif
