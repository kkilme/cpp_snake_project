#pragma once

class Game {
public:
    int stage; // ���� ��������
    bool gameover = false;
    Game() {
        stage = 0;
    }

    void launchGame();
    bool updateScreen(); // ȭ�� ������Ʈ ��ȯ�� - �������� Ŭ�����: 1 = Ŭ���� 0 = ��Ŭ����
    void nextStage(); // ������������
};