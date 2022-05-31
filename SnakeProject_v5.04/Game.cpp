#include "Game.h"
#include "curses.h"
#include "Map.h"
#include "snake.h"
#include "ItemClass.h"
#include "Score.h"


vector<SnakePart> snake;
Map map;
WINDOW* win1,* win2;
extern int headDir;
ItemClass item;
Score score;

void Game::launchGame()
{
    //�÷� ����
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    //���ο� â �����
    win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(stdscr, true);      //getch()�� ��� �ð� ����. ���� Ű�� �޾ƿ��� ������ ���α׷��� �������� �׷��� �ʰ� ����(�ϴµ�)
    keypad(stdscr, true);       // Ű�е� ���� �Է¹��� �� �ְ� ����. �̷��� ���� �� ����Ű �Է��� �ȹ޾���..
    attroff(COLOR_PAIR(1));     //colo_pair �������.
    
    // ���� ȭ��
    win2 = newwin(20, 40, 13, 53);
    wbkgd(win2, COLOR_PAIR(3));
    wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(stdscr, true);      //getch()�� ��� �ð� ����. ���� Ű�� �޾ƿ��� ������ ���α׷��� �������� �׷��� �ʰ� ����(�ϴµ�)
    keypad(stdscr, true);       // Ű�е� ���� �Է¹��� �� �ְ� ����. �̷��� ���� �� ����Ű �Է��� �ȹ޾���..
    attroff(COLOR_PAIR(3));     //colo_pair �������.

    snake = makeSnake(stage);   // snake ����
    score.setSnakeLength(snake.size()); // �����ǿ� �ʱ� �� ���� �Է�
    map.setGate(stage);     // Gate ����
    // â�� �� �ҷ�����
    map.getMap(win1, stage);

    //ȭ�鰻��
    wrefresh(win1);
    wrefresh(win2);
}

bool Game::updateScreen() {
    gameover = moveSnake(stage); // snake �����̱�, ��ȯ�� gameover: ���ӿ��� ����
    map.setMap(stage, snake[0].x, snake[0].y, 'h'); //snake �Ӹ� �׸���
    for (int i = 1; i < snake.size(); i++) {
        map.setMap(stage, snake[i].x, snake[i].y, 't'); //snake ���� �׸���
    }
    map.getMap(win1, stage);    // ���
    score.updateScore(win2);    // ���� ������Ʈ
    item.itemCreator(stage);    // �����ۻ���
    item.itemDeleter(stage);    // ������ �ʿ��� ����

    if (snake.size() < 3) {// snake ���̰� 3���������� gameover
        gameover = true ;
    }
    
    wrefresh(win1);
    wrefresh(win2);

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
    map.setGate(stage);         // gate ����
    snake = makeSnake(stage); // snake �ٽ� ����
    map.getMap(win1, stage); // �� �޾ƿ�
    item.listOfItem.clear(); //�޸𸮰����� ���� �����۰����ϴ� ���� �ʱ�ȭ
    item.countItem = 0; // ������ ���� 0���� ����
    score.resetScore();     // ���� �ʱ�ȭ
    wrefresh(win1);
}