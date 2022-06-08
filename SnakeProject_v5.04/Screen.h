#include "curses.h"

class Screen {
public:
    WINDOW* menu;
    void loadHome();
    void loadMenu();
    void resetScreen();

private:
    char menuList[4][30] = { "\t     MENU","NUM_PAD '1': START GAME","NUM_PAD '2': RECORDS","NUM_PAD '3': EXIT" };    // ���߿� record �߰��Ǹ� ����Ʈ, ����Ʈ���� ����
    int menuLength = 4;
};
