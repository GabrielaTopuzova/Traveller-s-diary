#ifndef __TRAVEL
#define __TRAVEL
#include <fstream>
#include "date.h"
#include "photo.h"

class Travel  {
    String destination;
    Date timePeriod[2];
    size_t grade;
    String comment;
    Photo* album;
    size_t photoCount;

    bool validTimePeriod(const Date [2]) const;

    void copyFrom(const Travel&);
    void free();
public:
    const String& getDestination() const;
    const Date* getTimePeriod() const;
    const size_t getGrade() const;
    const String& getComment() const;
    const Photo* getAlbum() const;
    const size_t getPhotoCount() const;
    void setDestination(const String&);
    void setTimePeriod(const Date [2]);
    void setGrade(const size_t);
    void setComment(const String&);
    void setAlbum(const Photo*, const size_t);

    Travel();
    Travel(const String&, const Date [2], const size_t, const String&, const Photo*, const size_t);
    Travel(const Travel&);
    Travel& operator=(const Travel&);
    ~Travel();

    void readFromFile(ifstream&);
    void saveToFile(ofstream&) const;

    void inputTravel();
    void printTravel() const;
};
#endif