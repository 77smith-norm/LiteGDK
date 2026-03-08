#pragma once

void dbLoadSound(const char* filename, int soundId);
void dbDeleteSound(int soundId);
void dbPlaySound(int soundId);
void dbStopSound(int soundId);
void dbSetSoundVolume(int soundId, int volume);

void dbLoadMusic(const char* filename, int musicId);
void dbDeleteMusic(int musicId);
void dbPlayMusic(int musicId);
void dbStopMusic(int musicId);
void dbPauseMusic(int musicId);
void dbResumeMusic(int musicId);
void dbSetMusicVolume(int musicId, int volume);
