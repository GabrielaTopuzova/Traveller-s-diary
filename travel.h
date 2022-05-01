#ifndef __TRAVEL
#define __TRAVEL
#include <fstream>
#include "date.h"
#include "photo.h"

class Travel  {
    char* name;
    char* destination;
    Date timePeriod[2];
    size_t grade;
    char* comment;
    Photo* album;
    size_t photoCount;

    bool validTimePeriod(Date [2]);

    void copyFrom(const Travel&);
    void free();
public:
    char* getName() const;
    char* getDestination() const;
    const Date* getTimePeriod() const;
    size_t getGrade() const;
    char* getComment() const;
    Photo* getAlbum() const;
    size_t getPhotoCount() const;
    void setName(char*);
    void setDestination(char*);
    void setTimePeriod(Date [2]);
    void setGrade(size_t);
    void setComment(char*);
    void setAlbum(Photo*, size_t);

    Travel();
    Travel(char*, char*, Date [2], size_t, char*, Photo*, size_t);
    Travel(const Travel&);
    Travel& operator=(const Travel&);
    ~Travel();

    void inputTravel();
    void printTravel() const;
};
#endif