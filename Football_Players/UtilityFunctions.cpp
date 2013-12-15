#include <iostream>
#include "UtilityFunctions.h"

#include <limits>

namespace mas {

void SkipLine(std::istream& input, char delimiter)
{
  input.ignore(std::numeric_limits<int>::max(), delimiter);
}

}
