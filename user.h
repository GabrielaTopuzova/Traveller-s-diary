#ifndef __USER
#define __USER
#include "travel.h"

class User {
    char* username;
    char* password;
    char* email;
    Travel** journeys;
    size_t journeyCount;
public:
    char* getUsername() const;
    char* getPassword() const;
    char* getEmail() const;
    Travel** getJourneys() const;
    size_t getJourneyCount() const;
    void setUsername(char*);
    void setPassword(char*);
    void setEmail(char*);

    User(char*, char*, char*);
    User(const User&);
    User& operator=(const User&);
    ~User();

    void copyFrom(const User&);
    void free();

    friend fstream& openFile(fstream&, const User&);
    friend fstream& closeFile(fstream&, const User&);
    friend ofstream& saveFile(ofstream&, const User&);

    void printUser();
};
#endif