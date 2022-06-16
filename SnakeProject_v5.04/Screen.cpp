#include "Screen.h"
#pragma warning(disable:4996)
extern vector<vector<time_t>> rec;
extern void insertRec(time_t date, time_t gametime);
extern void saveRec();
extern void setRec();
void Screen::loadHome() {
    //�⺻ â ���� ��, ������ ����.
    initscr();
    resize_term(50, 100);

    noecho(); //�Է��� ȭ�鿡 ǥ�� �ȵǰ��ϴ� �Լ�

    //�⺻ â color����
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
    menu = newwin(8 + menuLength, 30, 16, 35); //Ȩȭ�� �޴�â
    // stage ������ ����
    wbkgd(menu, COLOR_PAIR(1));
    for (int i = 0; i < menuLength; i++) {
        mvwprintw(menu, 2*(i+1), 1, menuList[i]);
    }
    wborder(menu, '|', '|', '-', '-', '+', '+', '+', '+');   
    attroff(COLOR_PAIR(1));     //colo_pair �������.
    wrefresh(menu);
}

void Screen::resetScreen() { // â ������ ��ũ�� ����
    start_color();
    init_pair(2, COLOR_WHITE, COLOR_BLUE);
    bkgd(COLOR_PAIR(2));
    refresh();
}

void Screen::loadRecord(bool iscleared, time_t cleartime) {
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    if (!iscleared) { // �޴�ȭ�鿡�� ���ڵ� ����
        setRec();
        delwin(menu);
        resetScreen();
        record = newwin(33, 50, 6, 25); //���ڵ�â
        mvwprintw(record, 2, 18, "Top 10 records");
        mvwprintw(record, 4, 10, "Time");
        mvwprintw(record, 4, 34, "Date");
        wbkgd(record, COLOR_PAIR(1));
        for (int i = 0; i < rec.size(); i++) {
            if (rec[i][1] == INT_MAX) { 
                if (rec.size() == 1) {
                    mvwprintw(record, 17, 16, "No record set yet.."); // ���ڵ� ������
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
        attroff(COLOR_PAIR(1));     //colo_pair �������.
        wrefresh(record);
    }
    else {
        resetScreen();
        record = newwin(33, 50, 6, 25); //���ڵ�â
        mvwprintw(record, 3, 5, "Congratulations!!");
        mvwprintw(record, 3, 25, "Your record:");
        mvwprintw(record, 5, 18, "Top 10 records");
        mvwprintw(record, 7, 10, "Time");
        mvwprintw(record, 7, 34, "Date");
        long int min = cleartime / 60;
        long int sec = cleartime % 60;
        string t = to_string(min) + "m " + to_string(sec) + "s"; // �̹� �� Ŭ���� �ð�
        vector<char> gametime(t.begin(), t.end());
        gametime.push_back('\0');
        mvwprintw(record, 3, 38, &gametime[0]);
        time_t gamedate = time(NULL);
        insertRec(gamedate, cleartime);
        wbkgd(record, COLOR_PAIR(1));
        int n = rec.size() > 10 ? 10 : rec.size();
        for (int i = 0; i < n; i++) { // ��� ǥ��
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
        attroff(COLOR_PAIR(1));     //colo_pair �������.
        wrefresh(record);
        saveRec(); // ���� ������� ���� ��� ����
        getch();
    }
}

void Screen::gameoverScreen() {
    resetScreen();
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    gameover = newwin(10, 40, 15, 30); //���ӿ��� ȭ��
    // stage ������ ����
    wbkgd(gameover, COLOR_PAIR(1));
    mvwprintw(gameover, 2,14, "Game Over..");
    mvwprintw(gameover, 8, 2, "Press any key to return to main menu");
    wborder(gameover, '|', '|', '-', '-', '+', '+', '+', '+');
    attroff(COLOR_PAIR(1));     //colo_pair �������.
    wrefresh(gameover);
    getch();
}