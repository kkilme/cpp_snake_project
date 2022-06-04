#include "Map.h"
#include "curses.h"
#include <stdlib.h>  
#include <time.h>
#include "gate.h"
#include "snake.h"


#define NUM_1_OF_STAGE0 112
#define NUM_1_OF_STAGE1 176
#define NUM_1_OF_STAGE2 140

#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

#define UP_LEFT 4
#define UP_RIGHT 5
#define DOWN_RIGHT 6
#define DOWN_LEFT 7

extern vector<SnakePart> snake;
Gate Gate1;
Gate Gate2;

void Map::mapColorStart()
{
    init_pair(11, COLOR_WHITE, COLOR_WHITE); //벽
    init_pair(33, COLOR_BLUE, COLOR_BLUE); //머리
    init_pair(44, COLOR_CYAN, COLOR_CYAN); //꼬리
    init_pair(55, COLOR_GREEN, COLOR_GREEN);  //increase item
    init_pair(66, COLOR_RED, COLOR_RED);  //increase item
    init_pair(77, COLOR_YELLOW, COLOR_YELLOW);  //increase item
    

}

// 맵을 화면에 새로운 window로 보여줌
void Map::getMap(WINDOW* window, const int stage)
{
    
    //map을 한줄씩 load 
    mvwprintw(window, 0, 0, "stage %d",stage + 1);
    
    
    for (int i = 0; i < 30; i++) {
        for (int j = 0; j < 30; j++) {
            if (mapList[stage][i][j] == '1' or mapList[stage][i][j] == '2') {
                wattron(window, COLOR_PAIR(11));
                mvwprintw(window, i + 5, j + 5, "%c", mapList[stage][i][j]);
                wattroff(window, COLOR_PAIR(11));
            }
            else if (mapList[stage][i][j] == '3') {
                wattron(window, COLOR_PAIR(33));
                mvwprintw(window, i + 5, j + 5, "%c", mapList[stage][i][j]);
                wattroff(window, COLOR_PAIR(33));
            }
            else if (mapList[stage][i][j] == '4') {
                wattron(window, COLOR_PAIR(44));
                mvwprintw(window, i + 5, j + 5, "%c", mapList[stage][i][j]);
                wattroff(window, COLOR_PAIR(44));
            }
            else if (mapList[stage][i][j] == '5') {
                wattron(window, COLOR_PAIR(55));
                mvwprintw(window, i + 5, j + 5, "%c", mapList[stage][i][j]);
                wattroff(window, COLOR_PAIR(55));
            }
            else if (mapList[stage][i][j] == '6') {
                wattron(window, COLOR_PAIR(66));
                mvwprintw(window, i + 5, j + 5, "%c", mapList[stage][i][j]);
                wattroff(window, COLOR_PAIR(66));
            }
            else if (mapList[stage][i][j] == '7') {
                wattron(window, COLOR_PAIR(77));
                mvwprintw(window, i + 5, j + 5, "%c", mapList[stage][i][j]);
                wattroff(window, COLOR_PAIR(77));
            }
            else {
                mvwprintw(window, i + 5, j + 5, "%c", mapList[stage][i][j]);
            }
             
        }
        //mvwprintw(window, i + 5, 5, mapList[stage][i]); //mapList[stage] 번째 맵 출력
    }
}

