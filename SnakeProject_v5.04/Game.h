
class Game {
public:
    int stage; // ���� ��������
    Game() {
        stage = 1;
    }
    Game(char selectedNum) {
        stage = selectedNum - '0';
    }

    void launchGame();
    void updateScreen(); // ȭ�� ������Ʈ
    bool overCheck(); // ���ӿ��� üũ

};