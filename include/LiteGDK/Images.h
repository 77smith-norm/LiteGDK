#pragma once

void dbLoadImage(const char* filename, int imageId);
int dbImageExist(int imageId);
int dbGetImageWidth(int imageId);
int dbGetImageHeight(int imageId);
