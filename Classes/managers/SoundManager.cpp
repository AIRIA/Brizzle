﻿#include "SoundManager.h"

SoundManager *SoundManager::_instance = NULL;

SoundManager * SoundManager::shareSoundManager()
{
    if(!_instance)
    {
        _instance = new SoundManager();
    }
    return _instance;
}

void SoundManager::playBackground( const char *sound,bool repeat )
{
    bool soundEnable = CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_SOUND_ENABLE);
    if(soundEnable)
    {
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic((sound+suffix).c_str(),repeat);
    }
}

void SoundManager::playEffect( const char *sound )
{
	bool soundEnable = CCUserDefault::sharedUserDefault()->getBoolForKey(KEY_SOUND_ENABLE);
	if(soundEnable)
	{
		SimpleAudioEngine::sharedEngine()->playEffect((sound+suffix).c_str());
	}
}
