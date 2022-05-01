#include <iostream>
#include <cstring>
#include "travel.h"
using namespace std;

bool Travel::validTimePeriod(Date timePeriod[2]) {
    return timePeriod[0] <= timePeriod[1];  
}

char* Travel::getName() const {
    return name;
}
char* Travel::getDestination() const {
    return destination;
}
const Date* Travel::getTimePeriod() const {
    return timePeriod;
}
size_t Travel::getGrade() const {
    return grade;
}
char* Travel::getComment() const {
    return comment;
}
Photo* Travel::getAlbum() const {
    return album;
}
size_t Travel::getPhotoCount() const {
    return photoCount;
}
void Travel::setName(char* otherName) {
    delete[] name;
    name = new char[strlen(otherName) + 1];
    strcpy(name, otherName);
}
void Travel::setDestination(char* otherDestination) {
    delete[] destination;
    destination = new char[strlen(otherDestination)];
    strcpy(destination, otherDestination);
}
void Travel::setTimePeriod(Date otherTimePeriod[2]) {
    if(!validTimePeriod(otherTimePeriod))
        throw "Invalid time period";
        
    timePeriod[0] = otherTimePeriod[0];
    timePeriod[1] = otherTimePeriod[1];
}
void Travel::setGrade(size_t otherGrade) {
    grade = otherGrade;
}
void Travel::setComment(char* otherComment) {
    delete[] comment;
    comment = new char[strlen(otherComment)];
    strcpy(comment, otherComment);
}
void Travel::setAlbum(Photo* otherAlbum, size_t otherPhotoCount) {
    delete[] album;
    photoCount = otherPhotoCount;
    album = new Photo[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        album[i] = otherAlbum[i];
}

void Travel::copyFrom(const Travel& otherTravel) {
    name = new char[strlen(otherTravel.name) + 1];
    destination = new char[strlen(otherTravel.destination) + 1];
    comment = new char[strlen(otherTravel.comment) + 1];

    strcpy(name, otherTravel.name);
    strcpy(destination, otherTravel.destination);
    strcpy(comment, otherTravel.comment);

    timePeriod[0] = otherTravel.timePeriod[0];
    timePeriod[1] = otherTravel.timePeriod[1];

    grade = otherTravel.grade;

    photoCount = otherTravel.photoCount;
    album = new Photo[photoCount];
    album = otherTravel.album;    
}
void Travel::free() {
    delete[] name;
    delete[] destination;
    delete[] comment;
    delete[] album;
}

Travel::Travel() {
    name = nullptr;
    destination = nullptr;
    grade = 1;
    comment = nullptr;
    album = nullptr;
    photoCount = 0;
}
Travel::Travel(char* otherName, char* otherDestination, Date otherTimePeriod[2], size_t otherGrade, char* otherComment, Photo* otherAlbum, size_t otherPhotoCount) {
    name = new char[strlen(otherName) + 1];
    destination = new char[strlen(otherDestination) + 1];
    comment = new char[strlen(otherComment) + 1];
    strcpy(name, otherName);
    strcpy(destination, otherDestination);
    strcpy(comment, otherComment);
    if(!validTimePeriod(otherTimePeriod))
        throw "Invalid time period";
    timePeriod[0] = otherTimePeriod[0];
    timePeriod[1] = otherTimePeriod[1];

    grade = otherGrade;
    photoCount = otherPhotoCount;
    album = new Photo[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        album[i] = otherAlbum[i];
}
Travel::Travel(const Travel& otherTravel) { 
    copyFrom(otherTravel);
}
Travel& Travel::operator=(const Travel& otherTravel) {
    if(this != &otherTravel)
    {
        free();
        copyFrom(otherTravel);
    }
    return *this;
}
Travel::~Travel() { 
    free();
}

void Travel::inputTravel() {
    free();
    char* buffer = new char[1024];
    cout << "Enter destination: ";
    cin >> buffer;
    setDestination(buffer);

    Date dateBuffer[2];
    cout << "Enter time period: ";
    cin >> dateBuffer[0] >> dateBuffer[1];
    setTimePeriod(dateBuffer);

    size_t gradeBuffer;
    cout << "Enter grade from 1 to 5: ";
    cin >> gradeBuffer;
    setGrade(gradeBuffer);

    cout << "Enter comment: ";
    cin >> buffer;
    setComment(buffer);

    size_t photoCountBuffer;
    cout << "Enter photo count: ";
    cin >> photoCountBuffer;
    photoCount = photoCountBuffer;

    Photo* albumBuffer = new Photo[photoCountBuffer];
    cout << "Enter photo files: ";
    for(size_t i = 0; i < photoCountBuffer; i++)
        cin >> albumBuffer[i];
    album = albumBuffer;
}

void Travel::printTravel() const {
    cout << "Destination: " << destination << endl;
    cout << "Time period: " << timePeriod[0] << " - " << timePeriod[1] << endl;
    cout << "Grade: " << grade << endl;
    cout << "Comment: " << comment << endl;
    cout << "Photos: ";
    for(size_t i = 0; i < photoCount; i++)
        cout << album[i] << endl;
}