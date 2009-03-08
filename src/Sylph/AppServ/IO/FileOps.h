/*
 * FileOps.h
 *
 *  Created on: 26-nov-2008
 *      Author: frank
 */

#ifndef FILEOPS_H_
#define FILEOPS_H_

#include "../../Core/File.h"

#include <string>

SYLPH_PUBLIC
namespace Sylph {
namespace AppServ {
namespace IO {

using namespace Sylph::Core;

string getExtension(File * f);
string getBasename(File * f);
bool isBundle(File * f);

}
}
}

#endif /* FILEOPS_H_ */
