
class HomeMenu {
public:
    //home menu 출력 및 
    void loadHome();

private:
    // 나중에 record 추가되면 리스트, 리스트길이 변경
    char menuList[4][30] = {"MENU","NUM_PAD '1' : START GAME","NUM_PAD '2' : RECORDS","NUM_PAD '3' : EXIT" };
    int menuLength = 4;
};
