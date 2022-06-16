#include "Game.h"
#include "curses.h"
#include "Map.h"
#include "snake.h"
#include "ItemClass.h"
#include "Score.h"
#include "gate.h"
#include "Screen.h"

vector<SnakePart> snake;
Map map;
WINDOW* win1,* win2,* win3;
extern int headDir;
extern Gate Gate1;
extern Screen screen;
ItemClass item;
Score score;
extern void setRec();


void Game::launchGame()
{
    //�÷� ����
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    //���ο� â �����
    win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(stdscr, true);      //getch()�� ��� �ð� ����. ���� Ű�� �޾ƿ��� ������ ���α׷��� �������� �׷��� �ʰ� ����
    keypad(stdscr, true);       // Ű�е� ���� �Է¹��� �� �ְ� ����. �̷��� ���� �� ����Ű �Է��� �ȹ޾���
    attroff(COLOR_PAIR(1));     //colo_pair �������.
    
    // ���� ȭ��
    win2 = newwin(10, 30, 8, 53);
    wbkgd(win2, COLOR_PAIR(3));
    wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(win2, true);      
    

    win3 = newwin(10, 30, 23, 53);
    wbkgd(win3, COLOR_PAIR(3));
    wborder(win3, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(win3, true);      
    attroff(COLOR_PAIR(3));     //colo_pair �������.

    snake = makeSnake(stage);   // snake ����
    score.resetScore(); // �����ǿ� �ʱ� �� ���� �Է�
    map.mapColorStart(); // �� ��� ���� on
    map.getMap(win1, stage);// â�� �� �ҷ�����

    starttime = time(NULL); // ���۽ð�
    setRec();
    //ȭ�鰻��
    wrefresh(win1);
    wrefresh(win2);
    wrefresh(win3);
}

void Game::gameStatusCheck() {
    if (snake.size() < 3) {// snake ���̰� 3���������� gameover
        gameover = true;
    }
    stageCleared = score.isClear(win3);
}

void Game::updateScreen() {
    gameover = moveSnake(stage); // snake �����̱�, ��ȯ�� gameover: ���ӿ��� ����
    map.setMap(stage, snake[0].x, snake[0].y, 'h'); //snake �Ӹ� �׸���
    for (int i = 1; i < snake.size(); i++) {
        map.setMap(stage, snake[i].x, snake[i].y, 't'); //snake ���� �׸���
    }
    map.getMap(win1, stage);    // ���
    score.updateScore(win2);    // ���� ������Ʈ
    item.itemCreator(stage);    // �����ۻ���
    item.itemDeleter(stage);    // ������ �ʿ��� ����
    wrefresh(win1);
    wrefresh(win2);
    wrefresh(win3);
}


void Game::nextStage() {
    stage++;
    stageCleared = false;
    snake = makeSnake(stage); // snake �ٽ� ����
    map.getMap(win1, stage); // �� �޾ƿ�
    item.listOfItem.clear(); //�޸𸮰����� ���� �����۰����ϴ� ���� �ʱ�ȭ
    Gate1.delGates(stage, map); // Gate �ʱ�ȭ
    item.countItem = 0; // ������ ���� 0���� ����
    score.resetScore();     // ���� �ʱ�ȭ
    wrefresh(win1);
}

void Game::gameCleared() {
    nodelay(stdscr, false);
    endtime = time(NULL);
    delwin(win1);
    delwin(win2);
    delwin(win3);
    map.resetMap();
    item.listOfItem.clear();
    item.countItem = 0;
    screen.loadRecord(true, endtime-starttime);
}

void Game::gameOvered() {
    nodelay(stdscr, false);
    delwin(win1);
    delwin(win2);
    delwin(win3);
    map.resetMap();
    item.listOfItem.clear();
    item.countItem = 0;
    screen.gameoverScreen();
}