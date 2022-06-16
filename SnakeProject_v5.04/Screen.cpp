#include "Screen.h"
#pragma warning(disable:4996)
extern vector<vector<time_t>> rec;
extern void insertRec(time_t date, time_t gametime);
extern void saveRec();
extern void setRec();
void Screen::loadHome() {
    //기본 창 생성 및, 사이즈 조절.
    initscr();
    resize_term(50, 100);

    noecho(); //입력을 화면에 표시 안되게하는 함수

    //기본 창 color설정
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(2));

    border('|', '|', '-', '-', '+', '+', '+', '+');
    
    refresh();
    Screen::loadMenu();
}

void Screen::loadMenu() {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    menu = newwin(8 + menuLength, 30, 16, 35); //홈화면 메뉴창
    // stage 선택지 띄우기
    wbkgd(menu, COLOR_PAIR(1));
    for (int i = 0; i < menuLength; i++) {
        mvwprintw(menu, 2*(i+1), 1, menuList[i]);
    }
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');   
    attroff(COLOR_PAIR(1));     //colo_pair 사용종료.
    wrefresh(menu);
}

void Screen::resetScreen() { // 창 삭제후 스크린 리셋
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(2));
    refresh();
}

void Screen::loadRecord(bool iscleared, time_t cleartime) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    if (!iscleared) { // 메뉴화면에서 레코드 선택
        setRec();
        delwin(menu);
        resetScreen();
        record = newwin(33, 50, 6, 25); //레코드창
        mvwprintw(record, 2, 18, "Top 10 records");
        mvwprintw(record, 4, 10, "Time");
        mvwprintw(record, 4, 34, "Date");
        wbkgd(record, COLOR_PAIR(1));
        for (int i = 0; i < rec.size(); i++) {
            if (rec[i][1] == INT_MAX) { 
                if (rec.size() == 1) {
                    mvwprintw(record, 17, 16, "No record set yet.."); // 레코드 없을시
                }
                continue;
            }
            long int min = rec[i][1] / 60;
            long int sec = rec[i][1] % 60;
            string t = to_string(min) + "m " + to_string(sec) + "s";
            vector<char> gametime(t.begin(), t.end());
            string strgamedate = ctime(&rec[i][0]);
            vector<char> gamedate(strgamedate.begin(), strgamedate.end());
            string rank = to_string(i + 1) + '.';
            vector<char> ranking(rank.begin(), rank.end());
            gametime.push_back('\0');
            gamedate.push_back('\0');
            ranking.push_back('\0');
            mvwprintw(record, 2 * (i + 1) + 5, 2, &ranking[0]);
            mvwprintw(record, 2 * (i + 1) + 5, 6, &gametime[0]);
            mvwprintw(record, 2 * (i + 1) + 5, 24, &gamedate[0]);
        }
        mvwprintw(record, 30, 13, "Press any key to return");
        wborder(record, '|', '|', '-', '-', '+', '+', '+', '+');
        attroff(COLOR_PAIR(1));     //colo_pair 사용종료.
        wrefresh(record);
    }
    else {
        resetScreen();
        record = newwin(33, 50, 6, 25); //레코드창
        mvwprintw(record, 3, 5, "Congratulations!!");
        mvwprintw(record, 3, 25, "Your record:");
        mvwprintw(record, 5, 18, "Top 10 records");
        mvwprintw(record, 7, 10, "Time");
        mvwprintw(record, 7, 34, "Date");
        long int min = cleartime / 60;
        long int sec = cleartime % 60;
        string t = to_string(min) + "m " + to_string(sec) + "s"; // 이번 판 클리어 시간
        vector<char> gametime(t.begin(), t.end());
        gametime.push_back('\0');
        mvwprintw(record, 3, 38, &gametime[0]);
        time_t gamedate = time(NULL);
        insertRec(gamedate, cleartime);
        wbkgd(record, COLOR_PAIR(1));
        int n = rec.size() > 10 ? 10 : rec.size();
        for (int i = 0; i < n; i++) { // 기록 표시
            if (rec[i][1] == INT_MAX) { continue; }
            long int min = rec[i][1] / 60;
            long int sec = rec[i][1] % 60;
            string t = to_string(min)+"m "+to_string(sec)+"s";
            vector<char> gametime(t.begin(), t.end());
            string strgamedate = ctime(&rec[i][0]);
            vector<char> gamedate(strgamedate.begin(),strgamedate.end());
            string rank = to_string(i+1) + '.';
            vector<char> ranking(rank.begin(), rank.end());
            gametime.push_back('\0');
            gamedate.push_back('\0');
            ranking.push_back('\0');
            mvwprintw(record, 2 * (i + 1) + 7, 2, &ranking[0]);
            mvwprintw(record, 2 * (i + 1) + 7, 6, &gametime[0]);
            mvwprintw(record, 2 * (i + 1) + 7, 24, &gamedate[0]);
        }
        mvwprintw(record, 30, 10, "Press any key to return to main menu");
        wborder(record, '|', '|', '-', '-', '+', '+', '+', '+');
        attroff(COLOR_PAIR(1));     //colo_pair 사용종료.
        wrefresh(record);
        saveRec(); // 파일 입출력을 통해 기록 저장
        getch();
    }
}

void Screen::gameoverScreen() {
    resetScreen();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    gameover = newwin(10, 40, 15, 30); //게임오버 화면
    // stage 선택지 띄우기
    wbkgd(gameover, COLOR_PAIR(1));
    mvwprintw(gameover, 2,14, "Game Over..");
    mvwprintw(gameover, 8, 2, "Press any key to return to main menu");
    wborder(gameover, '|', '|', '-', '-', '+', '+', '+', '+');
    attroff(COLOR_PAIR(1));     //colo_pair 사용종료.
    wrefresh(gameover);
    getch();
}