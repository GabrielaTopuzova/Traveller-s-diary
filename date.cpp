#include <iostream>
#include <iomanip>
#include "date.h"
using namespace std;

size_t lastDayOfMonth(size_t month, size_t year) {
    bool isLeap = ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0);
    if(month == 4 || month == 6 || month == 9 || month == 11)
        return 30;
    if(month == 2 && isLeap)
        return 29;
    if(month == 2 && !isLeap)
        return 28;
    return 31;
}
bool Date::validDate(const size_t day, const size_t month, const size_t year) const {
    if(year > 9999 || year < 0) 
        return false;

    if(month < 1 || month > 12)
        return false;

    size_t lastDay = lastDayOfMonth(month, year);
    if(day > lastDay || day < 1)
        return false;

    return true;
}

const size_t Date::getDay() const {
    return day;
}
const size_t Date::getMonth() const {
    return month;
}
const size_t Date::getYear() const {
    return year;
}
void Date::setDay(const size_t day) {
    if(validDate(day, month, year))
        this->day = day;
}
void Date::setMonth(const size_t month) {
    if(validDate(day, month, year))
        this->month = month;
}
void Date::setYear(const size_t year) {
    if(validDate(day, month, year))
        this->year = year;
}

Date::Date() {
    day = 1;
    month = 1;
    year = 1;
}
Date::Date(const size_t day, const size_t month, const size_t year) {
    if(!validDate(day, month, year))
        throw "Invalid date!";
    this->day = day;
    this->month = month;
    this->year = year;
}

bool Date::operator<=(const Date& otherDate) const {
    return *this < otherDate || (otherDate.year == year && otherDate.month == month && otherDate.day == day);
}
bool Date::operator<(const Date& otherDate) const {
    return otherDate.year > year || (otherDate.year == year && otherDate.month > month) || 
        (otherDate.year == year && otherDate.month == month && otherDate.day > day);
}

void Date::readFromFile(ifstream& file) {
    file.read((char*) this, sizeof(Date));
}
void Date::writeInFile(ofstream& file) const {
    file.write((const char*) this, sizeof(Date));
}

istream& operator>>(istream& stream, Date& date) {
    size_t inputDay, inputMonth, inputYear;
    stream >> inputDay >> inputMonth >> inputYear;

    if(!(date.validDate(inputDay, inputMonth, inputYear)))
        throw "Invalid date!";
        
    date.day = inputDay;
    date.month = inputMonth;
    date.year = inputYear;
    return stream;
}
ostream& operator<<(ostream& stream, const Date& date) {
    stream << setw(2) << setfill('0') << date.day << ".";
    stream << setw(2) << setfill('0') << date.month << ".";
    stream << setw(4) << setfill('0') << date.year;
    return stream;
}