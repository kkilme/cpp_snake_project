#pragma once
#include "curses.h"
#include <time.h>
#include <vector>
#include <string>
using namespace std;
class Screen {
public:
    WINDOW* menu;
    WINDOW* record;
    void loadHome();
    void loadMenu();
    void loadRecord(bool isgamecleared, time_t cleartime = 0);
    void resetScreen();

private:
    char menuList[4][30] = { "\t     MENU","NUM_PAD '1': START GAME","NUM_PAD '2': RECORDS","NUM_PAD '3': EXIT" };    // 나중에 record 추가되면 리스트, 리스트길이 변경
    int menuLength = 4;
};
