#include "AppDelegate.h"

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
using namespace CocosDenshion;


//#include "HelloWorldScene.h"
#include "CompanyScene.h"
#include "Constants.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
    
}

AppDelegate::~AppDelegate()
{
    SimpleAudioEngine::end();
}

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCEGLView * pMainWnd = new CCEGLView();
        CC_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(TEXT("identifygame"), 320, 480));
#endif  // CC_PLATFORM_WIN32

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

        // OpenGLView initialized in testsAppDelegate.mm on ios platform, nothing need to do here.

#endif  // CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

        // Android doesn't need to do anything.

#endif  // CC_PLATFORM_ANDROID

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)
        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        // Use GetScreenWidth() and GetScreenHeight() get screen width and height.
        CCEGLView * pMainWnd = new CCEGLView(this);
        CC_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(320, 480));

#if !defined(_TRANZDA_VM_)
        // set the resource zip file
        // on wophone emulator, we copy resources files to Work7/TG3/APP/ folder instead of zip file
        CCFileUtils::setResource("identifygame.zip");
#endif

#endif
	
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
//		CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationPortrait);
//#else
//		CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
//#endif

        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
    // sets landscape mode (MUST SET TO kCCDeviceOrientationPortrait for device on Marmalade)
    pDirector->setDeviceOrientation(kCCDeviceOrientationPortrait);
#else
		CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
#endif

#ifdef _DEBUG
    // turn on display FPS
    pDirector->setDisplayFPS(true);
#endif

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    //CCScene *pScene = HelloWorld::scene();

	// company scene
	//CompanyScene* companyScene=[CompanyScene node];
	//[[CCDirector sharedDirector] runWithScene:[CCTransitionFade transitionWithDuration:TRANSITION_DURATION scene:companyScene]];	
	CCScene* companyScene = CompanyScene::scene();
    // run Scene - cannot do transition unless there is another scene?
	pDirector->runWithScene(companyScene);
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();

    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
