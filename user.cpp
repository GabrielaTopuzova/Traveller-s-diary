#include "user.h"
#include <cstring>

const String& User::getUsername() const {
    return username;
}
const String& User::getPassword() const {
    return password;
}
const String& User::getEmail() const {
    return email;
}
Travel** User::getJourneys() const {
    return journeys;
}
const size_t User::getJourneyCount() const {
    return journeyCount;
}
void User::setUsername(const String& otherUsername) {
    for(size_t i = 0; i < otherUsername.length(); i++)
        if((otherUsername[i] < 'A' || otherUsername[i] > 'Z') && (otherUsername[i] < 'a' || 
            otherUsername[i] > 'z') && (otherUsername[i] < '0' || otherUsername[i] > '9'))
            throw "Invalid username!";

    username = otherUsername;
}
void User::setPassword(const String& otherPassword) {
    password = otherPassword;
}
void User::setEmail(const String& otherEmail) {
    email = otherEmail;
}

void User::copyFrom(const User& otherUser) {
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
    for(size_t i = 0; i < journeyCount; i++)
        delete journeys[i];
    delete[] journeys;
}

User::User() {
    username = "";
    password = "";
    email = "";
    journeys = nullptr;
    journeyCount = 0;
}
User::User(const String& otherUsername, const String& otherPassword, const String& otherEmail) {
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
    username.readFromFile(file);
    password.readFromFile(file);
    email.readFromFile(file);
}
void User::saveToFile(ofstream& file) const {
    username.saveToFile(file);
    password.saveToFile(file);
    email.saveToFile(file);
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