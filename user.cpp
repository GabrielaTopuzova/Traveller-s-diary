#include <iostream>
#include <cstring>
#include "user.h"
using namespace std;

bool User::validTimePeriod(Date timePeriod[2]) {
    if(!(timePeriod[0] <= timePeriod[1]))
        return false;
    return true;    
}
bool User::isCreated(const User& user) const {

}

char* User::getName() const {
    return name;
}
char* User::getDestination() const {
    return destination;
}
const Date* User::getTimePeriod() const {
    return timePeriod;
}
size_t User::getGrade() const {
    return grade;
}
char* User::getComment() const {
    return comment;
}
Photo* User::getAlbum() const {
    return album;
}
size_t User::getPhotoCount() const {
    return photoCount;
}
void User::setName(char* otherName) {
    this->name = new char[strlen(otherName)];
    strcpy(name, otherName);
}
void User::setDestination(char* otherDestination) {
    this->destination = new char[strlen(otherDestination)];
    strcpy(destination, otherDestination);
}
void User::setTimePeriod(Date otherTimePeriod[2]) {
    if(!validTimePeriod(otherTimePeriod))
        throw "Not valid time period";
        
    timePeriod[0] = otherTimePeriod[0];
    timePeriod[1] = otherTimePeriod[1];
}
void User::setGrade(size_t otherGrade) {
    grade = otherGrade;
}
void User::setComment(char* otherComment) {
    this->comment = new char[strlen(otherComment)];
    strcpy(comment, otherComment);
}
void User::setAlbum(Photo* otherAlbum) {
    album = otherAlbum;
}

void User::copyFrom(const User& otherUser) {
    name = new char[strlen(otherUser.name) + 1];
    destination = new char[strlen(otherUser.destination) + 1];
    comment = new char[strlen(otherUser.comment) + 1];

    strcpy(name, otherUser.name);
    strcpy(destination, otherUser.destination);
    strcpy(comment, otherUser.comment);

    timePeriod[0] = otherUser.timePeriod[0];
    timePeriod[1] = otherUser.timePeriod[1];

    grade = otherUser.grade;

    photoCount = otherUser.photoCount;
    album = new Photo[photoCount];
    album = otherUser.album;    
}
void User::free() {
    delete[] name;
    delete[] destination;
    delete[] comment;
    delete[] album;
}

User::User(char* otherName, char* otherDestination, Date otherTimePeriod[2], size_t otherGrade, char* otherComment, Photo* otherAlbum, size_t otherPhotoCount) {
    name = new char[strlen(otherName) + 1];
    destination = new char[strlen(otherDestination) + 1];
    comment = new char[strlen(otherComment) + 1];
    strcpy(name, otherName);
    strcpy(destination, otherDestination);
    strcpy(comment, otherComment);

    timePeriod[0] = otherTimePeriod[0];
    timePeriod[1] = otherTimePeriod[1];

    grade = otherGrade;
    photoCount = otherPhotoCount;
    album = new Photo[photoCount];
    album = otherAlbum;
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