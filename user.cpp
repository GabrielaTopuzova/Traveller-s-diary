#include <iostream>
#include <cstring>
#include "user.h"
using namespace std;

char* User::getName() const {
    return name;
}
char* User::getDestination() const {
    return destination;
}
const size_t* User::getTimePeriod() const {
    return timePeriod;
}
size_t User::getGrade() const {
    return grade;
}
char* User::getComment() const {
    return comment;
}
char** User::getAlbum() const {
    return album;
}
size_t User::getPhotoCount() const {
    return photoCount;
}
void User::setName(char* otherName) {
    strcpy(name, otherName);
}
void User::setDestination(char* otherDestination) {
    strcpy(destination, otherDestination);
}
void setTimePeriod(char [6]) {
    
}
void User::setGrade(size_t otherGrade) {
    grade = otherGrade;
}
void User::setComment(char* otherComment) {
    strcpy(comment, otherComment);
}
void User::setAlbum(char** otherAlbum) {
    for(size_t i = 0; i < photoCount; i++)
    {
        album[i] = new char[strlen(otherAlbum[i]) + 1];
        strcpy(album[i], otherAlbum[i]);
    }
}

void User::copyFrom(const User& otherUser) {
    name = new char[strlen(otherUser.name) + 1];
    destination = new char[strlen(otherUser.destination) + 1];
    comment = new char[strlen(otherUser.comment) + 1];
    strcpy(name, otherUser.name);
    strcpy(destination, otherUser.destination);
    strcpy(comment, otherUser.comment);
    for(size_t i = 0; i < 6; i++)
        timePeriod[i] = otherUser.timePeriod[i];
    grade = otherUser.grade;
    photoCount = otherUser.photoCount;
    album = new char*[photoCount];
    for(size_t i = 0; i < photoCount; i++)
    {
        album[i] = new char[strlen(otherUser.album[i]) + 1];
        strcpy(album[i], otherUser.album[i]);
    }
}
void User::free() {
    delete[] name;
    delete[] destination;
    delete[] comment;
    for(size_t i = 0; i < photoCount; i++)
        delete[] album[i];
    delete[] album;
}

User::User(char* otherName, char* otherDestination, size_t otherTimePeriod[6], size_t otherGrade, char* otherComment, char** otherAlbum, size_t otherPhotoCount) {
    name = new char[strlen(otherName) + 1];
    destination = new char[strlen(otherDestination) + 1];
    comment = new char[strlen(otherComment) + 1];
    strcpy(name, otherName);
    strcpy(destination, otherDestination);
    strcpy(comment, otherComment);
    for(size_t i = 0; i < 6; i++)
        timePeriod[i] = otherTimePeriod[i];
    grade = otherGrade;
    photoCount = otherPhotoCount;
    album = new char*[photoCount];
    for(size_t i = 0; i < photoCount; i++)
    {
        album[i] = new char[strlen(otherAlbum[i]) + 1];
        strcpy(album[i], otherAlbum[i]);
    }
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
























