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
    //�÷� ����
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    
    //���ο� â �����
    win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(win1, true); // getch()�� ��� �ð� ����. ���� Ű�� �޾ƿ��� ������ ���α׷��� �������� �׷��� �ʰ� ����(�ϴµ�)
    attroff(COLOR_PAIR(1)); //colo_pair �������.
    
    snake = makeSnake(stage); // snake ����
  
    // â�� �� �ҷ����� 
    map.getMap(win1, stage);

    //ȭ�鰻��
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