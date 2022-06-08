#include "Screen.h"
void Screen::loadHome() {
    //기본 창 생성 및, 사이즈 조절.
    initscr();
    resize_term(50, 100);

    noecho(); //입력을 화면에 표시 안되게하는 함수

    //기본 창 color설정
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(2));

    border('|', '|', '-', '-', '+', '+', '+', '+');
    
    refresh();
    Screen::loadMenu();
}

void Screen::loadMenu() {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    menu = newwin(8 + menuLength, 30, 16, 35); //홈화면 메뉴창
    // stage 선택지 띄우기
    wbkgd(menu, COLOR_PAIR(1));
    for (int i = 0; i < menuLength; i++) {
        mvwprintw(menu, 2*(i+1), 1, menuList[i]);
    }
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');   
    attroff(COLOR_PAIR(1));     //colo_pair 사용종료.
    wrefresh(menu);
}

void Screen::resetScreen() { // 창 삭제후 스크린 리셋
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(2));
    refresh();
}