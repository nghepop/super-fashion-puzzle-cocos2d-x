#ifndef __playingscene_h__   
#define __playingscene_h__ 

#include "cocos2d.h"
//#include "UIntegerLabel.h"
#include "BackgroundGirls.h"
#include "Board.h"
#include "TimeBar.h"

using namespace cocos2d;

typedef enum {
	STARTING_STATE_GS,
	READY,
	PLAYING, // uses a nested state chart
	PAUSED,
	PAUSE_BY_LOCK,
	GAME_OVER,
	ENDING_STATE_GS
} GameState;

class Board;

class PlayingScene : public CCScene
{
	public:
		PlayingScene(void){};
		~PlayingScene(void);

		// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
		virtual bool init(void);  
		// there's no 'id' in cpp, so we recommand to return the exactly class pointer
		static cocos2d::CCScene* scene(void);
		// implement the "static node()" method manually
		LAYER_NODE_FUNC(PlayingScene);

		Board* m_board;
		CCSprite* m_readySprite;
		CCSprite* m_gameOverSprite;
		CCSprite* m_girlTransition; // used when current girl have to be changed
		
		CCSprite* m_score_and_level_sprite;
		//UIntegerLabel* m_scoreLabel;
		//UIntegerLabel* m_levelLabel;
		TimeBar* m_timeBar;
		BackgroundGirls* m_backgroundGirls;
		CCMenu* m_pauseMenu;
		bool m_playedTooMuch;
		
		// vars for "game" FSM
		GameState m_state;

	public:
		void onEnter(void);
		void onExit(void);
		void onEnterTransitionDidFinish(void);

		void pauseButtonPressed(CCObject* pSender);
		void readySequenceFinished(CCObject* pSender);
		void playReadySoundFX(CCObject* pSender);
		void timeUp(void);
		void gameOverAnmationFinished(void);
		void reset(void);
		void onResume(void);
		bool isPlaying(void);
		unsigned int getLevel(void);
		void checkGameLayout();
		void applicationWillResginActive(void);
		void playedTooMuch(void);

		// Game FSM managment
		void changeGameState( GameState state);
		void onEnterGameState( GameState state);
		void onExitGameState( GameState state);

};

#endif
