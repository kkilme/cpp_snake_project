#pragma once
#include <vector>
#include <time.h>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
vector<vector<time_t>> rec;
bool cmp(vector<time_t>& v1, vector<time_t>& v2) { // 클리어시간순 오름차순 정렬 위해 필요한 비교 함수
    if (v1[1] == v2[1])
        return v1[0] < v2[0];
    else return v1[1] < v2[1];
}

void setRec() { // 기록 불러와서 벡터에 저장
    if (rec.size() != 0) { return; }
    ifstream ifs;
    ifs.open("record.txt");
    if (!ifs)
    {
        ofstream ofs;
        ofs.open("record.txt"); //파일없을시 만듬
        ofs << '1' << endl;
        ofs << '0' << ' ' << INT_MAX << endl;
        ofs.close();
        ifs.open("record.txt");
    }
    int n; // 기록 개수
    ifs >> n;
    for (int i = 0; i < n; i++) {
        time_t date, record;
        ifs >> date >> record;
        rec.push_back(vector<time_t>());
        rec[i].push_back(date);
        rec[i].push_back(record);
    }
    sort(rec.begin(), rec.end(), cmp); // 클리어시간순 오름차순 정렬
    ifs.close();
}

void insertRec(time_t date, time_t gametime) { // 클리어시 클리어 기록을 추가
    rec.push_back(vector<time_t>());
    rec[rec.size() - 1].push_back(date);
    rec[rec.size() - 1].push_back(gametime);
    sort(rec.begin(), rec.end(), cmp);
}

void saveRec() { // 파일에 기록을 저장
    ofstream ofs;
    ofs.open("record.txt");
    int n = rec.size() > 10 ? 10 : rec.size();
    ofs << n << endl;
    for (int j = 0; j < n; j++) {
        ofs << rec[j][0] << ' ' << rec[j][1] << endl;
    }
    ofs.close();
}