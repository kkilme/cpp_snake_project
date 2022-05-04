
class HomeMenu {
public:
    //home menu 출력 및 
    void loadHome();

private:
    // 나중에 record 추가되면 리스트, 리스트길이 변경
    char menuList[6][30] = {"SELECT STAGE","NUM_PAD '1' : 1STAGE","NUM_PAD '2' : 2STAGE","NUM_PAD '3' : 3STAGE","NUM_PAD '4' : RECORDS","NUM_PAD '5' : EXIT" };
    int menuLength = 6;
};
