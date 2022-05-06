#ifndef __USER
#define __USER
#include "travel.h"

class User {
    char* username;
    char* password;
    char* email;
    Travel** journeys;
    size_t journeyCount;
    
    void copyFrom(const User&);
    void free();
public:
    const char* getUsername() const;
    const char* getPassword() const;
    const char* getEmail() const;
    Travel** getJourneys() const;
    const size_t getJourneyCount() const;
    void setUsername(const char*);
    void setPassword(const char*);
    void setEmail(const char*);

    User();
    User(const char*, const char*, const char*);
    User(const User&);
    User& operator=(const User&);
    ~User();

    void addTravel(const Travel&);

    void readFromFile(ifstream&);
    void saveToFile(ofstream&) const;

    void readJourneysFromFile(ifstream&);
    void saveJourneysToFile(ofstream&) const;

    void printUser() const;
};
#endif