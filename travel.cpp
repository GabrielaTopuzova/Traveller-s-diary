#include <iostream>
#include <cstring>
#include "travel.h"
using namespace std;

bool Travel::validTimePeriod(const Date timePeriod[2]) const {
    return timePeriod[0] <= timePeriod[1];  
}

const String& Travel::getDestination() const {
    return destination;
}
const Date* Travel::getTimePeriod() const {
    return timePeriod;
}
const size_t Travel::getGrade() const {
    return grade;
}
const String& Travel::getComment() const {
    return comment;
}
const Photo* Travel::getAlbum() const {
    return album;
}
const size_t Travel::getPhotoCount() const {
    return photoCount;
}
void Travel::setDestination(const String& otherDestination) {
    destination = otherDestination;
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
void Travel::setComment(const String& otherComment) {
    comment = otherComment;
}
void Travel::setAlbum(const Photo* otherAlbum, size_t otherPhotoCount) {
    delete[] album;
    photoCount = otherPhotoCount;
    album = new Photo[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        album[i] = otherAlbum[i];
}

void Travel::copyFrom(const Travel& otherTravel) {
    destination = otherTravel.destination;
    comment = otherTravel.comment;

    timePeriod[0] = otherTravel.timePeriod[0];
    timePeriod[1] = otherTravel.timePeriod[1];

    grade = otherTravel.grade;

    photoCount = otherTravel.photoCount;
    album = new Photo[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        album[i] = otherTravel.album[i];
}
void Travel::free() {
    delete[] album;
}

Travel::Travel() {
    destination = "";
    grade = 1;
    comment = "";
    album = nullptr;
    photoCount = 0;
}
Travel::Travel(const String& otherDestination, const Date otherTimePeriod[2], const size_t otherGrade, const String& otherComment, const Photo* otherAlbum, const size_t otherPhotoCount) {
    destination = otherDestination;
    comment = otherComment;

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
    destination.readFromFile(file);

    timePeriod[0].readFromFile(file);
    timePeriod[1].readFromFile(file);

    file.read((char*) &grade, sizeof(size_t));

    comment.readFromFile(file);

    file.read((char*) &photoCount, sizeof(size_t));
    Photo* newAlbum = new Photo[photoCount];
    for(size_t i = 0; i < photoCount; i++)
        newAlbum[i].readFromFile(file);
    setAlbum(newAlbum, photoCount);
}
void Travel::saveToFile(ofstream& file) const {
    destination.saveToFile(file);

    timePeriod[0].writeInFile(file);
    timePeriod[1].writeInFile(file);

    file.write((const char*) &grade, sizeof(size_t));

    comment.saveToFile(file);

    file.write((const char*) &photoCount, sizeof(size_t));
    for(size_t i = 0; i < photoCount; i++)
        album[i].saveToFile(file);
}

void Travel::inputTravel() {
    free();
    char* buffer = new char[1024];

    cout << "Enter destination: ";
    cin.ignore();
    cin.getline(buffer, 1024);
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
    cin.ignore();
    cin.getline(buffer, 1024);
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