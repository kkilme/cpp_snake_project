#include "snake.h"
#include "Map.h"

vector<SnakePart> makeSnake(int stage); // snake ���� (�������� ����) , stage�� ���ڷ� �޴� ����: ���� ������������ �ٸ� ��ġ�� �����Ҽ��� �ֱ� ���� (������ ��ġ ����)
int setheadDir(); // Ű �Է¹޾� snake�� �ٶ󺸴� ���� ����
vector<int> snakeNextPos; // snake ���� ��ġ
void moveSnake(); // �����̱�

vector<SnakePart> makeSnake(int stage) {
    vector<SnakePart> snake; // snake ����(���������� �߾� ��ġ)
    snake.push_back(SnakePart(15, 16)); // snake �Ӹ�
    snake.push_back(SnakePart(15, 17)); 
    snake.push_back(SnakePart(15, 18)); // snake ���� 2�� (ó�� ���̴� 3)
    return snake;
}