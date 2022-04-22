#include <iostream>
#include <cstring>
#include "photo.h"
using namespace std;

bool Photo::validPhoto(char* photoName) const {
    return strstr(name + strlen(name) - 4, "png") != nullptr;
}

char* Photo::getName() const {
    return name;
}
void Photo::setName(char* name) {
    this->name = new char[strlen(name)];
    strcpy(this->name, name);
}

Photo::Photo() {
    name = nullptr;
}

Photo::Photo(char* photoName) {
    setName(photoName);
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

istream& operator>>(istream& stream, Photo& photo) {
    char* name = new char[1024];
    stream >> name;
    char* result = new char[strlen(name) + 1];
    strcpy(photo.name, result);
    return stream;
}
ostream& operator<<(ostream& stream, const Photo& photo) {
    stream << photo.name;
    return stream;
}