#include "snake.h"
#include "Map.h"
#include "ItemClass.h"
#include "gate.h"
#include "Score.h"

#define WALL '1'
#define INC_ITEM '5'
#define DEC_ITEM '6'
#define SNAKE_TAIL '4'
#define GATE '7'

int headDir; // 머리 방향
int dir[4][2] = { {0,-1},{1,0},{0,1},{-1,0} }; // 위,오른쪽,아래,왼쪽 방향 - headDir에 따른 snake 이동 시 사용
extern vector<SnakePart> snake;
extern Map map;
extern ItemClass item;
extern Gate Gate1, Gate2;
extern Score score;


vector<SnakePart> makeSnake(const int stage) {
    vector<SnakePart> tempsnake; // snake 생성
    tempsnake.push_back(SnakePart(15, 16)); // snake 머리가 됨(스테이지의 중앙 위치)
    tempsnake.push_back(SnakePart(15, 17)); 
    tempsnake.push_back(SnakePart(15, 18)); // snake 꼬리 2개 (처음 길이는 3)

    /*테스트용 코드 - 처음 길이 6개*//*
    tempsnake.push_back(SnakePart(16, 18)); 
    tempsnake.push_back(SnakePart(17, 18));
    tempsnake.push_back(SnakePart(17, 19));*/
    /**********************************/

    headDir = UP; // 처음 머리 방향은 위쪽
    return tempsnake;
}

bool setHeadDir() {
    int key = getch();
    switch (key) {
        case KEY_UP: // 위쪽방향키 눌렀을때
            if (headDir != DOWN) {
                headDir = UP;
                return false;
            }
            else {
                return true; // 리턴값: 게임오버 여부
            }
        case KEY_RIGHT:
            if (headDir != LEFT) {
                headDir = RIGHT;
                return false;
            }
            else {
                return true;
            }
        case KEY_DOWN:
            if (headDir != UP) {
                headDir = DOWN;
                return false;
            }
            else {
                return true;
            }
        case KEY_LEFT:
            if (headDir != RIGHT) {
                headDir = LEFT;
                return false;
            }
            else {
                return true;
            }
           
    }
    return false;
}

bool moveSnake(const int stage) {
    int headNextX = snake[0].x + dir[headDir][0]; // 머리 다음위치 x
    int headNextY = snake[0].y + dir[headDir][1]; // 머리 다음위치 y
    bool checkIncItem = false; // 다음이 아이템'5'면 true
    bool checkDecItem = false; // 다음이 아이템'6'면 true

    if (map.mapList[stage][headNextY][headNextX] == INC_ITEM) { //아이템(INC_ITEM) '5'와 충돌할때의 경우의수 체크
        checkIncItem = true;
        map.mapList[stage][headNextY][headNextX] = ' ';
        item.countItem--; //아이템 갯수확인하는 변수 감소
        score.addIncItem();
    }

    else if (map.mapList[stage][headNextY][headNextX] == DEC_ITEM) { //아이템(DEC_ITEM) '6'과 충돌할때의 경우의수 체크
        checkDecItem = true;
        map.mapList[stage][headNextY][headNextX] = ' ';
        item.countItem--; 
        score.addDecItem();
    }

    if (map.mapList[stage][headNextY][headNextX] == WALL) { //벽(BLOCK) '1'과 충돌
        return true;
    }
    else if(map.mapList[stage][headNextY][headNextX] == SNAKE_TAIL && !(headNextX == snake[snake.size()-1].x && headNextY == snake[snake.size() - 1].y)) { //꼬리와 충돌
        return true;
    } 


    else { // snake move logic - 자세한 내용은 struct.txt 참조
        static int tempExitY = 0, tempExitX = 0;        // 꼬리가 gate에서 나왔는지 확인하기 위해 저장할 임시 변수 static을 필수로 넣어야 한다.
        if (map.mapList[stage][headNextY][headNextX] == GATE) { // Gate 에 들어간 경우
            score.addGate();    // gate에 들어간 횟수 +1
            if (headNextY == Gate1.getY() && headNextX == Gate1.getX()) // Gate1에 들어간 경우
            {
                tempExitY = Gate2.getExitY();   // 꼬리가 gate에서 나왔는지 확인할 기준이 될 변수 설정
                tempExitX = Gate2.getExitX();
                headNextY = tempExitY;      // 뱀의 머리를 연결된 게이트에서 나와야 할 지점으로 설정
                headNextX = tempExitX;
            }
            else
            {
                tempExitY = Gate1.getExitY();// Gate2에 들어간 경우
                tempExitX = Gate1.getExitX();
                headNextY = tempExitY;
                headNextX = tempExitX;
            }
        }
        int PrevX = snake[0].x;
        int PrevY = snake[0].y;
        int tempPrevX;
        int tempPrevY;
        snake[0].x = headNextX;
        snake[0].y = headNextY;
        if (snake[snake.size() - 1].y == tempExitY && snake[snake.size() - 1].x == tempExitX)   // 꼬리가 저장했던 임시 변수의 위치에 온 경우
        {
            map.mapList[stage][Gate1.getY()][Gate1.getX()] = '1';   // gate가 있던 위치를 모두 1로 교체
            map.mapList[stage][Gate2.getY()][Gate2.getX()] = '1';
            Gate1.delGates(stage, map);     // gate 삭제
            map.setGate(stage);             // gate 재설정
            tempExitY = 0;      // 임시 변수 초기화
            tempExitX = 0;
        }
        map.setMap(stage, snake[snake.size() - 1].x, snake[snake.size() - 1].y);
        for (unsigned int i = 1; i < snake.size(); i++)
        {
            tempPrevX = snake[i].x;
            tempPrevY = snake[i].y;
            snake[i].x = PrevX;
            snake[i].y = PrevY;
            PrevX = tempPrevX;
            PrevY = tempPrevY;
        }

        if (checkIncItem) { // '5'아이템과 충돌 시 꼬리 추가
            snake.push_back(SnakePart(PrevX, PrevY));
            checkIncItem = false;
            score.addSnakeLength(); // score에 snake_length +1
            if (Gate1.getY() == 0 && Gate1.getX() == 0)
            {
                map.setGate(stage);
            }
        }

        else if (checkDecItem) {//'6'아이템과 충돌 시 꼬리 추가
            SnakePart lastTail = snake.back();
            map.setMap(stage, lastTail.x,lastTail.y);
            snake.pop_back();
            checkDecItem = false;
            score.subSnakeLength(); // score에 snake_length -1
            if (score.getDecItem() == 2)    // 만약에 dec item 2개를 먹었으면 게임 오버
            {
                return true;
            }
        }
    }
    return false;
}