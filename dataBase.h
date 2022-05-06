#ifndef __DATABASE
#define __DATABASE
#include "user.h"

class DataBase {
    User* users;
    size_t userCount;

    bool userCreated(const char*) const;
    const char* fileName(const char*) const;

    void copyFrom(const DataBase&);
    void free();
public:
    DataBase();
    DataBase(const User*, const size_t);
    DataBase(const DataBase&);
    DataBase& operator=(const DataBase&);
    ~DataBase();

    void loadDataBase(const char*);
    void saveDataBase(const char*) const;

    const char* registerUser();
    const char* logIn();
    void addTravelToUser(const char*, const Travel&);

    void printDataBase() const;
    void printDataBaseByDestination(const char*) const;

    void startProgram();
};
#endif