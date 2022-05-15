#ifndef __PHOTO
#define __PHOTO
#include <iostream>
#include "string.h"
using namespace std;

class Photo {
    String name;
    
    bool validPhoto(const String&) const;
public:
    const String& getName() const;
    void setName(const String&);

    Photo() = default;
    Photo(const String&);
    
    void readFromFile(ifstream&);
    void saveToFile(ofstream&) const;

    friend istream& operator>>(istream&, Photo&);
    friend ostream& operator<<(ostream&, const Photo&);
};
#endif