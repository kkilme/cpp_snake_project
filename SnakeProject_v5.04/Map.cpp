#include "Map.h"
#include "curses.h"

// ���� ȭ�鿡 ���ο� window�� ������
void Map::getMap(WINDOW* window, int stage)
{
    //map�� ���پ� load 
    mvwprintw(window, 0, 0, "stage");
    for (int i = 0; i < 30; i++) {
        mvwprintw(window, i + 5, 5, mapList[stage][i]); //mapList[stage] ��° �� ���
    }
}

// �� Ư����ġ ����
// k�� ������ ������ ��Ÿ��. t : snake tail, h : snake head, n : null(�����)
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
