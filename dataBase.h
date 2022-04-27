#ifndef __DATABASE
#define __DATABASE
#include "user.h"

class DataBase {
    User** users;
    size_t userCount;
public:
    DataBase(User**);
    DataBase(const DataBase&);
    DataBase& operator=(const DataBase&);
    ~DataBase();

    void copyFrom(const DataBase&);
    void free();

    friend fstream& registerNewUser(fstream&, User&);
    friend fstream& editUser(fstream&, User&);

    void printDataBase();
    void printDataBaseByDestination(char*);
};
#endif