#include <iostream>
#include <vector>
#include <algorithm>

int main(){
    int movieNum;
    int watchableMovieNum;
    std::cin >> movieNum >> watchableMovieNum;

    std::vector<int> movieUserRateList;
    for(int i = 0; i < movieNum; i++){
        int movieUserRate;
        std::cin >> movieUserRate;
        movieUserRateList.push_back(movieUserRate);
    }

    std::sort(movieUserRateList.begin(),
            movieUserRateList.end(),
            std::greater<int>{});

    std::vector<int> watchMovieUserRateList;
    std::copy(movieUserRateList.begin(),
              movieUserRateList.begin() + watchableMovieNum,
              std::back_inserter(watchMovieUserRateList));

    std::sort(watchMovieUserRateList.begin(),
              watchMovieUserRateList.end(),
              std::less<int>{});

    double currentUserRate = 0;
    for(int movieUserRate : watchMovieUserRateList){
        currentUserRate = (currentUserRate + movieUserRate) * 0.5;
    }

    printf("%f\n", currentUserRate);
    return 0;
}