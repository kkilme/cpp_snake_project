#include "snake.h"
#include "Map.h"

vector<SnakePart> makeSnake(int stage); // snake 생성 (스테이지 시작) , stage를 인자로 받는 이유: 추후 스테이지마다 다른 위치에 생성할수도 있기 때문 (지금은 위치 고정)
int setheadDir(); // 키 입력받아 snake가 바라보는 방향 설정
vector<int> snakeNextPos; // snake 다음 위치
void moveSnake(); // 움직이기

vector<SnakePart> makeSnake(int stage) {
    vector<SnakePart> snake; // snake 생성(스테이지의 중앙 위치)
    snake.push_back(SnakePart(15, 16)); // snake 머리
    snake.push_back(SnakePart(15, 17)); 
    snake.push_back(SnakePart(15, 18)); // snake 꼬리 2개 (처음 길이는 3)
    return snake;
}