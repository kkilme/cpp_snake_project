
#include "Map.h"
#include "curses.h"




// ���� ȭ�鿡 ���ο� window�� ������
void Map::getMap(WINDOW* window, char stage)
{
    //map�� ���پ� load 
    mvwprintw(window, 0, 0, "stage");
    for (int i = 0; i < 30; i++) {
        mvwprintw(window, i + 5, 5, mapList[stage - 49][i]); //mapList[stage-49] ��° �� ���,'1'�� �޾ƿ��� ������ int 1�� �ٲ���.
    }
}