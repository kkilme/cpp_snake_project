#include <vector>

using std::vector;

class SnakePart { //snake�� �̷�� ��ĭ��ĭ�� �κ� - x,y��ǥ�� ����
    
public:
    int x;
    int y;
    SnakePart(int xpos, int ypos) {
        x = xpos;
        y = ypos;
    }
    SnakePart() {
        x = 0;
        y = 0;
    }
};

