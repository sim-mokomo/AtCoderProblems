#include <iostream>
#include <vector>

int main(){
    int changeNum;
    std::cin >> changeNum;

    std::vector<int> cards =  {1,2,3,4,5,6};
    // note: 30でカードの並び順が循環する、素直に計算すると処理に時間がかかる為計算を省略する。
    changeNum %= 30;
    for(int i = 0; i < changeNum; i++){
        const int changeIndex = (i % 5);
        const int temp = cards[changeIndex];
        cards[changeIndex] = cards[changeIndex + 1];
        cards[changeIndex + 1] = temp;
    }

    for (const int card: cards) {
        std::cout << card;
    }

    printf("\n");

    return 0;
}