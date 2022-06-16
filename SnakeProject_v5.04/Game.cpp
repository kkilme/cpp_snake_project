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
    //컬러 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, COLOR_BLACK, COLOR_WHITE);
    //새로운 창 만들기
    win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(stdscr, true);      //getch()의 대기 시간 없앰. 원래 키를 받아오기 전까지 프로그램이 멈추지만 그렇지 않게 설정
    keypad(stdscr, true);       // 키패드 값도 입력받을 수 있게 해줌. 이렇게 안할 시 방향키 입력이 안받아짐
    attroff(COLOR_PAIR(1));     //colo_pair 사용종료.
    
    // 점수 화면
    win2 = newwin(10, 30, 8, 53);
    wbkgd(win2, COLOR_PAIR(3));
    wborder(win2, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(win2, true);      
    

    win3 = newwin(10, 30, 23, 53);
    wbkgd(win3, COLOR_PAIR(3));
    wborder(win3, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(win3, true);      
    attroff(COLOR_PAIR(3));     //colo_pair 사용종료.

    snake = makeSnake(stage);   // snake 생성
    score.resetScore(); // 점수판에 초기 뱀 길이 입력
    map.mapColorStart(); // 맵 요소 색상 on
    map.getMap(win1, stage);// 창에 맵 불러오기

    starttime = time(NULL); // 시작시간
    setRec();
    //화면갱신
    wrefresh(win1);
    wrefresh(win2);
    wrefresh(win3);
}

void Game::gameStatusCheck() {
    if (snake.size() < 3) {// snake 길이가 3보다작으면 gameover
        gameover = true;
    }
    stageCleared = score.isClear(win3);
}

void Game::updateScreen() {
    gameover = moveSnake(stage); // snake 움직이기, 반환값 gameover: 게임오버 여부
    map.setMap(stage, snake[0].x, snake[0].y, 'h'); //snake 머리 그리기
    for (int i = 1; i < snake.size(); i++) {
        map.setMap(stage, snake[i].x, snake[i].y, 't'); //snake 꼬리 그리기
    }
    map.getMap(win1, stage);    // 출력
    score.updateScore(win2);    // 점수 업데이트
    item.itemCreator(stage);    // 아이템생성
    item.itemDeleter(stage);    // 아이템 맵에서 제거
    wrefresh(win1);
    wrefresh(win2);
    wrefresh(win3);
}


void Game::nextStage() {
    stage++;
    stageCleared = false;
    snake = makeSnake(stage); // snake 다시 만듦
    map.getMap(win1, stage); // 맵 받아옴
    item.listOfItem.clear(); //메모리관리를 위해 아이템관리하는 백터 초기화
    Gate1.delGates(stage, map); // Gate 초기화
    item.countItem = 0; // 아이템 갯수 0으로 변경
    score.resetScore();     // 점수 초기화
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