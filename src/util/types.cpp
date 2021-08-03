#include "types.h"

/**
 * Custom function to output a grid item based on its block type.
 * 
 * @param os the output stream
 * @param g the grid item
 * @return the stream containing the grid item output
 */
//custom fn to print GridItem
std::ostream &operator<<(std::ostream &os, const GridItem g) {
  if (g.val) {
    os << blockTypeToChar[*g.val];
  } else {
    os << " ";
  }
  return os;
}