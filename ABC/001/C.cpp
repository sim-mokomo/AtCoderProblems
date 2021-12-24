#include <iostream>
#include <vector>
#include <algorithm>

class WindDirection
{
public:
    static std::string calcDirection(int degree){
        // note: 桁を合わせる
        degree *= 10;
        const std::vector<std::string> directionStringTable = {
                "N",
                "NNE",
                "NE",
                "ENE",
                "E",
                "ESE",
                "SE",
                "SSE",
                "S",
                "SSW",
                "SW",
                "WSW",
                "W",
                "WNW",
                "NW",
                "NNW"
        };
        int windThreshold = 1125;
        // note: 整数のみを扱い、計算誤差をなくす
        const int windThresholdDiffPerDirection = 360 * 100 / 16;
        for(const auto& it : directionStringTable) {
            if(degree < windThreshold){
                return it;
            }

            windThreshold += windThresholdDiffPerDirection;
        }
        return directionStringTable[0];
    }
};

class WindPower
{
public:
    static int calcPower(int windMeterPerMinutes){
        struct WindPowerRecord{
            int minWindSpeed;
            int maxWindSpeed;
        };

        std::vector<WindPowerRecord> table = {
                {0, 2},
                {3, 15},
                {16, 33},
                {34, 54},
                {55, 79},
                {80, 107},
                {108, 138},
                {139, 171},
                {172, 207},
                {208, 244},
                {245, 284},
                {285, 326},
                {327, INT32_MAX},
        };

        // note: 整数のみを扱い、誤差をなくす
        int windMeterPerSeconds = windMeterPerMinutes * 100 / 60;
        int roundDiff = windMeterPerSeconds % 10 >= 5;
        windMeterPerSeconds = (windMeterPerSeconds / 10) + roundDiff;


        auto it = std::find_if(
                table.cbegin(),
                table.cend(),
                 [windMeterPerSeconds](const WindPowerRecord& x) {
                     return
                             x.minWindSpeed <= windMeterPerSeconds &&
                             windMeterPerSeconds <= x.maxWindSpeed;
                 }
                );

        const int index = std::distance(table.cbegin(), it);
        return index;
    }
};


class WindObservation
{
public:
    static std::tuple<std::string , int> calc(int degree, int windMeterPerMinutes){
        std::string direction = WindDirection::calcDirection(degree);
        int windPower = WindPower::calcPower(windMeterPerMinutes);
        if(windPower == 0){
            return std::make_tuple("C", windPower);
        }
        return std::make_tuple(direction, windPower);
    }
};

int main() {
    int inputDegree;
    int inputWindMeterPerMinutes;
    std::cin >> inputDegree >> inputWindMeterPerMinutes;

    auto ret = WindObservation::calc(
            inputDegree,
            inputWindMeterPerMinutes);
    std::cout
        << std::get<0>(ret)
        << " "
        << std::get<1>(ret)
        << std::endl;
    return 0;
}
