#include "Game.h"
#include "curses.h"
#include "Map.h"
#include "snake.h"

vector<SnakePart> snake;
Map map;
WINDOW* win1;
extern int headDir;

void Game::launchGame()
{
    //�÷� ����
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    
    //���ο� â �����
    win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(stdscr, true);//getch()�� ��� �ð� ����. ���� Ű�� �޾ƿ��� ������ ���α׷��� �������� �׷��� �ʰ� ����(�ϴµ�)
    keypad(stdscr, true); // Ű�е� ���� �Է¹��� �� �ְ� ����. �̷��� ���� �� ����Ű �Է��� �ȹ޾���..
    attroff(COLOR_PAIR(1)); //colo_pair �������.
    
    snake = makeSnake(stage); // snake ����
  
    // â�� �� �ҷ����� 
    map.getMap(win1, stage);

    //ȭ�鰻��
    wrefresh(win1);
}

bool Game::updateScreen() {
    gameover = moveSnake(stage); // snake �����̱�, ��ȯ�� gameover: ���ӿ��� ����
    map.setMap(stage, snake[0].x, snake[0].y, 'h'); //snake �Ӹ� �׸���
    for (int i = 1; i < snake.size(); i++) {
        map.setMap(stage, snake[i].x, snake[i].y, 't'); //snake ���� �׸���
    }
    map.getMap(win1, stage); //���
    wrefresh(win1);

    /***********************�׽�Ʈ�� �ڵ�*************************/
    if (snake[0].x == 1 && snake[0].y == 1) {// (1,1)�� �̵� �� �ٷ� ���� ��������
        return true;
    }
    /************************************************************/

    return false; // �������� Ŭ���� �ȵ�
}


void Game::nextStage() {
    if (stage == 2) { // ������ �ϴ� ������ �������� Ŭ����� ����
        endwin();
        exit(1);
    }
    stage++;
    snake = makeSnake(stage); // snake �ٽ� ����
    map.getMap(win1, stage); // �� �޾ƿ�
    wrefresh(win1);
}