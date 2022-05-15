#include <iostream>
#include <cstring>
#include "dataBase.h"
#include "user.h"
using namespace std;

void DataBase::copyFrom(const DataBase &otherDatabase)
{
    userCount = otherDatabase.userCount;
    User *copyData = new User[userCount];
    for (size_t i = 0; i < userCount; i++)
        copyData[i] = otherDatabase.users[i];
    users = copyData;
}
void DataBase::free()
{
    delete[] users;
}
bool DataBase::userCreated(const String &useraname) const
{
    for (size_t i = 0; i < userCount; i++)
        if (strcmp(users[i].getUsername().getStr(), useraname.getStr()) == 0)
            return true;
    return false;
}
String DataBase::fileName(const String &username) const
{
    char *result = new char[username.length() + 4];
    strcpy(result, username.getStr());
    strcat(result, ".db");

    String str(result);
    delete[] result;

    return str;
}

DataBase::DataBase()
{
    users = nullptr;
    userCount = 0;
}
DataBase::DataBase(const User *userList, const size_t userCount)
{
    this->userCount = userCount;
    users = new User[userCount];
    for (size_t i = 0; i < userCount; i++)
        users[i] = userList[i];
}
DataBase::DataBase(const DataBase &otherDataBase)
{
    copyFrom(otherDataBase);
}
DataBase &DataBase::operator=(const DataBase &otherDataBase)
{
    if (this != &otherDataBase)
    {
        free();
        copyFrom(otherDataBase);
    }
    return *this;
}
DataBase::~DataBase()
{
    free();
}

void DataBase::loadDataBase(const String &fileName)
{
    ifstream file(fileName.getStr(), ios::binary);
    if (!file.is_open())
        return;
    free();
    file.read((char *)&userCount, sizeof(size_t));
    users = new User[userCount];
    for (size_t i = 0; i < userCount; i++)
        users[i].readFromFile(file);
    file.close();

    for (size_t i = 0; i < userCount; i++)
    {
        ifstream userFile(this->fileName(users[i].getUsername()).getStr(), ios::binary);
        if (userFile.is_open())
            users[i].readJourneysFromFile(userFile);
        userFile.close();
    }
}
void DataBase::saveDataBase(const String &fileName) const
{
    ofstream file(fileName.getStr(), ios::binary);
    if (!file.is_open())
        throw "Can't open DataBase!";
    file.write((const char *)&userCount, sizeof(size_t));
    for (size_t i = 0; i < userCount; i++)
        users[i].saveToFile(file);
    file.close();

    for (size_t i = 0; i < userCount; i++)
    {
        ofstream userFile(this->fileName(users[i].getUsername()).getStr(), ios::binary);
        if (userFile.is_open())
            users[i].saveJourneysToFile(userFile);
        userFile.close();
    }
}

const String &DataBase::registerUser()
{
    char username[1024];
    cout << "Username: ";
    cin >> username;
    if (userCreated(username))
        throw "Username is taken!";

    char password[1024];
    cout << "Password: ";
    cin >> password;
    char email[1024];
    cout << "Email: ";
    cin >> email;

    User user(username, password, email);

    userCount++;
    User *result = new User[userCount];
    for (size_t i = 0; i < userCount - 1; i++)
        result[i] = users[i];
    result[userCount - 1] = user;

    delete[] users;
    users = result;
    return users[userCount - 1].getUsername();
}
const String &DataBase::logIn()
{
    char username[1024];
    cout << "Username: ";
    cin >> username;
    char password[1024];
    cout << "Password: ";
    cin >> password;

    if (!userCreated(username))
        throw "There is no such user!";

    for (size_t i = 0; i < userCount; i++)
        if (strcmp(users[i].getUsername().getStr(), username) == 0)
        {
            if (strcmp(users[i].getPassword().getStr(), password) != 0)
                throw "Wrong password!";
            else
                return users[i].getUsername();
        }
    throw "Unknown error!";
}
void DataBase::addTravelToUser(const String &username, const Travel &travel)
{
    if (!userCreated(username))
        throw "User does not exist!";

    for (size_t i = 0; i < userCount; i++)
        if (strcmp(users[i].getUsername().getStr(), username.getStr()) == 0)
            users[i].addTravel(travel);
}

void DataBase::printDataBase() const
{
    for (size_t i = 0; i < userCount; i++)
    {
        users[i].printUser();
        cout << "---------------------" << endl;
    }
}
void DataBase::printDataBaseByDestination(const String &inputDestination) const
{
    cout << "Destination review for " << inputDestination << ":" << endl;
    cout << "------------------------------" << endl;
    double average = 0.0;
    size_t count = 0;

    for (size_t i = 0; i < userCount; i++)
        for (size_t j = 0; j < users[i].getJourneyCount(); j++)
            if (strcmp(users[i].getJourneys()[j]->getDestination().getStr(), inputDestination.getStr()) == 0)
            {
                users[i].getJourneys()[j]->printTravel();
                cout << "------------------------------" << endl;
                average += users[i].getJourneys()[j]->getGrade();
                count++;
            }
    if (count == 0)
        cout << "No destination found!" << endl;
    else
        cout << "Average grade for destination: " << average / count << endl;
}

void DataBase::startProgram()
{
    loadDataBase("database.db");

    size_t cmd = 0;
    bool successful = true;
    String currentUser;

    do
    {
        cout << "------------------------------" << endl;
        cout << "(1) Register new user" << endl;
        cout << "(2) Log In" << endl;
        cout << "(3) Exit" << endl;
        cin >> cmd;
        successful = true;
        try
        {
            switch (cmd)
            {
            case 1:
                currentUser = registerUser();
                break;

            case 2:
                currentUser = logIn();
                break;

            case 3:
                return;
            }
        }
        catch (const char *error)
        {
            cout << error << endl;
            successful = false;
        }
    } while (!successful || cmd < 0 || cmd > 3);
    cout << endl
         << "Logged in as " << currentUser << endl
         << endl;

    do
    {
        cout << "------------------------------" << endl;
        cout << "(1) Add Travel" << endl;
        cout << "(2) Destination review" << endl;
        cout << "(3) Save and Exit" << endl;
        cin >> cmd;
        try
        {
            switch (cmd)
            {
            case 1:
            {
                Travel travel;
                travel.inputTravel();
                addTravelToUser(currentUser, travel);
                break;
            }
            case 2:
                char destination[1024];
                cout << "Search for Destination: ";
                cin.ignore();
                cin.getline(destination, 1024);
                printDataBaseByDestination(destination);
                break;

            case 3:
                saveDataBase("database.db");
                return;
            }
        }
        catch (const char *error)
        {
            cout << error << endl;
        }
    } while (true);
}
