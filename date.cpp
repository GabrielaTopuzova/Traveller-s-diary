#include <iostream>
#include "date.h"
using namespace std;

bool validDate(size_t day, size_t month, size_t year) {

}
/*
size_t getDay() const;
    size_t getMonth() const;
    size_t getYear() const;
    void setDay(size_t);
    void setMonth(size_t);
    void setYear(size_t);

    Date(size_t, size_t, size_t);
    void print() const;

    Date& operator=(const Date&);
    bool operator<=(const Date&) const;
    bool operator<(const Date&) const;

    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, const Date&);