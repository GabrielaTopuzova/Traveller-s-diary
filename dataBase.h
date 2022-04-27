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

    void loadDataBase();
    void saveDataBase();

    void printDataBase();
    void printDataBaseByDestination(char*);
};
#endif