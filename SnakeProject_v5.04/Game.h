#pragma once

class Game {
public:
    int stage; // ���� ��������
    bool gameover = false;
    bool stageCleared = false;
    Game() {
        stage = 0;
    }

    void launchGame();
    void updateScreen(); // ȭ�� ������Ʈ ��ȯ�� - �������� Ŭ�����: 1 = Ŭ���� 0 = ��Ŭ����
    void nextStage(); // ���� ��������
    void gameStatusCheck();
};