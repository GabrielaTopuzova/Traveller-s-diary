#ifndef __PHOTO
#define __PHOTO
#include <iostream>
using namespace std;

class Photo {
    char* name;
    bool validPhoto(const char*) const;
public:
    const char* getName() const;
    void setName(const char*);

    Photo();
    Photo(const char*);
    Photo(const Photo&);
    ~Photo();
    
    Photo& operator=(const Photo&);

    void readFromFile(ifstream&);
    void saveToFile(ofstream&) const;

    friend istream& operator>>(istream&, Photo&);
    friend ostream& operator<<(ostream&, const Photo&);
};
#endif