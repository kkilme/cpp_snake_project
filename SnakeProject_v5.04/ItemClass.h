#pragma once
#include "Map.h"
#include <stdlib.h>
#include <time.h>
#include <vector>

extern Map map;
using std::vector;

class ItemClass {
    public:

        vector <ItemClass> listOfItem; //아이템을 관리할 벡터
        
        int x;
        int y;
        int createTime = time(NULL);
        int countItem = 0;

        ItemClass(const int ypos=0, const int xpos=0) { // 아이템 관리할때 백터에 아이템 클래스로 넣어서 관리
            x = xpos;
            y = ypos;
        }

        void itemCreator (const int stage) {
            if (countItem < 3) {
                srand(time(NULL));
                int boundaryY = sizeof(map.mapList[stage]) / sizeof(map.mapList[stage][0]); // 맵마다 세로길이 search
                int boundaryX = sizeof(map.mapList[stage][0]); // 맵마다 가로길이 search
                int y = rand() % boundaryY; // random y좌표
                int x = rand() % boundaryX; // random x좌표
                if (map.mapList[stage][y][x] == ' ') { // 5초에한번이라 실패하면 안생김
                    if (rand()%2 == 0) { // 랜덤으로 아이템 생성
                        map.mapList[stage][y][x] = '6';
                    }
                    else {
                        map.mapList[stage][y][x] = '5';
                    }
                    countItem++;
                    listOfItem.push_back(ItemClass(y, x)); //아이템 백터에 정보추가
                }
            }
        }

        void itemDeleter(const int stage) { //시간지나면 화면에서 아이템 지우는 함수
            for (int i = 0; i < listOfItem.size(); i++) {
                char checkMapItem = map.mapList[stage][listOfItem[i].y][listOfItem[i].x]; // 맵의 위치에 아이템있나 체크
                if (time(NULL) - listOfItem[i].createTime >= 5 && (checkMapItem == '5' || checkMapItem == '6')) { // 생성 했을때 5초 지났나 확인
                    map.mapList[stage][listOfItem[i].y][listOfItem[i].x] = ' '; //아이템을 blank로
                    countItem--; // 아이템 갯수로 관리하는 변수를 감소시킴
                }
            }
        };
        

};