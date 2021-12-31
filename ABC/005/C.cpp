#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int saleLimitSeconds;
    std::cin >> saleLimitSeconds;

    int makeTakoyakiNum;
    std::cin >> makeTakoyakiNum;

    std::vector<int> makeTakoyakiSecondsList;
    for (int i = 0; i < makeTakoyakiNum; ++i) {
        int makeTakoyakiSeconds;
        std::cin >> makeTakoyakiSeconds;
        makeTakoyakiSecondsList.push_back(makeTakoyakiSeconds);
    }

    int comeCustomerNum;
    std::cin >> comeCustomerNum;

    std::vector<int> comeCustomerSecondsList;
    for (int i = 0; i < comeCustomerNum; ++i) {
        int comeCustomerSeconds;
        std::cin >> comeCustomerSeconds;
        comeCustomerSecondsList.push_back(comeCustomerSeconds);
    }

    // note: お客さんの数が多ければ全員にたこ焼きをふるまいことはできない
    if(comeCustomerNum > makeTakoyakiNum){
        std::cout << "no" << std::endl;
        return 0;
    }

    std::sort(
            comeCustomerSecondsList.begin(),
            comeCustomerSecondsList.end(),
            std::greater<int>{}
            );

    // note: 最短経過秒数のたこ焼き販売タイミングを計算
    // note: 販売制限時間を超えていればそれは売れない
    for (int comeCustomerSeconds : comeCustomerSecondsList) {
        int minSaleLimit = INT32_MAX;
        int minSaleIndex = 0;
        for (int i = 0; i < makeTakoyakiSecondsList.size(); i++) {
            const int makeTakoyakiSecond = makeTakoyakiSecondsList[i];
            const int saleLimit = comeCustomerSeconds - makeTakoyakiSecond;
            if(saleLimit < 0){
                continue;
            }

            if(saleLimit < minSaleLimit){
                minSaleLimit = saleLimit;
                minSaleIndex = i;
            }
        }
        if(minSaleLimit > saleLimitSeconds){
            std::cout << "no" << std::endl;
            return 0;
        }
        makeTakoyakiSecondsList.erase(makeTakoyakiSecondsList.begin() + minSaleIndex);
    }

    std::cout << "yes" << std::endl;
    return 0;
}