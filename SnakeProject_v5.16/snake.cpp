#include "snake.h"
#include "Map.h"
#include "ItemClass.h"


int headDir; // �Ӹ� ����
int dir[4][2] = { {0,-1},{1,0},{0,1},{-1,0} }; // ��,������,�Ʒ�,���� ���� - headDir�� ���� snake �̵� �� ���
extern vector<SnakePart> snake;
extern Map map;
extern ItemClass item;

vector<SnakePart> makeSnake(int stage) {
    vector<SnakePart> tempsnake; // snake ����
    tempsnake.push_back(SnakePart(15, 16)); // snake �Ӹ��� ��(���������� �߾� ��ġ)
    tempsnake.push_back(SnakePart(15, 17)); 
    tempsnake.push_back(SnakePart(15, 18)); // snake ���� 2�� (ó�� ���̴� 3)

    /*�׽�Ʈ�� �ڵ� - ó�� ���� 6��*/
    //tempsnake.push_back(SnakePart(16, 18)); 
    //tempsnake.push_back(SnakePart(17, 18));
    //tempsnake.push_back(SnakePart(17, 19));
    /**********************************/

    headDir = UP; // ó�� �Ӹ� ������ ����
    return tempsnake;
}

void setHeadDir() {
    int key = getch();
    
    switch (key) {
        case KEY_UP: // ���ʹ���Ű ��������
            if (headDir != DOWN) {
                headDir = UP;
                break;
            }
            else {
                exit(0); // �ݴ� �����̸� gameover
            }
        case KEY_RIGHT:
            if (headDir != LEFT) {
                headDir = RIGHT;
                break;
            }
            else {
                exit(0);
            }
        case KEY_DOWN:
            if (headDir != UP) {
                headDir = DOWN;
                break;
            }
            else {
                exit(0);
            }
        case KEY_LEFT:
            if (headDir != RIGHT) {
                headDir = LEFT;
                break;
            }
            else {
                exit(0);
            }
    }
    /*return headDir;*/ //���� �ʿ� ������?
}

bool moveSnake(int stage) {
    int headNextX = snake[0].x + dir[headDir][0]; // �Ӹ� ������ġ x
    int headNextY = snake[0].y + dir[headDir][1]; // �Ӹ� ������ġ y
    bool checkIncItem = false; // ������ ������'5'�� true
    bool checkDecItem = false; // ������ ������'6'�� true

    if (map.mapList[stage][headNextY][headNextX] == '5') { //������ '5'�� �浹�Ҷ��� ����Ǽ� üũ
        checkIncItem = true;
        map.mapList[stage][headNextY][headNextX] = ' ';
        item.countItem--; //������ ����Ȯ���ϴ� ���� ����
        
    }
    else if (map.mapList[stage][headNextY][headNextX] == '6') { //������ '6'�� �浹�Ҷ��� ����Ǽ� üũ
        checkDecItem = true;
        map.mapList[stage][headNextY][headNextX] = ' ';
        item.countItem--; 
    }

    if (map.mapList[stage][headNextY][headNextX] == '1') { //���� �浹
        return true;
    }
    else if(map.mapList[stage][headNextY][headNextX] == '4' && !(headNextX == snake[snake.size()-1].x && headNextY == snake[snake.size() - 1].y)) { //������ �浹
        return true;
    } // else if(����Ʈ�� �浹) -- ���밡��
    else { // snake move logic - �ڼ��� ������ struct.txt ����
        int PrevX = snake[0].x;
        int PrevY = snake[0].y;
        int tempPrevX;
        int tempPrevY;
        snake[0].x = headNextX;
        snake[0].y = headNextY;
        map.setMap(stage, snake[snake.size() - 1].x, snake[snake.size() - 1].y);
        for (unsigned int i = 1; i < snake.size(); i++) {
            tempPrevX = snake[i].x;
            tempPrevY = snake[i].y;
            snake[i].x = PrevX;
            snake[i].y = PrevY;
            PrevX = tempPrevX;
            PrevY = tempPrevY;
        }
        if (checkIncItem) { // '5'�����۰� �浹 �� ���� �߰�
            snake.push_back(SnakePart(PrevX, PrevY));
            checkIncItem = false;
            
        }
        else if (checkDecItem) {//'6'�����۰� �浹 �� ���� �߰�
            SnakePart lastTail = snake.back();
            map.setMap(stage, lastTail.x,lastTail.y);
            snake.pop_back();
            checkDecItem = false;
        }
    }
    return false;
}