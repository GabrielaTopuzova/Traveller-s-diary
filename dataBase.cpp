#include "dataBase.h"
#include "user.h"
#include <cstring>

void DataBase::copyFrom(const DataBase& otherDatabase) {
    User** copyData = new User*[userCount];
    userCount = otherDatabase.userCount;
    for(size_t i = 0; i < userCount; i++)
        copyData[i] = new User(*otherDatabase.users[i]);
    users = copyData;
}
void DataBase::free() {
    for(size_t i = 0; i < userCount; i++)
        delete[] users[i];
    delete[] users;
}

DataBase::DataBase(User** userList) {
    User** buffer = new User*[1024];
    size_t count = 0;
    for(size_t i = 0; i < userCount; i++)
        if(userList[i] != nullptr)
            count++;
    userCount = count;
    User** copyData = new User*[userCount];
    users = userList;
}
DataBase::DataBase(const DataBase& otherDataBase) {
    copyFrom(otherDataBase);
}
DataBase& DataBase::operator=(const DataBase& otherDataBase) {
    if(this != &otherDataBase)
    {
    free();
    copyFrom(otherDataBase);
    }
    return *this;
}
DataBase::~DataBase() {
    free();
}

void DataBase::printDataBase() {
    for(size_t i = 0; i < userCount; i++)
        users[i]->printUser();
}

void DataBase::printDataBaseByDestination(char* inputDestination) {
    for(size_t i = 0; i < userCount; i++)
        for(size_t j = 0; j < users[i]->getJourneyCount(); i++)
            if(strcmp(users[i]->getJourneys()[j]->getDestination(), inputDestination) == 0)
                users[i]->printUser();
}