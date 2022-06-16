#pragma once
#include <time.h>
class Game {
public:
    int stage; // ���� ��������
    bool gameover = false;
    bool stageCleared = false;
    time_t starttime;
    time_t endtime;
    Game() {
        stage = 0;
    }

    void launchGame();
    void updateScreen(); // ȭ�� ������Ʈ ��ȯ�� - �������� Ŭ�����: 1 = Ŭ���� 0 = ��Ŭ����
    void nextStage(); // ���� ��������
    void gameStatusCheck();
    void gameCleared(); // ���� Ŭ�����
    void gameOvered(); // ���ӿ�����
};