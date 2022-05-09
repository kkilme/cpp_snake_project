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
    //컬러 설정
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_GREEN);
    
    //새로운 창 만들기
    win1 = newwin(40, 40, 3, 3);
    wbkgd(win1, COLOR_PAIR(1));
    wborder(win1, '|', '|', '-', '-', '+', '+', '+', '+');
    nodelay(stdscr, true);//getch()의 대기 시간 없앰. 원래 키를 받아오기 전까지 프로그램이 멈추지만 그렇지 않게 설정(하는듯)
    keypad(stdscr, true); // 키패드 값도 입력받을 수 있게 해줌. 이렇게 안할 시 방향키 입력이 안받아짐..
    attroff(COLOR_PAIR(1)); //colo_pair 사용종료.
    
    snake = makeSnake(stage); // snake 생성
  
    // 창에 맵 불러오기 
    map.getMap(win1, stage);

    //화면갱신
    wrefresh(win1);
}

bool Game::updateScreen() {
    gameover = moveSnake(stage); // snake 움직이기, 반환값 gameover: 게임오버 여부
    map.setMap(stage, snake[0].x, snake[0].y, 'h'); //snake 머리 그리기
    for (int i = 1; i < snake.size(); i++) {
        map.setMap(stage, snake[i].x, snake[i].y, 't'); //snake 꼬리 그리기
    }
    map.getMap(win1, stage); //출력
    wrefresh(win1);

    /***********************테스트용 코드*************************/
    if (snake[0].x == 1 && snake[0].y == 1) {// (1,1)로 이동 시 바로 다음 스테이지
        return true;
    }
    /************************************************************/

    return false; // 스테이지 클리어 안됨
}


void Game::nextStage() {
    if (stage == 2) { // 지금은 일단 마지막 스테이지 클리어시 종료
        endwin();
        exit(1);
    }
    stage++;
    snake = makeSnake(stage); // snake 다시 만듦
    map.getMap(win1, stage); // 맵 받아옴
    wrefresh(win1);
}