#include "Map.h"
#include "curses.h"

// 맵을 화면에 새로운 window로 보여줌
void Map::getMap(WINDOW* window, int stage)
{
    //map을 한줄씩 load 
    mvwprintw(window, 0, 0, "stage");
    for (int i = 0; i < 30; i++) {
        mvwprintw(window, i + 5, 5, mapList[stage][i]); //mapList[stage] 번째 맵 출력
    }
}

// 맵 특정위치 변경
// k는 변경할 종류를 나타냄. t : snake tail, h : snake head, n : null(빈공간)
void Map::setMap(int stage, int x, int y, char k) {
    if (k == 'n') {
        mapList[stage][y][x] = 32;
    }
    else if (k == 'h') {
        mapList[stage][y][x] = '3';
    }
    else if (k == 't') {
        mapList[stage][y][x] = '4';
    }
}
