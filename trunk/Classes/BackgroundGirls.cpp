
#include "BackgroundGirls.h"
#include "Constants.h"


bool BackgroundGirls::init(void)
{

    bool bRet = false;
    do 
    {
        // super init first
        //CC_BREAK_IF(! CCScene::init());

        // Get window size
        CCSize size = CCDirector::sharedDirector()->getWinSize();

		// init vars
		m_currentGirlNumber=0;
		
		// frame indices and its size (copied from a text file)
		unsigned int framesIndices[]={1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 9, 8, 1, 8, 9, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 9, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 10, 11, 10, 7, 7, 7, 7, 7, 7, 7, 6, 5, 4, 3, 2, 1, 8, 9, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 9, 8, 1, 8, 9, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 10, 11, 10, 11, 10, 11, 10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 10, 11, 10, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 4, 5, 6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 10, 11, 10, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 6, 5, 4, 3, 2, 1};
		unsigned int framesIndicesNumberOfElements=sizeof(framesIndices)/sizeof(framesIndices[0]);
		
		// test frame indices, all must be between 1 and 11
		for (unsigned int i=0; i<framesIndicesNumberOfElements; i++) 
		{
			if (framesIndices[i]<1 || framesIndices[i]>NUMBER_OF_FRAMES_PER_GIRL) 
			{
				CCLog("Frame indices must be between 1 and 11.");
				exit(1);
			}
		}
		
		// load all sprite sheets and create animations
		m_differentGirlsActions = new CCMutableArray<CCRepeatForever *>;
		m_spriteSheetTextures = new CCMutableArray<CCTexture2D *>;

    // IMPORTANT:
    // The sprite frames will be cached AND RETAINED, and they won't be released unless you call
    //     CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames);
		CCSpriteFrameCache* spriteFrameCache = CCSpriteFrameCache::sharedSpriteFrameCache();

		for (unsigned int girl=0; girl < NUMBER_OF_GIRLS; girl++) 
		{
		
			// if odd (1 texture/coordinate for 2 girls)
			if (girl%2==0) 
			{
				// texture filename and path
				char name[256] = {0};
				sprintf(name,"game/girls/girls_%02d_%02d.pvr", girl+1, girl+2);
				std::string texturePathAndFilename = name;
				texturePathAndFilename = CCFileUtils::fullPathFromRelativePath(texturePathAndFilename.c_str());
				
				// load texture	
				CCTexture2D* texture = new CCTexture2D;
				texture->initWithPVRFile(texturePathAndFilename.c_str() );
				m_spriteSheetTextures->addObject(texture);
				texture->release();
				
				// load sprite sheet coordinates file
				char plistFilename[256] = {0};
				sprintf(plistFilename, "game/girls/girls_%02d_%02d.plist", girl+1, girl+2);
				std:string plistPathAndFilename = plistFilename;
				plistPathAndFilename = CCFileUtils::fullPathFromRelativePath(plistPathAndFilename.c_str());
				spriteFrameCache->addSpriteFramesWithFile(plistPathAndFilename.c_str(), texture);

			}
			// add as many textures as frame indices we have
			CCAnimation* girlAnimation = CCAnimation::animation();
			girlAnimation->setDelay(1/12.0f);
			char originalTextureFilename[256]=  {0};
			for (unsigned int frameIndex=0; frameIndex < framesIndicesNumberOfElements; frameIndex++) 
			{
				sprintf(originalTextureFilename, "girl_%02d_%04d.png", girl+1, framesIndices[frameIndex]);
				CCSpriteFrame* spriteFrame = spriteFrameCache->spriteFrameByName(originalTextureFilename);
				girlAnimation->addFrame(spriteFrame);
			}
			
			// create an animation/action and add it to action container
			CCAnimate* girlAction = CCAnimate::actionWithAnimation(girlAnimation);
			CCRepeatForever* repeatForever = CCRepeatForever::actionWithAction(girlAction);
			m_differentGirlsActions->addObject(repeatForever);
		}

	
		// girl sprite		
		CCSpriteFrame* spriteFrame = spriteFrameCache->spriteFrameByName("girl_01_0001.png");
		m_girlSprite = CCSprite::spriteWithSpriteFrame(spriteFrame); // retain];
		m_girlSprite->retain();
		this->addChild(m_girlSprite);

        bRet = true;
    } while (0);

    return bRet;
}

/*!
 Activate next girl modifiying m_currentGirlNumber. 0...NUMBER_OF_GIRLS-1,0,1,2...
 */
void BackgroundGirls::incrementGirl(void)
{	
	unsigned int newGirlNumber=(m_currentGirlNumber+1) % NUMBER_OF_GIRLS;
	this->setGirlNumber(newGirlNumber);
}

void BackgroundGirls::setGirlNumber( unsigned int girlNumber)
{
	// NSAssert(girlNumber<NUMBER_OF_GIRLS, @"girlNumber too high.");
	m_currentGirlNumber = girlNumber;
	m_girlSprite->stopAllActions();
	m_girlSprite->runAction(m_differentGirlsActions->getObjectAtIndex(m_currentGirlNumber));
	CCLog("BackgroundGirls setting girlNumber to: %d", m_currentGirlNumber);
}

void BackgroundGirls::onEnter (void)
{
	CCLog("BackgroundGirls onEnter");
	m_girlSprite->stopAllActions();
	m_girlSprite->runAction(m_differentGirlsActions->getObjectAtIndex(m_currentGirlNumber));
	CCNode::onEnter();
}

void BackgroundGirls::onExit(void)
{
	CCLog("BackgroundGirls onExit");
	m_girlSprite->stopAllActions();
	CCNode::onExit();
}

BackgroundGirls::~BackgroundGirls(void)
{
	CCLog("BackgroundGirls deconstructor");
	CC_SAFE_RELEASE(m_spriteSheetTextures);
	CC_SAFE_RELEASE(m_differentGirlsActions);
	CC_SAFE_RELEASE(m_girlSprite);

}