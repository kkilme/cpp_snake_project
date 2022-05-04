
#include "Map.h"
#include "curses.h"




// 맵을 화면에 새로운 window로 보여줌
void Map::getMap(WINDOW* window, char stage)
{
    //map을 한줄씩 load 
    mvwprintw(window, 0, 0, "stage");
    for (int i = 0; i < 30; i++) {
        mvwprintw(window, i + 5, 5, mapList[stage - 49][i]); //mapList[stage-49] 번째 맵 출력,'1'로 받아오기 때문에 int 1로 바꿔줌.
    }
}