#ifndef __DATE
#define __DATE
#include <iostream>
#include <fstream>
using namespace std;

class Date {
    size_t day;
    size_t month;
    size_t year;
    bool validDate(size_t, size_t, size_t);
public:
    size_t getDay() const;
    size_t getMonth() const;
    size_t getYear() const;
    void setDay(size_t);
    void setMonth(size_t);
    void setYear(size_t);

    Date();
    Date(size_t, size_t, size_t);

    bool operator<=(const Date&) const;
    bool operator<(const Date&) const;

    void readFromFile(ifstream&);
    void writeInFile(ofstream&) const;

    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, const Date&);
};
#endif