#include "Game.h"
#include "curses.h"
#include "Map.h"
#include "snake.h"

vector<SnakePart> makeSnake(int stage);
vector<SnakePart> snake;
Map map;
WINDOW* win1;

void Game::launchGame()
{
    //컬러 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    
    //새로운 창 만들기
    win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(win1, true); // getch()의 대기 시간 없앰. 원래 키를 받아오기 전까지 프로그램이 멈추지만 그렇지 않게 설정(하는듯)
    attroff(COLOR_PAIR(1)); //colo_pair 사용종료.
    
    snake = makeSnake(stage); // snake 생성
  
    // 창에 맵 불러오기 
    map.getMap(win1, stage);

    //화면갱신
    wrefresh(win1);
}

void Game::updateScreen() {
    map.setMap(stage, snake[0].x, snake[0].y, 'h');
    for (int i = 1; i < snake.size(); i++) {
        map.setMap(stage, snake[i].x, snake[i].y, 't');
    }
    map.getMap(win1, stage);
    wrefresh(win1);
}

bool Game::overCheck() {
    return false;
}