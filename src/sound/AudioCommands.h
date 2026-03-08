#pragma once

#include <string_view>

namespace litegdk {
bool audioInitializationAllowed();

void loadSound(std::string_view filename, int soundId);
void deleteSound(int soundId);
void playSound(int soundId);
void stopSound(int soundId);
void setSoundVolume(int soundId, int volume);

void loadMusic(std::string_view filename, int musicId);
void deleteMusic(int musicId);
void playMusic(int musicId);
void stopMusic(int musicId);
void pauseMusic(int musicId);
void resumeMusic(int musicId);
void setMusicVolume(int musicId, int volume);
}  // namespace litegdk
