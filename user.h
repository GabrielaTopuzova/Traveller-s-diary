#ifndef __USER
#define __USER

class User  {
    char* name;
    char* destination;
    size_t timePeriod[6];
    size_t grade;
    char* comment;
    char** album;
    size_t photoCount;

    bool isCreated(const User&) const;
public:
    User(char*, char*, size_t[6], size_t, char*, char**, size_t);
    User(const User&);
    User& operator=(const User&);
    ~User();

    void copyFrom(const User&);
    void free();

    User& editUser();
    void saveUser() const;
    void printUser() const;
    
    char* getName() const;
    char* getDestination() const;
    const size_t* getTimePeriod() const;
    size_t getGrade() const;
    char* getComment() const;
    char** getAlbum() const;
    size_t getPhotoCount() const;
    void setName(char*);
    void setDestination(char*);
    void setTimePeriod(char [6]);
    void setGrade(size_t);
    void setComment(char*);
    void setAlbum(char**);

};
#endif