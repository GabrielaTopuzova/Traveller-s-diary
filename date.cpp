#include <iostream>
#include "date.h"
using namespace std;

bool validDate(size_t day, size_t month, size_t year) {
    if(year > 9999 || year < 0)
        return false;
    if(month < 1 || month > 12)
        return false;
    if(((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0))
        if(month == 2)
            if(day > 29)
            return false;
    if (month == 4 || month == 6 ||
        month == 9 || month == 11)
        if(day > 30)
        return false;
    if(day > 31 || day < 1)
        return false;

    return true;
}

size_t Date::getDay() const {
    return day;
}
size_t Date::getMonth() const {
    return month;
}
size_t Date::getYear() const {
    return year;
}
void Date::setDay(size_t day) {
    this->day = day;
}
void Date::setMonth(size_t month) {
    this->month = month;
}
void Date::setYear(size_t year) {
    this->year = year;
}

Date::Date() {
    day = 1;
    month = 1;
    year = 0;
}
Date::Date(size_t day, size_t month, size_t year) {
    setDay(day);
    setMonth(month);
    setYear(year);
}
Date::Date(const Date& otherDate) {
    day = otherDate.day;
    month = otherDate.month;
    year = otherDate.year;
}

Date& Date::operator=(const Date& otherDate)
{
    if(year == otherDate.year && month == otherDate.month && day == otherDate.day)
        return *this;
    setDay(otherDate.day);
    setMonth(otherDate.month);
    setYear(otherDate.year);
    return *this;
}
bool Date::operator<=(const Date& otherDate) const {
    return *this < otherDate || (otherDate.year == year && otherDate.month == month && otherDate.day == day);
}
bool Date::operator<(const Date& otherDate) const {
    return otherDate.year > year || (otherDate.year == year && otherDate.month > month) || 
        (otherDate.year == year && otherDate.month == month && otherDate.day > day);
}

void Date::consolePrint() const {
    cout << day << "/" << month << "/" << year;
}

istream& operator>>(istream& stream, Date& date) {
    size_t inputDay, inputMonth, inputYear;
    stream >> inputDay >> inputMonth >> inputYear;

    if(!(validDate(inputDay, inputMonth, inputYear)))
        throw "Not valid Date";
        
    date.setDay(inputDay);
    date.setMonth(inputMonth);
    date.setYear(inputYear);
    return stream;
}
ostream& operator<<(ostream& stream, const Date& date) {
    stream << date.day << date.month << date.year;
}

//test