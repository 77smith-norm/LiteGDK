#pragma once

namespace litegdk {
void createSprite(int spriteId, int x, int y, int imageId);
void deleteSprite(int spriteId);
void hideSprite(int spriteId);
void showSprite(int spriteId);
void setSpriteX(int spriteId, int x);
void setSpriteY(int spriteId, int y);
bool spriteExists(int spriteId);
}  // namespace litegdk
