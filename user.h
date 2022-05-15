#ifndef __USER
#define __USER
#include "travel.h"

class User {
    String username;
    String password;
    String email;
    Travel** journeys;
    size_t journeyCount;
    
    void copyFrom(const User&);
    void free();
public:
    const String& getUsername() const;
    const String& getPassword() const;
    const String& getEmail() const;
    Travel** getJourneys() const;
    const size_t getJourneyCount() const;
    void setUsername(const String&);
    void setPassword(const String&);
    void setEmail(const String&);

    User();
    User(const String&, const String&, const String&);
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