#include "ExVectrLibTemplate/your_header_files_here.hpp" //Should have the exact same name as the header file.


/**
 * The source files define functions declared inside the header files.
 * Its recommended to add comments explaining each implementation, but much more important is that the implementation should explain itsself!
 * 
 * You can use functions and classes from other ExVectr libraries by adding them to the CMakeLists.txt file and then include them here as you
 * would if you were using them for a project.
 * 
*/

#include "cstringt.h"

#include "ExVectrHAL/time_hal.hpp" //Included in the ExVectrHAL library.
#include "ExVectrCore/time_definitions.hpp" //Included in the ExVectrCore library.


/**
 * Simply takes the time from ExVectrHAL and converts it to seconds and returns that.
*/
float VCTR::yourSpecialFunctionDefined() {
    return (float)VCTR::internalTime()/SECONDS;
}


/**
 * Creates the string: "Hello user! The current time is x seconds since start!". Where x is the given parameter of system time in seconds.
*/
const char* VCTR::SomeSuperDuperClass::aSuperDuperFunction(float systemTime) {

    static char* outputString = new char[100];

    snprintf(outputString, 100, "Hello user! The current time is %f seconds since start!", systemTime);

    return outputString;

}



