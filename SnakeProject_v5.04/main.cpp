#include "curses.h"
#include "HomeMenu.h"
#include "gameLuncher.h"


int main() {

    //HomeMenu 띄우기
    HomeMenu homeMenu;
    homeMenu.loadHome();

    
    //선택 받아오기
    char selectedNum = getch(); 

    if (selectedNum == '1' || selectedNum == '2' || selectedNum == '3') { //1,2,3선택시 게임 스타트
        //game luncher에서 stage띄우기
        GameLuncher gameLuncher;
        gameLuncher.lunchGame(selectedNum);
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