
class HomeMenu {
public:
    //home menu ��� �� 
    void loadHome();

private:
    // ���߿� record �߰��Ǹ� ����Ʈ, ����Ʈ���� ����
    char menuList[4][30] = {"MENU","NUM_PAD '1' : START GAME","NUM_PAD '2' : RECORDS","NUM_PAD '3' : EXIT" };
    int menuLength = 4;
};
