#include <vector>

using std::vector;

class SnakePart { //snake를 이루는 한칸한칸의 부분 - x,y좌표를 가짐
    
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

