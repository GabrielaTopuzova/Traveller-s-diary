#ifndef __PHOTO
#define __PHOTO
#include <iostream>
using namespace std;

class Photo {
    char* name;
    bool validPhoto(const char*) const;
public:
    char* getName() const;
    void setName(char*);

    Photo();
    Photo(char*);
    ~Photo();
    
    Photo& operator=(const Photo&);

    friend istream& operator>>(istream&, Photo&);
    friend ostream& operator<<(ostream&, const Photo&);
};
#endif