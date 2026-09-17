#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course {
public:
    string name;
    int hoursPerWeek;

    Course();
    Course(string name, int hoursPerWeek);
};

#endif
