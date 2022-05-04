#include "curses.h"
#include "HomeMenu.h"
#include "gameLuncher.h"


int main() {

    //HomeMenu ����
    HomeMenu homeMenu;
    homeMenu.loadHome();

    
    //���� �޾ƿ���
    char selectedNum = getch(); 

    if (selectedNum == '1' || selectedNum == '2' || selectedNum == '3') { //1,2,3���ý� ���� ��ŸƮ
        //game luncher���� stage����
        GameLuncher gameLuncher;
        gameLuncher.lunchGame(selectedNum);
    }
    else if (selectedNum == '4') { // 4 �����ϸ� recordsâ����
        
    }
    else if (selectedNum == '5') { //5 �����ϸ� ����
        endwin();
        return 0;
    }
    
    
    getch(); 
    endwin();


    return 0;
}