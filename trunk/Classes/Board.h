#ifndef __board_h__   
#define __board_h__ 

#include "cocos2d.h"
#include "Piece.h"
//#include "BoardPiecePlace.h"
#include "BoardPiecePlacesPivotNode.h"
#include "Constants.h"
#include "PlayingScene.h"

using namespace cocos2d;

class PlayingScene;

typedef enum {
	REGENERATING_BOARD,
	CHANGING_GIRL,
	WAITING_USER_INPUT_WO_CHIP_SELECTED,
	WAITING_USER_INPUT_WITH_CHIP_SELECTED,
} BoardState;

class Board :
	public CCNode, public CCTargetedTouchDelegate
{
public:
	Board(void);
	~Board(void);

	PlayingScene* m_playingScene;
	CCMutableArray<CCObject *> *m_boardPiecePlaces;
	CCMutableArray<CCObject *> *m_piecesDataBase;
	CCTexture2D* m_piecesSpriteSheetTexture;
	Piece* m_wildcardPiece;
	BoardPiecePlacesPivotNode* m_boardPiecePlacesPivotNode;
	CCRect m_boardRect;
	
	// Used by BoardPiecePlace to create selection and matching animations
	CCTexture2D* m_selectedTexture;
	CCRepeatForever* m_selectedAction;
	CCTexture2D* m_startingMatchingTexture;
	CCAnimate* m_startingMatchingAction;
	CCAnimate* m_correctMatchingEndingAction;
	CCAnimate* m_incorrectMatchingEndingAction;
	
	// FSM
	//BoardPiecePlace* m_selectedBoardPiecePlace;
	unsigned int m_numberOfRegenerations;
	unsigned int m_numberOfMatches;
	BoardState m_state;

public:

Board* initWithPlayingScene(PlayingScene* playingScene);
//BoardPiecePlace* getBoardPiecePlaceAtColumn:(unsigned int)column Row:(unsigned int)row;
Piece* getPiece(unsigned int piece, unsigned int girl);
void reset(void);
void regenerate(unsigned int level);
void inTheMiddleOfRegenerationSequenceCallback(CCObject* pSender);
void regenerationSquenceWasDone(CCObject* pSender);
void inTheMiddleOfChangeGirlSequenceCallback(CCObject* pSender);
void changeGirlSequenceWasDoneCallback(CCObject* pSender);
//void correctMatchWasDone:(bool)withWildcard BoardPiecePlace(BoardPiecePlace* boardPiecePlace);
//void incorrectMatchWasDone(BoardPiecePlace* boardPiecePlace);
/// NSUInteger getNumberOfWildcardsForLevel:(NSUInteger)level;

// Used by BoardPiecePlace
bool canBoardPiecePlaceBeSelected;
//void boardPiecePlaceWasSelected(BoardPiecePlace* boardPiecePlace);

// FSM managment
void changeBoardState(BoardState state);
void onEnterBoardState(BoardState state);
void onExitBoardState(BoardState state);

};

#endif
