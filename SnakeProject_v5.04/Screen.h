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
    char menuList[4][30] = { "\t     MENU","NUM_PAD '1': START GAME","NUM_PAD '2': RECORDS","NUM_PAD '3': EXIT" };    // ���߿� record �߰��Ǹ� ����Ʈ, ����Ʈ���� ����
    int menuLength = 4;
};
