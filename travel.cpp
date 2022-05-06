#include <iostream>
#include <cstring>
#include "travel.h"
using namespace std;

bool Travel::validTimePeriod(const Date timePeriod[2]) const {
    return timePeriod[0] <= timePeriod[1];  
}

const char* Travel::getDestination() const {
    return destination;
}
const Date* Travel::getTimePeriod() const {
    return timePeriod;
}
const size_t Travel::getGrade() const {
    return grade;
}
const char* Travel::getComment() const {
    return comment;
}
const Photo* Travel::getAlbum() const {
    return album;
}
const size_t Travel::getPhotoCount() const {
    return photoCount;
}
void Travel::setDestination(const char* otherDestination) {
    delete[] destination;
    destination = new char[strlen(otherDestination)];
    strcpy(destination, otherDestination);
}
void Travel::setTimePeriod(const Date otherTimePeriod[2]) {
    if(!validTimePeriod(otherTimePeriod))
        throw "Invalid time period!";
        
    timePeriod[0] = otherTimePeriod[0];
    timePeriod[1] = otherTimePeriod[1];
}
void Travel::setGrade(const size_t otherGrade) {
    if(otherGrade < 1 || otherGrade > 5)
        throw "Invalid grade!";
    grade = otherGrade;
}
void Travel::setComment(const char* otherComment) {
    delete[] comment;
    comment = new char[strlen(otherComment)];
    strcpy(comment, otherComment);
}
void Travel::setAlbum(const Photo* otherAlbum, size_t otherPhotoCount) {
    delete[] album;
    photoCount = otherPhotoCount;
    album = new Photo[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        album[i] = otherAlbum[i];
}

void Travel::copyFrom(const Travel& otherTravel) {
    destination = new char[strlen(otherTravel.destination) + 1];
    comment = new char[strlen(otherTravel.comment) + 1];

    strcpy(destination, otherTravel.destination);
    strcpy(comment, otherTravel.comment);

    timePeriod[0] = otherTravel.timePeriod[0];
    timePeriod[1] = otherTravel.timePeriod[1];

    grade = otherTravel.grade;

    photoCount = otherTravel.photoCount;
    album = new Photo[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        album[i] = otherTravel.album[i];
}
void Travel::free() {
    delete[] destination;
    delete[] comment;
    delete[] album;
}

Travel::Travel() {
    destination = nullptr;
    grade = 1;
    comment = nullptr;
    album = nullptr;
    photoCount = 0;
}
Travel::Travel(const char* otherDestination, const Date otherTimePeriod[2], const size_t otherGrade, const char* otherComment, const Photo* otherAlbum, const size_t otherPhotoCount) {
    destination = new char[strlen(otherDestination) + 1];
    comment = new char[strlen(otherComment) + 1];

    strcpy(destination, otherDestination);
    strcpy(comment, otherComment);

    if(!validTimePeriod(otherTimePeriod))
        throw "Invalid time period!";
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

void Travel::readFromFile(ifstream& file) {
    size_t length = 0;
    file.read((char*)&length, sizeof(size_t));
    char* newDestination = new char[length];
    file.read((char*) newDestination, sizeof(char) * length);
    setDestination(newDestination);
    delete[] newDestination;

    timePeriod[0].readFromFile(file);
    timePeriod[1].readFromFile(file);

    file.read((char*) &grade, sizeof(size_t));

    file.read((char*)&length, sizeof(size_t));
    char* newComment = new char[length];
    file.read((char*) newComment, sizeof(char) * length);
    setComment(newComment);
    delete[] newComment;

    file.read((char*) &photoCount, sizeof(size_t));
    Photo* newAlbum = new Photo[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        newAlbum[i].readFromFile(file);
    setAlbum(newAlbum, photoCount);
}
void Travel::saveToFile(ofstream& file) const {
    size_t length = strlen(destination) + 1;
    length = strlen(destination) + 1;
    file.write((const char*) &length, sizeof(size_t));
    file.write((const char*) destination, sizeof(char) * length);

    timePeriod[0].writeInFile(file);
    timePeriod[1].writeInFile(file);

    file.write((const char*) &grade, sizeof(size_t));

    length = strlen(comment) + 1;
    file.write((const char*) &length, sizeof(size_t));
    file.write((const char*) comment, sizeof(char) * length);

    file.write((const char*) &photoCount, sizeof(size_t));
    for(size_t i = 0; i < photoCount; i++)
        album[i].saveToFile(file);
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
    cout << "Time period: " << timePeriod[0] << " - " << timePeriod[1] << endl;
    cout << "Grade: " << grade << endl;
    cout << "Comment: " << comment << endl;
    cout << "Photos: ";
    for(size_t i = 0; i < photoCount; i++)
        cout << album[i] << endl;
}