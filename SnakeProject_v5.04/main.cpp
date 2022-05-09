#include "curses.h"
#include "HomeMenu.h"
#include "Game.h"
#include "windows.h"
#include "Map.h"
#include "snake.h"

int main() {

    //HomeMenu ����
    HomeMenu homeMenu;
    homeMenu.loadHome();

    
    //���� �޾ƿ���
    char selectedNum = getch(); 

    if (selectedNum == '1') { //1���ý� ���� ��ŸƮ
        //game���� stage����
        Game game; // 1������������ ����
        game.launchGame();
        int timer = 0;
        while (true) { // ���� �÷����� ��� ����
            setHeadDir(); //0.025�ʸ��� key�� �Է¹޾Ƽ� ���⼳��
            if (timer >= 200) { // ���� �ð����� ȭ�� ������Ʈ
                if (game.gameover) {//���ӿ��� üũ
                    Sleep(1000); // 1�� ��� �� ��������
                    endwin();
                    break;
                }
                timer = 0;
                bool clear = game.updateScreen(); //ȭ�� ������Ʈ
                if (clear) { //Ŭ���� �� ���� ��������
                    game.nextStage();
                }
            }
            timer += 25;
            Sleep(25); // �����ð� ��� (1000 = 1��, 25 = 0.025��)
        }
    }
    else if (selectedNum == '2') { // 2 �����ϸ� recordsâ����
        
    }
    else if (selectedNum == '3') { // 3 �����ϸ� ����
        endwin();
        return 0;
    }
    
    
    getch(); 
    endwin();


    return 0;
}