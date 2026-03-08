#include "DarkGDK.h"
#include "sprites/SpriteCommands.h"

void dbSprite(int spriteId, int x, int y, int imageId) {
    litegdk::createSprite(spriteId, x, y, imageId);
}

void dbDeleteSprite(int spriteId) {
    litegdk::deleteSprite(spriteId);
}

void dbHideSprite(int spriteId) {
    litegdk::hideSprite(spriteId);
}

void dbShowSprite(int spriteId) {
    litegdk::showSprite(spriteId);
}

void dbXSprite(int spriteId, int x) {
    litegdk::setSpriteX(spriteId, x);
}

void dbYSprite(int spriteId, int y) {
    litegdk::setSpriteY(spriteId, y);
}

int dbSpriteExist(int spriteId) {
    return litegdk::spriteExists(spriteId) ? TRUE : FALSE;
}
