#include "curses.h"
#include "HomeMenu.h"
#include "Game.h"
#include "windows.h"
#include "Map.h"

int main() {

    //HomeMenu ����
    HomeMenu homeMenu;
    homeMenu.loadHome();

    
    //���� �޾ƿ���
    char selectedNum = getch(); 

    if (selectedNum == '1' || selectedNum == '2' || selectedNum == '3') { //1,2,3���ý� ���� ��ŸƮ
        //game���� stage����
        Game game(selectedNum); // selectedNum -> game.stage // ���� �ݵ�� 1������������ �����ؾ� ������ ������ �׽�Ʈ�� ���� ������ ���������� ����
        game.launchGame();
        
        while (true) { // ���� �÷����� ��� ����
            bool gameOver = game.overCheck(); //���ӿ��� üũ
            if (gameOver) {
                break;
            }
            game.updateScreen();
            Sleep(500); // 0.5�� ��� (1000 = 1��)
        }
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