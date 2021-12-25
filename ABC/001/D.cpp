#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::string> split(const std::string & text, std::string separator) {
    auto separator_length = separator.length(); // 区切り文字の長さ
    if (separator_length == 0) {
        return std::vector<std::string>() = {text};
    }

    auto list = std::vector<std::string>();
    auto offset = std::string::size_type(0);
    while (1) {
        auto pos = text.find(separator, offset);
        if (pos == std::string::npos) {
            list.push_back(text.substr(offset));
            break;
        }
        list.push_back(text.substr(offset, pos - offset));
        offset = pos + separator_length;
    }
    return list;
}

class Time {
private:
    int hour;
    int minutes;
public:
    Time()
            : hour(0), minutes(0) {

    }

    Time(int hour, int minutes)
            : hour(0), minutes(0) {
        addHours(hour);
        addMinutes(minutes);
    }

    void addMinutes(int addMinutes) {
        if (minutes + addMinutes >= 60) {
            addHours((minutes + addMinutes) / 60);
            minutes = (minutes + addMinutes) % 60;
            return;
        }

        minutes += addMinutes;
    }

    void addHours(int addHour) {
        if (hour + addHour > 24) {
            hour = (hour + addHour) % 24;
            return;
        }

        hour += addHour;
    }

    int getHour() const { return hour; }

    int getMinutes() const { return minutes; }

};

class TimeFormatter {
public:
    // note: フォーマット: 12時30分 -> 1230
    static int toOneLineValue(Time time) {
        return time.getHour() * 100 + time.getMinutes();
    }
};

class RainReport {
private:
    Time start;
    Time end;
public:
    // note: RainReportStrの format は <start>-<end>
    RainReport(const std::string &RainReportStr) {
        auto timeList = split(RainReportStr, "-");

        const int startInt = std::stoi(timeList[0]);
        start = Time(startInt / 100, startInt % 100);
        start.addMinutes(-start.getMinutes() % 5);

        const int endInt = std::stoi(timeList[1]);
        end = Time(endInt / 100, endInt % 100);
        const int tailEndNum = end.getMinutes() % 10;
        if (tailEndNum != 0) {
            if (tailEndNum <= 5) {
                end.addMinutes(5 - tailEndNum);
            } else {
                end.addMinutes(10 - tailEndNum);
            }
        }
    }

    Time getStartTime() const { return start; }

    Time getEndTime() const { return end; }
};

class RainReportFormatter {
public:
    static std::string reportFormat(Time start, Time end) {
        return timeFormat(start) + "-" + timeFormat(end);
    }

    static std::string timeFormat(Time time) {
        char buffer[128];
        snprintf(buffer,
                 sizeof(buffer),
                 "%02d%02d",
                 time.getHour(),
                 time.getMinutes());
        return buffer;
    }
};

int main(){
    int reportNum;
    std::cin >> reportNum;
    std::vector<RainReport> reports;
    for (int i = 0; i < reportNum; ++i) {
        std::string rainReportStr;
        std::cin >> rainReportStr;
        RainReport report(rainReportStr);
        reports.push_back(report);
    }

    // note: 時刻を記録
    const int timeTableLength = 2500;
    int timeTable[timeTableLength] = {0};

    for (const auto& report : reports) {
        const int start = TimeFormatter::toOneLineValue(report.getStartTime());
        const int end = TimeFormatter::toOneLineValue(report.getEndTime());
        for (int i = start; i <= end; ++i) {
            timeTable[i] = 1;
        }
    }

    bool isInspection = false;
    int startTime = 0;
    int endTime = 0;
    std::vector<RainReport> resultReports;
    for(int i = 0; i < timeTableLength; i++){
        if(!isInspection && timeTable[i] == 1){
            startTime = i;
            isInspection = true;
        }
        else if(isInspection && timeTable[i] == 0){
            endTime = i - 1;
            isInspection = false;

            Time start(startTime/ 100, startTime % 100);
            Time end(endTime /100, endTime % 100);
            RainReport report(RainReportFormatter::reportFormat(start, end));
            resultReports.push_back(report);

            startTime = 0;
            endTime = 0;
        }
    }

    for(const auto& report : resultReports){
        std::cout << RainReportFormatter::reportFormat(
                report.getStartTime(),
                report.getEndTime()) << std::endl;
    }

    return 0;
}