// 맵 특정위치 변경
// k는 변경할 종류를 나타냄. t : snake tail, h : snake head, n : null(빈공간)
void Map::setMap(const int stage,const  int x, const int y,const char k) {
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

void Map::setGate(const int stage) {      // stage 마다 wall의 위치가 달라 stage별로 함수 
    if (snake.size() > 5 || snake.size() == 5)
    {
        switch (stage)
        {
        case 0:
            gateInStage0(stage);
            break;
        case 1:
            gateInStage1(stage);
            break;
        case 2:
            gateInStage2(stage);
            break;
        }
    }
}

void Map::gateInStage0(const int stage)
{

    int firstNum, secondNum;
    do
    {
        srand(time(NULL));
        firstNum = rand() * 123 % NUM_1_OF_STAGE0;      // 첫번재 게이트 지점
        secondNum = rand() * 456 % NUM_1_OF_STAGE0;     // 두번째 게이트 지점
    } while (abs(firstNum - secondNum) < 2);
    
    // 첫번째 게이트 설정
    if (firstNum < 28)
    {
        mapList[stage][0][1 + firstNum] = '7';
        Gate1.setPos(0,1 + firstNum);                    // Gate class 의 객체 Gate1 생성
        Gate1.setExitDirect(DOWN);
    }
    else if (firstNum < 56)
    {
        mapList[stage][1 + firstNum - 28][29] = '7';
        Gate1.setPos(1 + firstNum - 28, 29);
        Gate1.setExitDirect(LEFT);
    }
    else if (firstNum < 84)
    {
        mapList[stage][29][28 - (firstNum - 56)] = '7';
        Gate1.setPos(29, 28 - (firstNum - 56));
        Gate1.setExitDirect(UP);
    }
    else
    {
        mapList[stage][28 - (firstNum - 84)][0] = '7';
        Gate1.setPos(28 - (firstNum - 84), 0);
        Gate1.setExitDirect(RIGHT);
    }

    // 두번째 게이트 설정 
    if (secondNum < 28)
    {
        mapList[stage][0][1 + secondNum] = '7';
        Gate2.setPos(0, 1 + secondNum);                    // Gate class 의 객체 Gate2 생성
        Gate2.setExitDirect(DOWN);
    }
    else if (secondNum < 56)
    {
        mapList[stage][1 + secondNum - 28][29] = '7';
        Gate2.setPos(1 + secondNum - 28, 29);
        Gate2.setExitDirect(LEFT);
    }
    else if (secondNum < 84)
    {
        mapList[stage][29][28 - (secondNum - 56)] = '7';
        Gate2.setPos(29, 28 - (secondNum - 56));
        Gate2.setExitDirect(UP);
    }
    else
    {
        mapList[stage][28 - (secondNum - 84)][0] = '7';
        Gate2.setPos(28 - (secondNum - 84), 0);
        Gate2.setExitDirect(RIGHT);
    }
    Gate1.setPairPtr(&Gate2);
}

void Map::gateInStage1(const int stage)
{
    int firstNum, secondNum;
    do
    {
        unsigned srand(time(NULL));
        firstNum = rand() * 123 % NUM_1_OF_STAGE1;      // 첫번재 게이트 지점
        secondNum = rand() * 456 % NUM_1_OF_STAGE1;     // 두번째 게이트 지점
    } while (abs(firstNum - secondNum) < 2);

    // 첫번째 게이트 설정
    if (firstNum < 6)
    {
        mapList[stage][0][1 + firstNum] = '7';
        Gate1.setPos(0,1 + firstNum);                    // Gate class 의 객체 Gate1 생성
        Gate1.setExitDirect(DOWN);
    }
    else if (firstNum < 26)
    {
        mapList[stage][0][9 + firstNum - 6] = '7';
        Gate1.setPos(0, 9 + firstNum - 6);
        Gate1.setExitDirect(DOWN);
    }
    else if (firstNum < 54)
    {
        mapList[stage][1 + firstNum - 26][29] = '7';
        Gate1.setPos(1 + firstNum - 26, 29);
        Gate1.setExitDirect(LEFT);
    }
    else if (firstNum < 60)
    {
        mapList[stage][29][28 - (firstNum - 54)] = '7';
        Gate1.setPos(29, 28 - (firstNum - 54));
        Gate1.setExitDirect(UP);
    }
    else if (firstNum < 80)
    {
        mapList[stage][29][20 -(firstNum - 60)] = '7';
        Gate1.setPos(29, 20 - (firstNum - 60));
        Gate1.setExitDirect(UP);
    }
    else if (firstNum < 108)
    {
        mapList[stage][28 - (firstNum - 80)][0] = '7';
        Gate1.setPos(28 -(firstNum - 80), 0);
        Gate1.setExitDirect(RIGHT);
    }
    else if (firstNum < 125)
    {
        mapList[stage][1 + firstNum - 108][7] = '7';
        Gate1.setPos(1 + firstNum - 108, 7);
        if (firstNum == 124)
        {
            Gate1.setExitDirect(DOWN_LEFT);
        }
        else
        {
            Gate1.setExitDirect(LEFT);
        }
    }
    else if (firstNum < 142)
    {
        mapList[stage][17 - (firstNum - 125)][8] = '7';
        Gate1.setPos(17 - (firstNum - 125), 8);
        if (firstNum == 125)
        {
            Gate1.setExitDirect(DOWN_RIGHT);
        }
        else
        {
            Gate1.setExitDirect(RIGHT);
        }
    }
    else if (firstNum < 159)
    {
        mapList[stage][28 - (firstNum - 142)][22] = '7';
        Gate1.setPos(28 - (firstNum - 142), 22);
        if (firstNum == 158)
        {
            Gate1.setExitDirect(UP_RIGHT);
        }
        else
        {
            Gate1.setExitDirect(RIGHT);
        }
    }
    else
    {
        mapList[stage][12 + (firstNum - 159)][21] = '7';
        Gate1.setPos(12 + (firstNum - 159), 21);
        if (firstNum == 159)
        {
            Gate1.setExitDirect(UP_LEFT);
        }
        else
        {
            Gate1.setExitDirect(LEFT);
        }
    }

    // 두번째 게이트 설정 
    if (secondNum < 6)
    {
        mapList[stage][0][1 + secondNum] = '7';
        Gate2.setPos(0, 1 + secondNum);                    // Gate class 의 객체 Gate2 생성
        Gate2.setExitDirect(DOWN);
    }
    else if (secondNum < 26)
    {
        mapList[stage][0][9 + secondNum - 6] = '7';
        Gate2.setPos(0, 9 + secondNum - 6);
        Gate2.setExitDirect(DOWN);
    }
    else if (secondNum < 54)
    {
        mapList[stage][1 + secondNum - 26][29] = '7';
        Gate2.setPos(1 + secondNum - 26, 29);
        Gate2.setExitDirect(LEFT);
    }
    else if (secondNum < 60)
    {
        mapList[stage][29][28 - (secondNum - 54)] = '7';
        Gate2.setPos(29, 28 - (secondNum - 54));
        Gate2.setExitDirect(UP);
    }
    else if (secondNum < 80)
    {
        mapList[stage][29][20 - (secondNum - 60)] = '7';
        Gate2.setPos(29, 20 - (secondNum - 60));
        Gate2.setExitDirect(UP);
    }
    else if (secondNum < 108)
    {
        mapList[stage][28 - (secondNum - 80)][0] = '7';
        Gate2.setPos(28 - (secondNum - 80), 0);
        Gate2.setExitDirect(RIGHT);
    }
    else if (secondNum < 125)
    {
        mapList[stage][1 + secondNum - 108][7] = '7';
        Gate2.setPos(1 + secondNum - 108, 7);
        if (secondNum == 124)
        {
            Gate2.setExitDirect(DOWN_LEFT);
        }
        else
        {
            Gate2.setExitDirect(LEFT);
        }
    }
    else if (secondNum < 142)
    {
        mapList[stage][17 - (secondNum - 125)][8] = '7';
        Gate2.setPos(17 - (secondNum - 125), 8);
        if (secondNum == 125)
        {
            Gate2.setExitDirect(DOWN_RIGHT);
        }
        else
        {
            Gate2.setExitDirect(RIGHT);
        }
    }
    else if (secondNum < 159)
    {
        mapList[stage][29 - (secondNum - 142)][22] = '7';
        Gate2.setPos(29 - (secondNum - 142), 22);
        if (secondNum == 158)
        {
            Gate2.setExitDirect(UP_RIGHT);
        }
        else
        {
            Gate2.setExitDirect(RIGHT);
        }
    }
    else
    {
        mapList[stage][12 + (secondNum - 159)][21] = '7';
        Gate2.setPos(12 + (secondNum - 159), 21);
        if (secondNum == 159)
        {
            Gate2.setExitDirect(UP_LEFT);
        }
        else
        {
            Gate2.setExitDirect(LEFT);
        }
    }
    Gate1.setPairPtr(&Gate2);
}

void Map::gateInStage2(const int stage)
{
    int firstNum, secondNum;
    do
    {
        srand(time(NULL));
        firstNum = rand() * 123 % NUM_1_OF_STAGE2;      // 첫번재 게이트 지점
        secondNum = rand() * 456 % NUM_1_OF_STAGE2;     // 두번째 게이트 지점
    } while (abs(firstNum - secondNum) < 2);

    // 첫번째 게이트 설정
    if (firstNum < 28)
    {
        mapList[stage][0][1 + firstNum] = '7';
        Gate1.setPos(0, 1 + firstNum);                    // Gate class 의 객체 Gate1 생성
        Gate1.setExitDirect(DOWN);
    }
    else if (firstNum < 56)
    {
        mapList[stage][1 + firstNum - 28][29] = '7';
        Gate1.setPos(1 + firstNum - 28, 29);
        Gate1.setExitDirect(LEFT);
    }
    else if (firstNum < 84)
    {
        mapList[stage][29][28 - (firstNum - 56)] = '7';
        Gate1.setPos(29, 28 - (firstNum - 56));
        Gate1.setExitDirect(UP);
    }
    else if (firstNum < 112)
    {
        mapList[stage][28 -(firstNum - 84)][0] = '7';
        Gate1.setPos(28 - (firstNum - 84), 0);
        Gate1.setExitDirect(RIGHT);
    }
    else if (firstNum < 116)
    {
        mapList[stage][6 + firstNum - 112][13] = '7';
        Gate1.setPos(6 + firstNum - 112, 13);
        if (firstNum == 112)
        {
            Gate1.setExitDirect(UP_LEFT);
        }
        else
        {
            Gate1.setExitDirect(LEFT);
        }
    }
    else if (firstNum < 119)
    {
        mapList[stage][10][13 + (firstNum - 116)] = '7';
        Gate1.setPos(10, 13 + (firstNum - 116));
        if (firstNum == 116)
        {
            Gate1.setExitDirect(DOWN_LEFT);
        }
        else
        {
            Gate1.setExitDirect(DOWN);
        }
    }
    else if (firstNum < 123)
    {
        mapList[stage][10 - (firstNum - 119)][16] = '7';
        Gate1.setPos(10 - (firstNum - 119), 16);
        if (firstNum == 119)
        {
            Gate1.setExitDirect(DOWN_RIGHT);
        }
        else
        {
            Gate1.setExitDirect(RIGHT);
        }
    }
    else if (firstNum < 126)
    {
        mapList[stage][6][16 - (firstNum - 123)] = '7';
        Gate1.setPos(6, 16 - (firstNum - 123));
        if (firstNum == 123)
        {
            Gate1.setExitDirect(UP_RIGHT);
        }
        else
        {
            Gate1.setExitDirect(UP);
        }
    }
    else if (firstNum < 130)
    {
        mapList[stage][20 + (firstNum - 126)][13] = '7';
        Gate1.setPos(20 + (firstNum - 126), 13);
        if (firstNum == 126)
        {
            Gate1.setExitDirect(UP_LEFT);
        }
        else
        {
            Gate1.setExitDirect(LEFT);
        }
    }
    else if (firstNum < 133)
    {
        mapList[stage][24][13 + (firstNum - 130)] = '7';
        Gate1.setPos(24, 13 + (firstNum - 130));
        if (firstNum == 130)
        {
            Gate1.setExitDirect(DOWN_LEFT);
        }
        else
        {
            Gate1.setExitDirect(DOWN);
        }
    }
    else if (firstNum < 137)
    {
        mapList[stage][24 - (firstNum - 133)][16] = '7';
        Gate1.setPos(24 - (firstNum - 133), 16);
        if (firstNum == 133)
        {
            Gate1.setExitDirect(DOWN_RIGHT);
        }
        else
        {
            Gate1.setExitDirect(RIGHT);
        }
    }
    else
    {
        mapList[stage][20][16 - (firstNum - 137)] = '7';
        Gate1.setPos(20, 16 - (firstNum - 137));
        if (firstNum == 137)
        {
            Gate1.setExitDirect(UP_RIGHT);
        }
        else
        {
            Gate1.setExitDirect(UP);
        }
    }

    // 두번째 게이트 설정 
    if (secondNum < 28)
    {
        mapList[stage][0][1 + secondNum] = '7';
        Gate2.setPos(0, 1 + secondNum);                    // Gate class 의 객체 Gate2 생성
        Gate2.setExitDirect(DOWN);
    }
    else if (secondNum < 56)
    {
        mapList[stage][1 + secondNum - 28][29] = '7';
        Gate2.setPos(1 + secondNum - 28, 29);
        Gate2.setExitDirect(LEFT);
    }
    else if (secondNum < 84)
    {
        mapList[stage][29][28 - (secondNum - 56)] = '7';
        Gate2.setPos(29, 28 - (secondNum - 56));
        Gate2.setExitDirect(UP);
    }
    else if (secondNum < 112)
    {
        mapList[stage][28 - (secondNum - 84)][0] = '7';
        Gate2.setPos(28 - (secondNum - 84), 0);
        Gate2.setExitDirect(RIGHT);
    }
    else if (secondNum < 116)
    {
        mapList[stage][6 + secondNum - 112][13] = '7';
        Gate2.setPos(6 + secondNum - 112, 13);
        if (secondNum == 112)
        {
            Gate2.setExitDirect(UP_LEFT);
        }
        else
        {
            Gate2.setExitDirect(LEFT);
        }
    }
    else if (secondNum < 119)
    {
        mapList[stage][10][13 + (secondNum - 116)] = '7';
        Gate2.setPos(10, 13 + (secondNum - 116));
        if (secondNum == 116)
        {
            Gate2.setExitDirect(DOWN_LEFT);
        }
        else
        {
            Gate2.setExitDirect(DOWN);
        }
    }
    else if (secondNum < 123)
    {
        mapList[stage][10 - (secondNum - 119)][16] = '7';
        Gate2.setPos(10 - (secondNum - 119), 16);
        if (secondNum == 119)
        {
            Gate2.setExitDirect(DOWN_RIGHT);
        }
        else
        {
            Gate2.setExitDirect(RIGHT);
        }
    }
    else if (secondNum < 126)
    {
        mapList[stage][6][16 - (secondNum - 123)] = '7';
        Gate2.setPos(6, 16 - (secondNum - 123));
        if (secondNum == 123)
        {
            Gate2.setExitDirect(UP_RIGHT);
        }
        else
        {
            Gate2.setExitDirect(UP);
        }
    }
    else if (secondNum < 130)
    {
        mapList[stage][20 + (secondNum - 126)][13] = '7';
        Gate2.setPos(20 + (secondNum - 126), 13);
        if (secondNum == 126)
        {
            Gate2.setExitDirect(UP_LEFT);
        }
        else
        {
            Gate2.setExitDirect(LEFT);
        }
    }
    else if (secondNum < 133)
    {
        mapList[stage][24][13 + (secondNum - 130)] = '7';
        Gate2.setPos(24, 13 + (secondNum - 130));
        if (secondNum == 130)
        {
            Gate2.setExitDirect(DOWN_LEFT);
        }
        else
        {
            Gate2.setExitDirect(DOWN);
        }
    }
    else if (secondNum < 137)
    {
        mapList[stage][24 - (secondNum - 133)][16] = '7';
        Gate2.setPos(24 - (secondNum - 133), 16);
        if (secondNum == 133)
        {
            Gate2.setExitDirect(DOWN_RIGHT);
        }
        else
        {
            Gate2.setExitDirect(RIGHT);
        }
    }
    else
    {
        mapList[stage][20][16 - (secondNum - 137)] = '7';
        Gate2.setPos(20, 16 - (secondNum - 137));
        if (secondNum == 137)
        {
            Gate2.setExitDirect(UP_RIGHT);
        }
        else
        {
            Gate2.setExitDirect(UP);
        }
    }
    Gate1.setPairPtr(&Gate2);
}
