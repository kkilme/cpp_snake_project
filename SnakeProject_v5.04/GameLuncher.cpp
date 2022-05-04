#include "GameLuncher.h"
#include "curses.h"
#include "Map.h"
void GameLuncher::lunchGame(char selectedNum)
{
    //컬러 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    
    //새로운 창 만들기
    WINDOW* win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    attroff(COLOR_PAIR(1)); //colo_pair 사용종료.
    
    // 창에 맵 불러오기 
    Map map;
    map.getMap(win1,selectedNum);

    //화면갱신
    wrefresh(win1);
}