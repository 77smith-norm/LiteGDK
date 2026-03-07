#include "DarkGDK.h"

int main() {
    BYTE channel = 0;
    WORD width = 800;
    WORD height = 600;
    DWORD syncRate = 60;
    BOOL syncEnabled = TRUE;

    dbSetDisplayMode(width, height, 32);

    if (syncEnabled == TRUE && channel == 0) {
        dbSyncOn();
        dbSyncRate(static_cast<int>(syncRate));
        dbCLS();
    }

    return FALSE;
}
