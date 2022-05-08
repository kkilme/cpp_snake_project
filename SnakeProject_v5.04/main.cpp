#include "curses.h"
#include "HomeMenu.h"
#include "Game.h"
#include "windows.h"
#include "Map.h"

int main() {

    //HomeMenu 띄우기
    HomeMenu homeMenu;
    homeMenu.loadHome();

    
    //선택 받아오기
    char selectedNum = getch(); 

    if (selectedNum == '1' || selectedNum == '2' || selectedNum == '3') { //1,2,3선택시 게임 스타트
        //game에서 stage띄우기
        Game game(selectedNum); // selectedNum -> game.stage // 원래 반드시 1스테이지부터 시작해야 하지만 지금은 테스트를 위해 선택한 스테이지로 설정
        game.launchGame();
        
        while (true) { // 게임 플레이중 계속 실행
            bool gameOver = game.overCheck(); //게임오버 체크
            if (gameOver) {
                break;
            }
            game.updateScreen();
            Sleep(500); // 0.5초 대기 (1000 = 1초)
        }
    }
    else if (selectedNum == '4') { // 4 선택하면 records창으로
        
    }
    else if (selectedNum == '5') { //5 선택하면 종료
        endwin();
        return 0;
    }
    
    
    getch(); 
    endwin();


    return 0;
}