#pragma once

#include <vector>
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3

using std::vector;

class SnakePart { //snake를 이루는 한칸한칸의 부분 - x,y좌표를 가짐
    
public:
    int x;
    int y;
    
    SnakePart(const int xpos, const int ypos) {
        x = xpos;
        y = ypos;
    }
    SnakePart() {
        x = 0;
        y = 0;
    }
};

bool moveSnake(const int stage); // snake 움직이기, 반환값: 게임오버 여부 (true = 게임오버)
vector<SnakePart> makeSnake(const int stage); // snake 생성 (스테이지 시작) , stage를 인자로 넣어둔 이유: 추후 스테이지마다 시작 위치를 다르게할지도 몰라서 (지금은 위치 고정)
bool setHeadDir(); // 키 입력받아 snake가 바라보는 방향 설정