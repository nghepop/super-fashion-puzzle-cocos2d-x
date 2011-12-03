#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "SoundManager.h"
using namespace cocos2d;


// singleton stuff
static SoundManager* m_sharedSoundManager = NULL;

SoundManager *SoundManager::sharedSoundManager(void)
{
	if (m_sharedSoundManager == NULL)
	{
		m_sharedSoundManager = new SoundManager;
		if (m_sharedSoundManager)
		{
			m_sharedSoundManager->init();
			return m_sharedSoundManager;
		}
	}
	else
		return m_sharedSoundManager;

	//CC_SAFE_DELETE(m_sharedSoundManager);
	// return NULL;
}

void SoundManager::showVersion(void)
{
	CCLog("SoundManager. Calling this method to force effects preloading.");
}

bool SoundManager::init(void)
{
			// sound loading
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_chip_was_unselected.wav");
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_regeneration.wav");
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_selected_chip.wav");
#if (CC_TARGET_PLATFORM != CC_PLATFORM_AIRPLAY)
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_tap.wav");
#else
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_tap.raw");
#endif
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_ready.raw");
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_new_girl.mp3");
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_incorrect_matching.mp3");
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_game_over.mp3");
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_correct_matching_with_wildcard.mp3");
		//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect("sound/sound_fx_correct_matching.mp3");
		
		// music
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/sound_music_game.mp3");
		CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadBackgroundMusic("sound/sound_music_menu.mp3");

		return true;
}
void SoundManager::playSoundFxGameOver(void)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/sound_fx_game_over.mp3");
}

void SoundManager::playSoundFxTap(void)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("sound/sound_fx_tap.raw");
}

void SoundManager::playSoundMusicGame(void)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/sound_music_game.mp3");
}

void SoundManager::playSoundMusicMenu(void)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("sound/sound_music_menu.mp3");
}

void SoundManager::stopBackgroundMusic(void)
{
	CocosDenshion::SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
}
