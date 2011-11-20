
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;

class GameOverScene : public cocos2d::CCScene
{
public:
	GameOverScene(void){};
	~GameOverScene(void);

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
	    static cocos2d::CCScene* scene();
    // implement the "static node()" method manually
    LAYER_NODE_FUNC(GameOverScene);
	
	void goToMainMenu(void);
	void goToPlayAgain(void);

	// button handlers
	void playAgainButtonPressed(CCObject* pSender);
	void menuButtonPressed(CCObject* pSender);

#ifdef FREE_VERSION
	void buyFullVersionButtonPressed(CCObject* pSender);	
#endif

	// modify lables information
	void setHighScore(unsigned int highScore);
	void setCurrentScore(unsigned int currentScore);

	bool m_playedTooMuch;
	PlayingScene* m_playingScene;

protected:

	unsigned int m_level;
	bool m_scoreWasSentProperly;
	bool m_facebookWallWasWrittenProperly;

};
