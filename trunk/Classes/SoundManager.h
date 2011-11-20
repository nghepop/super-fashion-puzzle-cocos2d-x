#ifndef CCRadioMenu_h__
#define SoundManager_h__

class SoundManager :
	public cocos2d::CCObject
{
public:
	SoundManager(void){};
	~SoundManager(void){};

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init(void);  
	void showVersion(void);

	// effects
//void playSoundFxCorrectMatching;
//void playSoundFxCorrectMatchingWithWildcard;
//void playSoundFxChipWasUnselected;
void playSoundFxGameOver(void);
//void playSoundFxIncorrectMatching;
///void playSoundFxNewGirl;
//void playSoundFxRegeneration;
//void playSoundFxSelectedChip;
void playSoundFxTap(void);
// void playSoundFxReady;

// music
void playSoundMusicGame(void);
void playSoundMusicMenu(void);
void stopBackgroundMusic(void);

static SoundManager* sharedSoundManager(void);

};
#endif