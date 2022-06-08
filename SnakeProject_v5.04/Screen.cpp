#include "HomeMenu.h"
#include "curses.h"

void HomeMenu::loadHome() {

    //�⺻ â ���� ��, ������ ����.
    initscr();
    resize_term(50, 100);

    noecho(); //�Է��� ȭ�鿡 ǥ�� �ȵǰ��ϴ� �Լ�

    //�⺻ â color����
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(2));

    border('|', '|', '-', '-', '+', '+', '+', '+');
    
    // stage ������ ����
    for (int i = 0; i < menuLength; i++) {
        mvprintw(i+1, 70, menuList[i]);
    }
    
    refresh();
}