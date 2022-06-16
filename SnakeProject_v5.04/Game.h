#pragma once
#include <time.h>
class Game {
public:
    int stage; // 현재 스테이지
    bool gameover = false;
    bool stageCleared = false;
    time_t starttime;
    time_t endtime;
    Game() {
        stage = 0;
    }

    void launchGame();
    void updateScreen(); // 화면 업데이트 반환값 - 스테이지 클리어여부: 1 = 클리어 0 = 미클리어
    void nextStage(); // 다음 스테이지
    void gameStatusCheck();
    void gameCleared(); // 게임 클리어시
    void gameOvered(); // 게임오버시
};