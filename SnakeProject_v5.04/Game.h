
class Game {
public:
    int stage; // 현재 스테이지
    Game() {
        stage = 1;
    }
    Game(char selectedNum) {
        stage = selectedNum - '0';
    }

    void launchGame();
    void updateScreen(); // 화면 업데이트
    bool overCheck(); // 게임오버 체크

};