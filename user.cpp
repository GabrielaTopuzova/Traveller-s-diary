#include "user.h"
#include <cstring>

char* User::getUsername() const {
    return username;
}
char* User::getPassword() const {
    return password;
}
char* User::getEmail() const {
    return email;
}
Travel** User::getJourneys() const {
    return journeys;
}
size_t User::getJourneyCount() const {
    return journeyCount;
}
void User::setUsername(char* otherUsername) {
    username = new char[strlen(otherUsername) + 1];
    strcpy(username, otherUsername);
}
void User::setPassword(char* otherPassword) {
    password = new char[strlen(otherPassword) + 1];
    strcpy(password, otherPassword);
}
void User::setEmail(char* otherEmail) {
    email = new char[strlen(otherEmail) + 1];
    strcpy(email, otherEmail);
}

void User::copyFrom(const User& otherUser) {
    setUsername(otherUser.username);
    setPassword(otherUser.password);
    setEmail(otherUser.email); 
}
void User::free() {
    delete[] username;
    delete[] password;
    delete[] email;
}

User::User(char* otherUsername, char* otherPassword, char* otherEmail) {
    setUsername(otherUsername);
    setPassword(otherPassword);
    setEmail(otherEmail);    
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
    result = journeys;
    *result[journeyCount] = addition;
    journeys = result;
}

void User::saveToFile(ofstream& stream) const {
    for(size_t i = 0; i < journeyCount; i++)
    {
        stream << journeys[i]->getName() << journeys[i]->getDestination();
        stream << journeys[i]->getTimePeriod() << journeys[i]->getGrade();
        stream << journeys[i]->getComment() << journeys[i]->getPhotoCount() << journeys[i]->getAlbum(); //
    }
}

void User::printUser() const {
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;
    for(size_t i = 0; i < journeyCount; i++)
        journeys[i]->printTravel();
}