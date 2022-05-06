#include "user.h"
#include <cstring>

const char* User::getUsername() const {
    return username;
}
const char* User::getPassword() const {
    return password;
}
const char* User::getEmail() const {
    return email;
}
Travel** User::getJourneys() const {
    return journeys;
}
const size_t User::getJourneyCount() const {
    return journeyCount;
}
void User::setUsername(const char* otherUsername) {
    for(size_t i = 0; i < strlen(otherUsername); i++)
        if((otherUsername[i] < 'A' || otherUsername[i] > 'Z') && (otherUsername[i] < 'a' || 
            otherUsername[i] > 'z') && (otherUsername[i] < '0' || otherUsername[i] > '9'))
            throw "Invalid username!";

    delete[] username;
    username = new char[strlen(otherUsername) + 1];
    strcpy(username, otherUsername);
}
void User::setPassword(const char* otherPassword) {
    delete[] password;
    password = new char[strlen(otherPassword) + 1];
    strcpy(password, otherPassword);
}
void User::setEmail(const char* otherEmail) {
    delete[] email;
    email = new char[strlen(otherEmail) + 1];
    strcpy(email, otherEmail);
}

void User::copyFrom(const User& otherUser) {
    username = nullptr;
    password = nullptr;
    email = nullptr;
    journeys = nullptr;
    setUsername(otherUser.username);
    setPassword(otherUser.password);
    setEmail(otherUser.email);

    journeyCount = otherUser.journeyCount;
    journeys = new Travel*[journeyCount];
    for(size_t i = 0; i < journeyCount; i++)
        journeys[i] = new Travel(*otherUser.journeys[i]);
}
void User::free() {
    delete[] username;
    delete[] password;
    delete[] email;
    for(size_t i = 0; i < journeyCount; i++)
        delete journeys[i];
    delete[] journeys;
}

User::User() {
    username = nullptr;
    password = nullptr;
    email = nullptr;
    journeys = nullptr;
    journeyCount = 0;
}
User::User(const char* otherUsername, const char* otherPassword, const char* otherEmail) {
    username = nullptr;
    password = nullptr;
    email = nullptr;
    setUsername(otherUsername);
    setPassword(otherPassword);
    setEmail(otherEmail);
    journeyCount = 0;
    journeys = nullptr;
}
User::User(const User& otherUser) {
    copyFrom(otherUser);
}
User& User::operator=(const User& otherUser) {
    if(this != &otherUser)
    {
        free();
        copyFrom(otherUser);
    }
    return *this;
}
User::~User() {
    free();
}

void User::addTravel(const Travel& addition) {
    journeyCount++;
    Travel** result = new Travel*[journeyCount];
    for(size_t i = 0; i < journeyCount - 1; i++)
        result[i] = journeys[i];
    result[journeyCount - 1] = new Travel(addition);
    delete[] journeys;
    journeys = result;
}
void User::readFromFile(ifstream& file) {
    size_t length = 0;
    file.read((char*)&length, sizeof(size_t));
    char* newUsername = new char[length];
    file.read((char*) newUsername, sizeof(char) * length);
    setUsername(newUsername);
    delete[] newUsername;

    file.read((char*)&length, sizeof(size_t));
    char* newPassword = new char[length];
    file.read((char*) newPassword, sizeof(char) * length);
    setPassword(newPassword);
    delete[] newPassword;

    file.read((char*)&length, sizeof(size_t));
    char* newEmail = new char[length];
    file.read((char*) newEmail, sizeof(char) * length);
    setEmail(newEmail);
    delete[] newEmail;
}
void User::saveToFile(ofstream& file) const {
    size_t length = strlen(username) + 1;
    file.write((const char*) &length, sizeof(size_t));
    file.write((const char*) username, sizeof(char) * length);

    length = strlen(password) + 1;
    file.write((const char*) &length, sizeof(size_t));
    file.write((const char*) password, sizeof(char) * length);

    length = strlen(email) + 1;
    file.write((const char*) &length, sizeof(size_t));
    file.write((const char*) email, sizeof(char) * length);
}

void User::readJourneysFromFile(ifstream& file) {
    for(size_t i = 0; i < journeyCount; i++)
        delete journeys[i];
    delete[] journeys;

    file.read((char*) &journeyCount, sizeof(size_t));
    journeys = new Travel*[journeyCount];
    for(size_t i = 0; i < journeyCount; i++) {
        Travel travel;
        travel.readFromFile(file);
        journeys[i] = new Travel(travel);  
    }
}
void User::saveJourneysToFile(ofstream& file) const {
    file.write((const char*) &journeyCount, sizeof(size_t));

    for(size_t i = 0; i < journeyCount; i++)
        journeys[i]->saveToFile(file);
}

void User::printUser() const {
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;
    for(size_t i = 0; i < journeyCount; i++)
        journeys[i]->printTravel();
}