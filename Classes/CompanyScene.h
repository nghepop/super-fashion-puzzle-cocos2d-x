
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
class CompanyScene :
	public CCScene
{
public:
	CompanyScene(void){};
	~CompanyScene(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init(void);  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene(void);
    // implement the "static node()" method manually
    LAYER_NODE_FUNC(CompanyScene);

	void update(cocos2d::ccTime dt);

public:
	void onEnter(void);
	void onExit(void);
	void onEnterTransitionDidFinish(void);
};
