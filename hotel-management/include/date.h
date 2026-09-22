#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day, month, year;

public:
    Date();
    Date(int d, int m, int y);

    std::string toString() const;
    bool operator<(const Date& other) const;
    bool operator==(const Date& other) const;
    int getDaysDifference(const Date& other) const;
};

#endif // DATE_H