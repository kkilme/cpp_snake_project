
class HomeMenu {
public:
    //home menu ��� �� 
    void loadHome();

private:
    // ���߿� record �߰��Ǹ� ����Ʈ, ����Ʈ���� ����
    char menuList[6][30] = {"SELECT STAGE","NUM_PAD '1' : 1STAGE","NUM_PAD '2' : 2STAGE","NUM_PAD '3' : 3STAGE","NUM_PAD '4' : RECORDS","NUM_PAD '5' : EXIT" };
    int menuLength = 6;
};
