#include "DarkGDK.h"
#include "basic3d/Basic3DCommands.h"

void dbMakeObjectCube(int objectId, float size) {
    litegdk::makeObjectCube(objectId, size);
}

void dbPositionObject(int objectId, float x, float y, float z) {
    litegdk::positionObject(objectId, x, y, z);
}

void dbRotateObject(int objectId, float x, float y, float z) {
    litegdk::rotateObject(objectId, x, y, z);
}

void dbPositionCamera(float x, float y, float z) {
    litegdk::positionCamera(x, y, z);
}

void dbPointCamera(float x, float y, float z) {
    litegdk::pointCamera(x, y, z);
}
