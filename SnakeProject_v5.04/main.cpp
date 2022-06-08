#include "curses.h"
#include "Screen.h"
#include "Game.h"
#include "windows.h"
#include "Map.h"
#include "snake.h"

int main() {

    //HomeMenu ����
    Screen screen;
    screen.loadHome();

    
    //���� �޾ƿ���
    char selectedNum = getch();

    if (selectedNum == '1') { //1���ý� ���� ��ŸƮ
        delwin(screen.menu); // �޴����� â ����
        screen.resetScreen();
        Game game; // 1������������ ����
        game.launchGame();
        int timer = 0;
        while (true) { // ���� �÷����� ��� ����
            if (setHeadDir()) {  //0.025�ʸ��� key�� �Է¹޾Ƽ� ���⼳��, ���� ���� �ݴ�Ű �Է½� gameover
                Sleep(1000); // 1�� ��� �� ��������
                endwin();
                break;
            };
            game.gameStatusCheck(); // ���� ���� üũ (���ӿ���/�������� Ŭ����)
            if (timer >= 200 || game.gameover) { // ���� �ð����� ȭ�� ������Ʈ    
                if (!game.gameover) { game.updateScreen(); } //ȭ�� ������Ʈ
                else {//���ӿ��� üũ
                    Sleep(1000); // 1�� ��� �� ��������
                    endwin();
                    break;
                }
                timer = 0;
                if (game.stageCleared) { //Ŭ���� �� ���� ��������
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