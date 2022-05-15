#include <iostream>
#include <fstream>
#include <cstring>
#include "photo.h"
using namespace std;

bool Photo::validPhoto(const String& photoName) const {
    for(size_t i = 0; i < photoName.length(); i++)
        if((photoName[i] < 'A' || photoName[i] > 'Z') && (photoName[i] < 'a' || 
            photoName[i] > 'z') && photoName[i] != '_' && photoName[i] != '.' && 
            (photoName[i] < '0' || photoName[i] > '9'))
            return false;

    size_t dotCount = 0;
    for(size_t i = 0; i < photoName.length(); i++)
        if(photoName[i] == '.')
            dotCount++;

    if(dotCount != 1)
        return false;
    return (strcmp(photoName.getStr() + photoName.length() - 3, "png") == 0) ||
           (strcmp(photoName.getStr() + photoName.length() - 4, "jpeg") == 0);
}

const String& Photo::getName() const {
    return name;
}
void Photo::setName(const String& name) {
    if(!validPhoto(name))
        throw "Invalid photo!";
    this->name = name;
}

Photo::Photo(const String& photoName) {
    name = photoName;
}

void Photo::readFromFile(ifstream& file) {
    name.readFromFile(file);
}
void Photo::saveToFile(ofstream& file) const {
    name.saveToFile(file);
}

istream& operator>>(istream& stream, Photo& photo) {
    stream >> photo.name;
    return stream;
}
ostream& operator<<(ostream& stream, const Photo& photo) {
    stream << photo.name;
    return stream;
}