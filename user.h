#ifndef __USER
#define __USER
#include "date.h"
#include "photo.h"

class User  {
    char* name;
    char* destination;
    Date timePeriod[2];
    size_t grade;
    char* comment;
    Photo* album;
    size_t photoCount;

    bool isCreated(const User&) const;
public:
    User(char*, char*, Date [2], size_t, char*, Photo*, size_t);
    User(const User&);
    User& operator=(const User&);
    ~User();

    void copyFrom(const User&);
    void free();

    User& editUser();
    void saveUser() const;
    void printUser() const;
    
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
    void setAlbum(Photo*);

};
#endif