#include "Screen.h"
void Screen::loadHome() {
    //�⺻ â ���� ��, ������ ����.
    initscr();
    resize_term(50, 100);

    noecho(); //�Է��� ȭ�鿡 ǥ�� �ȵǰ��ϴ� �Լ�

    //�⺻ â color����
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
    menu = newwin(8 + menuLength, 30, 16, 35); //Ȩȭ�� �޴�â
    // stage ������ ����
    wbkgd(menu, COLOR_PAIR(1));
    for (int i = 0; i < menuLength; i++) {
        mvwprintw(menu, 2*(i+1), 1, menuList[i]);
    }
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');   
    attroff(COLOR_PAIR(1));     //colo_pair �������.
    wrefresh(menu);
}

void Screen::resetScreen() { // â ������ ��ũ�� ����
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(2));
    refresh();
}