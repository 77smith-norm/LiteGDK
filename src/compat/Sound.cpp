#include "DarkGDK.h"
#include "sound/AudioCommands.h"

void dbLoadSound(const char* filename, int soundId) {
    litegdk::loadSound(filename == nullptr ? "" : filename, soundId);
}

void dbDeleteSound(int soundId) {
    litegdk::deleteSound(soundId);
}

void dbPlaySound(int soundId) {
    litegdk::playSound(soundId);
}

void dbStopSound(int soundId) {
    litegdk::stopSound(soundId);
}

void dbSetSoundVolume(int soundId, int volume) {
    litegdk::setSoundVolume(soundId, volume);
}

void dbLoadMusic(const char* filename, int musicId) {
    litegdk::loadMusic(filename == nullptr ? "" : filename, musicId);
}

void dbDeleteMusic(int musicId) {
    litegdk::deleteMusic(musicId);
}

void dbPlayMusic(int musicId) {
    litegdk::playMusic(musicId);
}

void dbStopMusic(int musicId) {
    litegdk::stopMusic(musicId);
}

void dbPauseMusic(int musicId) {
    litegdk::pauseMusic(musicId);
}

void dbResumeMusic(int musicId) {
    litegdk::resumeMusic(musicId);
}

void dbSetMusicVolume(int musicId, int volume) {
    litegdk::setMusicVolume(musicId, volume);
}
