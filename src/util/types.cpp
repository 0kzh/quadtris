#include "types.h"

// custom fn to print GridItem
std::ostream &operator<<(std::ostream &os, const GridItem g) {
  if (g.val) {
    os << *g.val;
  } else {
    os << " ";
  }
  return os;
}