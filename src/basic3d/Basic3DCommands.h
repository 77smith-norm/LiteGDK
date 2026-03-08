#pragma once

namespace litegdk {
void makeObjectCube(int objectId, float size);
void positionObject(int objectId, float x, float y, float z);
void rotateObject(int objectId, float x, float y, float z);
void positionCamera(float x, float y, float z);
void pointCamera(float x, float y, float z);
}  // namespace litegdk
