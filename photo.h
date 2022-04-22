#ifndef __PHOTO
#define __PHOTO
#include <iostream>
using namespace std;

class Photo {
    char* name;
    bool validPhoto(char*) const;
public:
    Photo();
    Photo(char*);
    ~Photo();

    char* getName() const;
    void setName(char*);

    Photo& operator=(const Photo&);

    friend istream& operator>>(istream&, Photo&);
    friend ostream& operator<<(ostream&, const Photo&);
};
#endif