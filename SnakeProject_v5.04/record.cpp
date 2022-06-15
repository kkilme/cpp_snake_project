#pragma once
#include <vector>
#include <time.h>
#include <fstream>
#include <iostream>
#include <algorithm>
using namespace std;
vector<vector<time_t>> rec;
bool cmp(vector<time_t>& v1, vector<time_t>& v2) { // Ŭ����ð��� �������� ���� ���� �ʿ��� �� �Լ�
    if (v1[1] == v2[1])
        return v1[0] < v2[0];
    else return v1[1] < v2[1];
}

void setRec() { // ��� �ҷ��ͼ� ���Ϳ� ����
    if (rec.size() != 0) { return; }
    ifstream ifs;
    ifs.open("record.txt");
    if (!ifs)
    {
        ofstream ofs;
        ofs.open("record.txt"); //���Ͼ����� ����
        ofs << '1' << endl;
        ofs << '0' << ' ' << INT_MAX << endl;
        ofs.close();
        ifs.open("record.txt");
    }
    int n; // ��� ����
    ifs >> n;
    for (int i = 0; i < n; i++) {
        time_t date, record;
        ifs >> date >> record;
        rec.push_back(vector<time_t>());
        rec[i].push_back(date);
        rec[i].push_back(record);
    }
    sort(rec.begin(), rec.end(), cmp); // Ŭ����ð��� �������� ����
    ifs.close();
}

void insertRec(time_t date, time_t gametime) { // Ŭ����� Ŭ���� ����� �߰�
    rec.push_back(vector<time_t>());
    rec[rec.size() - 1].push_back(date);
    rec[rec.size() - 1].push_back(gametime);
    sort(rec.begin(), rec.end(), cmp);
}

void saveRec() { // ���Ͽ� ����� ����
    ofstream ofs;
    ofs.open("record.txt");
    int n = rec.size() > 10 ? 10 : rec.size();
    ofs << n << endl;
    for (int j = 0; j < n; j++) {
        ofs << rec[j][0] << ' ' << rec[j][1] << endl;
    }
    ofs.close();
}