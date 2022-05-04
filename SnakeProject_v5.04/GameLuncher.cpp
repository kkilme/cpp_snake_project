#include "GameLuncher.h"
#include "curses.h"
#include "Map.h"
void GameLuncher::lunchGame(char selectedNum)
{
    //�÷� ����
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    
    //���ο� â �����
    WINDOW* win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    attroff(COLOR_PAIR(1)); //colo_pair �������.
    
    // â�� �� �ҷ����� 
    Map map;
    map.getMap(win1,selectedNum);

    //ȭ�鰻��
    wrefresh(win1);
}