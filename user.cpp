#include "user.h"

char* User::getUsername() const {
    return username;
}
char* User::getPassword() const {
    return password;
}
char* User::getEmail() const {
    return email;
}
void User::setUsername(char* otherUsername) {
    username = new char[strlen(otherUsername) + 1];
    strcpy(username, otherUsername);
}
void User::setUsername(char* otherPassword) {
    password = new char[strlen(otherPassword) + 1];
    strcpy(password, otherPassword);
}
void User::setUsername(char* otherEmail) {
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