#ifndef __DATABASE
#define __DATABASE
#include "user.h"

class DataBase {
    User* users;
    size_t userCount;

    bool userCreated(const String&) const;
    String fileName(const String&) const;

    void copyFrom(const DataBase&);
    void free();
public:
    DataBase();
    DataBase(const User*, const size_t);
    DataBase(const DataBase&);
    DataBase& operator=(const DataBase&);
    ~DataBase();

    void loadDataBase(const String&);
    void saveDataBase(const String&) const;

    const String& registerUser();
    const String& logIn();
    void addTravelToUser(const String&, const Travel&);

    void printDataBase() const;
    void printDataBaseByDestination(const String&) const;

    void startProgram();
};
#endif