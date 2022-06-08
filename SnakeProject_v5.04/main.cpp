#include "curses.h"
#include "Screen.h"
#include "Game.h"
#include "windows.h"
#include "Map.h"
#include "snake.h"

int main() {

    //HomeMenu 띄우기
    Screen screen;
    screen.loadHome();

    
    //선택 받아오기
    char selectedNum = getch();

    if (selectedNum == '1') { //1선택시 게임 스타트
        delwin(screen.menu); // 메뉴선택 창 삭제
        screen.resetScreen();
        Game game; // 1스테이지부터 시작
        game.launchGame();
        int timer = 0;
        while (true) { // 게임 플레이중 계속 실행
            if (setHeadDir()) {  //0.025초마다 key값 입력받아서 방향설정, 가는 방향 반대키 입력시 gameover
                Sleep(1000); // 1초 대기 후 게임종료
                endwin();
                break;
            };
            game.gameStatusCheck(); // 게임 상태 체크 (게임오버/스테이지 클리어)
            if (timer >= 200 || game.gameover) { // 일정 시간마다 화면 업데이트    
                if (!game.gameover) { game.updateScreen(); } //화면 업데이트
                else {//게임오버 체크
                    Sleep(1000); // 1초 대기 후 게임종료
                    endwin();
                    break;
                }
                timer = 0;
                if (game.stageCleared) { //클리어 시 다음 스테이지
                    game.nextStage();
                }
            }
            timer += 25;
            Sleep(25); // 일정시간 대기 (1000 = 1초, 25 = 0.025초)
        }
    }
    else if (selectedNum == '2') { // 2 선택하면 records창으로
        
    }
    else if (selectedNum == '3') { // 3 선택하면 종료
        endwin();
        return 0;
    }
    getch(); 
    endwin();


    return 0;
}