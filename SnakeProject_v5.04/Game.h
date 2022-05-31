#pragma once

class Game {
public:
    int stage; // 현재 스테이지
    bool gameover = false;
    Game() {
        stage = 0;
    }

    void launchGame();
    bool updateScreen(); // 화면 업데이트 반환값 - 스테이지 클리어여부: 1 = 클리어 0 = 미클리어
    void nextStage(); // 다음스테이지
};