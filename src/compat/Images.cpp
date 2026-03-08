#include "DarkGDK.h"
#include "images/ImageCommands.h"

void dbLoadImage(const char* filename, int imageId) {
    litegdk::loadImage(filename == nullptr ? "" : filename, imageId);
}

int dbImageExist(int imageId) {
    return litegdk::imageExists(imageId) ? TRUE : FALSE;
}

int dbGetImageWidth(int imageId) {
    return litegdk::imageWidth(imageId);
}

int dbGetImageHeight(int imageId) {
    return litegdk::imageHeight(imageId);
}
