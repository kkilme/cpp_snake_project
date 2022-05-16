#include "snake.h"
#include "Map.h"

int headDir; // 머리 방향
int dir[4][2] = { {0,-1},{1,0},{0,1},{-1,0} }; // 위,오른쪽,아래,왼쪽 방향 - headDir에 따른 snake 이동 시 사용
extern vector<SnakePart> snake;
extern Map map;

vector<SnakePart> makeSnake(int stage) {
    vector<SnakePart> tempsnake; // snake 생성
    tempsnake.push_back(SnakePart(15, 16)); // snake 머리가 됨(스테이지의 중앙 위치)
    tempsnake.push_back(SnakePart(15, 17)); 
    tempsnake.push_back(SnakePart(15, 18)); // snake 꼬리 2개 (처음 길이는 3)

    /*▼▼▼테스트용 코드 - 처음 길이 6개▼▼▼*/
    tempsnake.push_back(SnakePart(16, 18)); 
    tempsnake.push_back(SnakePart(17, 18));
    tempsnake.push_back(SnakePart(17, 19));
    /**********************************/

    headDir = UP; // 처음 머리 방향은 위쪽
    return tempsnake;
}

void setHeadDir() {
    int key = getch();
    
    switch (key) {
        case KEY_UP: // 위쪽방향키 눌렀을때
            if (headDir != DOWN) {
                headDir = UP;
                break;
            }
            else {
                exit(0); // 반대 방향이면 gameover
            }
        case KEY_RIGHT:
            if (headDir != LEFT) {
                headDir = RIGHT;
                break;
            }
            else {
                exit(0);
            }
        case KEY_DOWN:
            if (headDir != UP) {
                headDir = DOWN;
                break;
            }
            else {
                exit(0);
            }
        case KEY_LEFT:
            if (headDir != RIGHT) {
                headDir = LEFT;
                break;
            }
            else {
                exit(0);
            }
    }
    /*return headDir;*/ //리턴 필요 없을듯?
}

bool moveSnake(int stage) {
    int headNextX = snake[0].x + dir[headDir][0]; // 머리 다음위치 x
    int headNextY = snake[0].y + dir[headDir][1]; // 머리 다음위치 y
    if (map.mapList[stage][headNextY][headNextX] == '1') { //벽과 충돌
        return true;
    }
    else if(map.mapList[stage][headNextY][headNextX] == '4' && !(headNextX == snake[snake.size()-1].x && headNextY == snake[snake.size() - 1].y)) { //꼬리와 충돌
        return true;
    } //else if(아이템과 충돌) // else if(게이트와 충돌) -- 응용가능
    else { // snake move logic - 자세한 내용은 struct.txt 참조
        int PrevX = snake[0].x;
        int PrevY = snake[0].y;
        int tempPrevX;
        int tempPrevY;
        snake[0].x = headNextX;
        snake[0].y = headNextY;
        map.setMap(stage, snake[snake.size() - 1].x, snake[snake.size() - 1].y);
        for (int i = 1; i < snake.size(); i++) {
            tempPrevX = snake[i].x;
            tempPrevY = snake[i].y;
            snake[i].x = PrevX;
            snake[i].y = PrevY;
            PrevX = tempPrevX;
            PrevY = tempPrevY;
        }
    }
    return false;
}