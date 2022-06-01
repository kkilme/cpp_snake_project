#pragma once
#include "Map.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

extern Map map;
using std::vector;

class ItemClass {
    public:

        vector <ItemClass> listOfItem; //�������� ������ ����
        
        int x;
        int y;
        int createTime = time(NULL);
        int countItem = 0;

        ItemClass(const int ypos=0, const int xpos=0) { // ������ �����Ҷ� ���Ϳ� ������ Ŭ������ �־ ����
            x = xpos;
            y = ypos;
        }

        void itemCreator (const int stage) {
            if (countItem < 3) {
                srand(time(NULL));
                int boundaryY = sizeof(map.mapList[stage]) / sizeof(map.mapList[stage][0]); // �ʸ��� ���α��� search
                int boundaryX = sizeof(map.mapList[stage][0]); // �ʸ��� ���α��� search
                int y = rand() % boundaryY; // random y��ǥ
                int x = rand() % boundaryX; // random x��ǥ
                if (map.mapList[stage][y][x] == ' ') { // 5�ʿ��ѹ��̶� �����ϸ� �Ȼ���
                    if (rand()%2 == 0) { // �������� ������ ����
                        map.mapList[stage][y][x] = '6';
                    }
                    else {
                        map.mapList[stage][y][x] = '5';
                    }
                    countItem++;
                    listOfItem.push_back(ItemClass(y, x)); //������ ���Ϳ� �����߰�
                }
            }
        }

        void itemDeleter(const int stage) { //�ð������� ȭ�鿡�� ������ ����� �Լ�
            for (int i = 0; i < listOfItem.size(); i++) {
                char checkMapItem = map.mapList[stage][listOfItem[i].y][listOfItem[i].x]; // ���� ��ġ�� �������ֳ� üũ
                if (time(NULL) - listOfItem[i].createTime >= 5 && (checkMapItem == '5' || checkMapItem == '6')) { // ���� ������ 5�� ������ Ȯ��
                    map.mapList[stage][listOfItem[i].y][listOfItem[i].x] = ' '; //�������� blank��
                    countItem--; // ������ ������ �����ϴ� ������ ���ҽ�Ŵ
                }
            }
        };
        

};