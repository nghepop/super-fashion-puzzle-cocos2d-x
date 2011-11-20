#ifndef __piece_h__   
#define __piece_h__ 

#include "cocos2d.h"

using namespace cocos2d;

class Piece :
	public CCObject
{
public:
	Piece(void);
	~Piece(void);

	unsigned int m_girl;
	unsigned int m_piece;
	bool m_isWildcard;
	CCSpriteFrame* m_spriteFrame;

public:
	Piece* initNormalPieceWithSpriteFrame(CCSpriteFrame* spriteFrame, unsigned int piece, unsigned int girl);
	Piece* initWildcardWithSpriteFrame(CCSpriteFrame* spriteFrame);
	bool test(int);
};

#endif
