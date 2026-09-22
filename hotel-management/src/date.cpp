#include "date.h"
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cmath>

Date::Date() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    day = ltm->tm_mday;
    month = 1 + ltm->tm_mon;
    year = 1900 + ltm->tm_year;
}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

std::string Date::toString() const {
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(2) << day << "/"
       << std::setw(2) << month << "/" << year;
    return ss.str();
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}

bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

int Date::getDaysDifference(const Date& other) const {
    // Simplified calculation - in real implementation, use proper date library
    return abs((year - other.year) * 365 + (month - other.month) * 30 + (day - other.day));
}