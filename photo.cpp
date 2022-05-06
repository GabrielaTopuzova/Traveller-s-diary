#include <iostream>
#include <fstream>
#include <cstring>
#include "photo.h"
using namespace std;

bool Photo::validPhoto(const char* photoName) const {
    for(size_t i = 0; i < strlen(photoName); i++)
        if((photoName[i] < 'A' || photoName[i] > 'Z') && (photoName[i] < 'a' || 
            photoName[i] > 'z') && photoName[i] != '_' && photoName[i] != '.' && 
            (photoName[i] < '0' || photoName[i] > '9'))
            return false;

    size_t dotCount = 0;
    for(size_t i = 0; i < strlen(photoName); i++)
        if(photoName[i] == '.')
            dotCount++;

    if(dotCount != 1)
        return false;
    return (strcmp(photoName + strlen(photoName) - 3, "png") == 0) ||
           (strcmp(photoName + strlen(photoName) - 4, "jpeg") == 0);
}

const char* Photo::getName() const {
    return name;
}
void Photo::setName(const char* name) {
    if(!validPhoto(name))
        throw "Invalid photo!";
    delete[] this->name;
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Photo::Photo() {
    name = nullptr;
}
Photo::Photo(const char* photoName) {
    name = nullptr;
    setName(photoName);
}
Photo::Photo(const Photo &otherPhoto) {
    name = nullptr;
    setName(otherPhoto.name);
}
Photo::~Photo() {
    delete[] name;
}

Photo& Photo::operator=(const Photo& otherPhoto) {
    if(this != &otherPhoto)
    {
        delete[] name;
        setName(otherPhoto.name);
    }
    return *this;
}

void Photo::readFromFile(ifstream& file) {
    size_t length = 0;
    file.read((char*)&length, sizeof(size_t));
    char* newName = new char[length];
    file.read((char*) newName, sizeof(char) * length);
    setName(newName);
    delete[] newName;
}
void Photo::saveToFile(ofstream& file) const {
    size_t length = strlen(name) + 1;
    file.write((const char*)&length, sizeof(size_t));
    file.write((const char*)name, sizeof(char) * length);
}

istream& operator>>(istream& stream, Photo& photo) {
    char* name = new char[1024];
    stream >> name;
    photo.setName(name);
    return stream;
}
ostream& operator<<(ostream& stream, const Photo& photo) {
    stream << photo.name;
    return stream;
}