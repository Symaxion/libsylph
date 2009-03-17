/* 
 * File:   ThisApp.cpp
 * Author: frank
 *
 * Created on 12 maart 2009, 16:45
 */

#include <cstdlib>
#include <iostream>

#include "Sylph.h"
int SylphMain() {
    std::cout << "Full path: " << thisapp->location() << std::endl;
}

