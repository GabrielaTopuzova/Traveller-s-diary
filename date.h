#ifndef __DATE
#define __DATE
#include <iostream>
#include <fstream>
using namespace std;

class Date {
    size_t day;
    size_t month;
    size_t year;
    
    bool validDate(const size_t, const size_t, const size_t) const;
public:
    const size_t getDay() const;
    const size_t getMonth() const;
    const size_t getYear() const;
    void setDay(const size_t);
    void setMonth(const size_t);
    void setYear(const size_t);

    Date();
    Date(const size_t, const size_t, const size_t);

    bool operator<=(const Date&) const;
    bool operator<(const Date&) const;

    void readFromFile(ifstream&);
    void writeInFile(ofstream&) const;

    friend istream& operator>>(istream&, Date&);
    friend ostream& operator<<(ostream&, const Date&);
};
#endif