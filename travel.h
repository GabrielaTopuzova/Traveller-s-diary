#ifndef __TRAVEL
#define __TRAVEL
#include <fstream>
#include "date.h"
#include "photo.h"

class Travel  {
    char* destination;
    Date timePeriod[2];
    size_t grade;
    char* comment;
    Photo* album;
    size_t photoCount;

    bool validTimePeriod(const Date [2]) const;

    void copyFrom(const Travel&);
    void free();
public:
    const char* getDestination() const;
    const Date* getTimePeriod() const;
    const size_t getGrade() const;
    const char* getComment() const;
    const Photo* getAlbum() const;
    const size_t getPhotoCount() const;
    void setDestination(const char*);
    void setTimePeriod(const Date [2]);
    void setGrade(const size_t);
    void setComment(const char*);
    void setAlbum(const Photo*, const size_t);

    Travel();
    Travel(const char*, const Date [2], const size_t, const char*, const Photo*, const size_t);
    Travel(const Travel&);
    Travel& operator=(const Travel&);
    ~Travel();

    void readFromFile(ifstream&);
    void saveToFile(ofstream&) const;

    void inputTravel();
    void printTravel() const;
};
#endif