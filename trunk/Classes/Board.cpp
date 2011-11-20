#include "Board.h"

Board::Board(void)
{
}

Board::~Board(void)
{
}

// init when a game is restored from a saved file
Board* Board::initWithPlayingScene(PlayingScene* playingScene) 
{
//	if( (self=[super init] )) 
	{	
		// board background texture
		CCSprite* board_sprite = CCSprite::spriteWithFile("game/board.png");
		addChild(board_sprite);

		// board rect
		m_boardRect = board_sprite->getTextureRect();
		
		// calculate board size
		CCSize s = board_sprite->getContentSize();
		m_boardRect = CCRectMake(-s.width / 2, -s.height / 2, s.width, s.height);

		// pieces texture		
		m_piecesSpriteSheetTexture = CCTextureCache::sharedTextureCache()->addImage("game/pieces.pvr");	
		CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();
		spriteFrameCache->addSpriteFramesWithFile("game/pieces.plist", m_piecesSpriteSheetTexture);

		// create 10*5 instances of Piece class
		m_piecesDataBase = new CCMutableArray<CCObject *>(50);

		for (unsigned int girl = 0; girl < NUMBER_OF_GIRLS; girl++) 
		{
			CCMutableArray<CCObject *> *pieces = new CCMutableArray<CCObject *>(NUMBER_OF_PIECES_PER_GIRL);

			for (unsigned int piece = 0; piece < NUMBER_OF_PIECES_PER_GIRL; piece++) 
			{
				// texture filename and path
				char originalTextureFilename[256] = {0};
				sprintf(originalTextureFilename,"g%d_f%d.png", girl+1, piece+1);

				CCSpriteFrame* spriteFrame = spriteFrameCache->spriteFrameByName(originalTextureFilename);

				//Piece* pieceInstance=[[Piece alloc] initNormalPieceWithSpriteFrame:spriteFrame Piece:piece Girl:girl];
				// Piece* pieceInstance = new Piece::initNormalPieceWithSpriteFrame(spriteFrame, piece, girl);
				Piece* pieceInstance = new Piece();
				pieceInstance->initNormalPieceWithSpriteFrame(spriteFrame, piece, girl);
				pieces->addObject(pieceInstance);
				pieceInstance->release();
			}

			m_piecesDataBase->addObject(pieces);
			pieces->release();
		}

		// wildcard piece
		CCSpriteFrame* wildcardSpriteFrame = spriteFrameCache->spriteFrameByName("wildcard.png");
		CCAssert(wildcardSpriteFrame != NULL, "wildcardSpriteFrame cannot be null.");

		// m_wildcardPiece= [[Piece alloc] initWildcardWithSpriteFrame:wildcardSpriteFrame];
		Piece * pieceInstance = new Piece();
		pieceInstance->initWildcardWithSpriteFrame(wildcardSpriteFrame);
		pieceInstance->release();

		// used by BoardPiecePlace when any of them is selected with m_selectedAction
		m_selectedTexture = CCTextureCache::sharedTextureCache()->addImage("game/selection_animated_0001.png");
		
		// used by BoardPiecePlace when any of them is selected with m_selectedSprite
		//CCAnimation* selectedAnimation=CCAnimation animationWithName:"selectedAnimation" delay:1/12.0f];
		CCAnimation* selectedAnimation = CCAnimation::animation();
		selectedAnimation->setDelay(1/12.0f);

		for (unsigned int i=1; i <= 11; i++) 
		{
			char originalTextureFilename[256] = {0};
			sprintf(originalTextureFilename,"game/selection_animated_%04d.png", i);
			selectedAnimation->addFrameWithFileName(originalTextureFilename);
		}

		// create an animation/action and add it to action container
		CCAnimate* selectedAnimationAction = CCAnimate::actionWithAnimation(selectedAnimation);
		m_selectedAction = CCRepeatForever::actionWithAction(selectedAnimationAction);
		m_selectedAction->retain();
		
		// matching starting sequence, used by BoardPiecePlace		
		// CCAnimation* startingMatchingAnimation = CCAnimation::animationWithName("startingMatchingAnimation" delay:1/12.0f);
		CCAnimation* startingMatchingAnimation = CCAnimation::animation();
		startingMatchingAnimation->setDelay(1/12.0f);

		for (unsigned int i=1; i<=5; i++) 
		{
			char originalTextureFilename[256] = {0};
			sprintf(originalTextureFilename,"game/starting_matching_sequence_%04d.png", i);
			startingMatchingAnimation->addFrameWithFileName(originalTextureFilename);
		}
		m_startingMatchingAction = CCAnimate::actionWithAnimation(startingMatchingAnimation);
		m_startingMatchingAction->retain();

		// correct matching ending sequence, used by BoardPiecePlace
		//CCAnimation* correctMatchingEndingAnimation=[CCAnimation animationWithName:@"correctMatchingEndingAnimation" delay:1/12.0f];
		CCAnimation* correctMatchingEndingAnimation = CCAnimation::animation();
		correctMatchingEndingAnimation->setDelay(1/12.0f);

		for (unsigned int i=6; i<=11; i++) 
		{
			//NSString* originalTextureFilename=[NSString stringWithFormat:@"correct_matching_ending_sequence_%04d.png", i];
			//[correctMatchingEndingAnimation addFrameWithFilename:originalTextureFilename];

			char originalTextureFilename[256] = {0};
			sprintf(originalTextureFilename,"game/correct_matching_ending_sequence_%04d.png", i);
			correctMatchingEndingAnimation->addFrameWithFileName(originalTextureFilename);

		}
		m_correctMatchingEndingAction = CCAnimate::actionWithAnimation(correctMatchingEndingAnimation);
		m_correctMatchingEndingAction->retain();

		// incorrect matching ending sequence, used by BoardPiecePlace
		// CCAnimation* incorrectMatchingEndingAnimation=[CCAnimation animationWithName:@"incorrectMatchingEndingAnimation" delay:1/12.0f];
		CCAnimation* incorrectMatchingEndingAnimation = CCAnimation::animation();
		incorrectMatchingEndingAnimation->setDelay(1/12.0f);

		for (unsigned int i=6; i<=11; i++) 
		{
			//NSString* originalTextureFilename=[NSString stringWithFormat:@"incorrect_matching_ending_sequence_%04d.png", i];
			//[incorrectMatchingEndingAnimation addFrameWithFilename:originalTextureFilename];

			char originalTextureFilename[256] = {0};
			sprintf(originalTextureFilename,"game/incorrect_matching_ending_sequence_%04d.png", i);
			incorrectMatchingEndingAnimation->addFrameWithFileName(originalTextureFilename);

		}
		m_incorrectMatchingEndingAction = CCAnimate::actionWithAnimation(incorrectMatchingEndingAnimation);
		m_incorrectMatchingEndingAction->retain();
	
		// starting matching texture, used by BoardPiecePlace
		m_startingMatchingTexture=CCTextureCache::sharedTextureCache()->addImage("game/starting_matching_sequence_0001.png");
	
#if 0
		// pivot node for BoardPiecePlace
		m_boardPiecePlacesPivotNode = BoardPiecePlacesPivotNode::node();
		m_boardPiecePlacesPivotNode->retain();
		this->addChild(m_boardPiecePlacesPivotNode);
#endif

		// add 7*7 BoardPiecePlace, each one has a node, and this node is also taken by Board
		// each one with a nodes with their position offsets to create 49 nodes
		// also store it in m_boardPiecePlaces matrix
		float correctedBoardWidth = m_boardRect.size.width-BORDER_MARGIN_IN_PIXELS*2;
		float correctedBoardHeight = m_boardRect.size.height-BORDER_MARGIN_IN_PIXELS*2;
		float pieceWidth = correctedBoardWidth/(float)NUMBER_OF_COLUMNS_IN_BOARD;
		float pieceHeight = correctedBoardHeight/(float)NUMBER_OF_ROWS_IN_BOARD;

		// m_boardPiecePlaces=[[NSMutableArray alloc] init];
		m_boardPiecePlaces = new CCMutableArray<CCObject *>(NUMBER_OF_ROWS_IN_BOARD);

		for (unsigned int column=0; column<NUMBER_OF_COLUMNS_IN_BOARD; column++) 
		{
			//NSMutableArray* rows=[[NSMutableArray alloc] init];
			CCMutableArray<CCObject *> *rows = new CCMutableArray<CCObject*>(NUMBER_OF_ROWS_IN_BOARD);

			for (unsigned int row=0; row<NUMBER_OF_ROWS_IN_BOARD; row++) 
			{
				float x=pieceWidth*0.5+pieceWidth*column-correctedBoardWidth*0.5;
				float y=pieceHeight*0.5+pieceHeight*row-correctedBoardHeight*0.5;
				CCSize size;
				size.width = pieceWidth;
				size.height = pieceHeight;
				//BoardPiecePlace* boardPiecePlace=[[BoardPiecePlace alloc] initWithBoard:self Column:column Row:row PieceSize:size];
				//boardPiecePlace.position=ccp(x,y);
				//[m_boardPiecePlacesPivotNode addChild:boardPiecePlace];
				//[rows addObject:boardPiecePlace];
				//[boardPiecePlace release];
			}
			//[m_boardPiecePlaces addObject:rows];
			rows->release();
		}

		// init vars
		m_playingScene = playingScene;
	}

	Board* pLayer = new Board();
	if (pLayer)
	{
		pLayer->autorelease();
		return pLayer;
	}
	CC_SAFE_DELETE(pLayer);
	return NULL;
}
