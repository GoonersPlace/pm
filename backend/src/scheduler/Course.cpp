#include "Course.h"
#include <iostream>

Course::Course() {
    name = "";
    hoursPerWeek = 0;
}

Course::Course(string name, int hoursPerWeek) {
    this->name = name;
    this->hoursPerWeek = hoursPerWeek;
}

