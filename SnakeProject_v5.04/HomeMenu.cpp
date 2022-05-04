#include "HomeMenu.h"
#include "curses.h"

void HomeMenu::loadHome() {

    //기본 창 생성 및, 사이즈 조절.
    initscr();
    resize_term(50, 100);

    noecho(); //입력을 화면에 표시 안되게하는 함수

    //기본 창 color설정
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(2));

    border('|', '|', '-', '-', '+', '+', '+', '+');
    
    // stage 선택지 띄우기
    for (int i = 0; i < menuLength; i++) {
        mvprintw(i+1, 70, menuList[i]);
    }
    
    refresh();
}