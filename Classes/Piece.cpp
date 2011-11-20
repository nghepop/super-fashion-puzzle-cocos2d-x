#include "Piece.h"
#include "Constants.h"

Piece::Piece(void)
{
}

Piece::~Piece(void)
{
}

// init when a game is restored from a saved file
Piece* Piece::initNormalPieceWithSpriteFrame(CCSpriteFrame* spriteFrame, unsigned int piece, unsigned int girl) 
{
	CCAssert(piece < NUMBER_OF_PIECES_PER_GIRL, "piece must be less than NUMBER_OF_PIECES_PER_GIRL.");
	CCAssert(girl < NUMBER_OF_GIRLS, "girl must be less than NUMBER_OF_GIRLS.");
	CCAssert(spriteFrame != NULL, "spriteFrame cannot be null.");
	m_girl = girl;
	m_piece = piece;
	m_isWildcard = false;
//	m_spriteFrame = spriteFrame->retain();

	Piece* pLayer = new Piece();
	if (pLayer)
	{
		pLayer->autorelease();
		return pLayer;
	}
	CC_SAFE_DELETE(pLayer);
	return NULL;

}

Piece* Piece::initWildcardWithSpriteFrame(CCSpriteFrame* spriteFrame)
{
	CCAssert(spriteFrame!=NULL, "spriteFrame cannot be null.");
	m_girl = 0;
	m_piece = 0;
	m_isWildcard = true;
	//m_spriteFrame=[spriteFrame retain];

	Piece* pLayer = new Piece();
	if (pLayer)
	{
		pLayer->autorelease();
		return pLayer;
	}
	CC_SAFE_DELETE(pLayer);
	return NULL;

}