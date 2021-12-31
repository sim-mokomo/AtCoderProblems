#include <iostream>

int main() {
    int humanNum;
    std::cin >> humanNum;

    int footNum;
    std::cin >> footNum;

    // x + y + z = 3
    // 2x + 3y + 4z = 9

    // zはループで探索するようにする
    // x, yを解く

    for (int child = 0; child <= humanNum; ++child) {
        const int adult = -footNum + (3 * humanNum) + child;
        const int silver = footNum - (2 * humanNum) - (2 * child);
        if(adult >= 0 && silver >= 0){
            std::cout << adult << " " << silver << " " << child << std::endl;
            return 0;
        }
    }

    std::cout << -1 << " " << -1 << " " << -1 << std::endl;
    return 0;
}