#include <iostream>
#include <vector>

// note : 下記記事を参考にして記述している
// https://qiita.com/drken/items/56a6b68edef8fc605821#4-%E4%BA%8C%E6%AC%A1%E5%85%83%E7%B4%AF%E7%A9%8D%E5%92%8C

int main(){
    int bakeSize;
    std::cin >> bakeSize;

    std::vector<std::vector<int>> deliciousValueList(
            bakeSize,
            std::vector<int>(bakeSize));
    for (int i = 0; i < bakeSize; ++i) {
        for (int j = 0; j < bakeSize; ++j) {
            std::cin >> deliciousValueList[i][j];
        }
    }

    // 累積和
    std::vector<std::vector<int>> accumulateDeliciousValueList(
            bakeSize + 1,
            std::vector<int>(bakeSize + 1, 0));
    for (int i = 0; i < bakeSize; ++i) {
        for (int j = 0; j < bakeSize; ++j) {
            accumulateDeliciousValueList[i + 1][j + 1] =
                    accumulateDeliciousValueList[i][j + 1]
                    + accumulateDeliciousValueList[i + 1][j]
                    - accumulateDeliciousValueList[i][j]
                    + deliciousValueList[i][j];
        }
    }

    // 全長方形区域の面積を計算
    std::vector<int> areaDeliciousList(bakeSize * bakeSize + 1, 0);
    for (int x1 = 0; x1 < bakeSize; ++x1) {
        for (int x2 = x1 + 1; x2 <= bakeSize; ++x2) {
            for (int y1 = 0; y1 < bakeSize; ++y1) {
                for (int y2 = y1 + 1; y2 <= bakeSize; ++y2) {
                    const int area = (x2 - x1) * (y2 - y1);
                    const int sum =
                            accumulateDeliciousValueList[x2][y2]
                            - accumulateDeliciousValueList[x1][y2]
                            - accumulateDeliciousValueList[x2][y1]
                            + accumulateDeliciousValueList[x1][y1];
                    areaDeliciousList[area] = std::max(areaDeliciousList[area], sum);
                }
            }
        }
    }

    // 指定の区域、区域以下の総和が上回っていればそちらを利用
    for (int i = 0; i < bakeSize * bakeSize; ++i) {
        areaDeliciousList[i + 1] = std::max(areaDeliciousList[i + 1], areaDeliciousList[i]);
    }

    // 指定された領域の総和を表示させる
    int workerNum;
    std::cin >> workerNum;
    for (int i = 0; i < workerNum; ++i) {
        int makeTakoyakiNum;
        std::cin >> makeTakoyakiNum;
        std::cout << areaDeliciousList[makeTakoyakiNum] << std::endl;
    }

    return 0;
}