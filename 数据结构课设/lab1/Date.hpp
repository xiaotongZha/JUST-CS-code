#ifndef DATE
#define DATE

#include <iostream>
#include <iomanip>

class Date {
private:
    int year;
    int month;
    int day;
    int hour;
    int minute;
    int second;

public:
    // 构造函数
    Date():year(0), month(0), day(0), hour(0), minute(0), second(0) {}
    
    Date(int yy, int mm, int dd, int hh, int min, int ss)
        : year(yy), month(mm), day(dd), hour(hh), minute(min), second(ss) {}

    // 通过字符串初始化
    Date(const std::string &dateStr) {
        sscanf(dateStr.c_str(), "%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);
    }

    // 格式化输出日期
    void showDate() const {
        std::cout << std::setfill('0') << std::setw(4) << year << "-"
                  << std::setw(2) << month << "-"
                  << std::setw(2) << day << " "
                  << std::setw(2) << hour << ":"
                  << std::setw(2) << minute << ":"
                  << std::setw(2) << second << std::endl;
    }

    // 重载比较运算符
    bool operator<(const Date &other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        if (day != other.day) return day < other.day;
        if (hour != other.hour) return hour < other.hour;
        if (minute != other.minute) return minute < other.minute;
        return second < other.second;
    }

    bool operator>(const Date &other) const {
        return other < *this;
    }

    bool operator<=(const Date &other) const {
        return !(other < *this);
    }

    bool operator>=(const Date &other) const {
        return !(*this < other);
    }

    bool operator==(const Date &other) const {
        return year == other.year && month == other.month && day == other.day &&
               hour == other.hour && minute == other.minute && second == other.second;
    }

    bool operator!=(const Date &other) const {
        return !(*this == other);
    }

    friend std::ostream& operator<<(std::ostream &os, const Date &date);
};
std::ostream& operator<<(std::ostream &os, const Date &date) {
    os << std::setfill('0') << std::setw(4) << date.year << "-"
       << std::setw(2) << date.month << "-"
       << std::setw(2) << date.day << " "
       << std::setw(2) << date.hour << ":"
       << std::setw(2) << date.minute << ":"
       << std::setw(2) << date.second;

    return os;
}

#endif