#include <iostream>
#include <string>

//// helper function to get prefix
//int prefix(std::string command) {
//    int pre = 1;
//    if (command[0] >= 48 && command[0] <= 57) {
//      pre = (int)command[0] - 48;
//    }
//    return pre;
//}
//
//int main () {
//std::string command;
//  std::cin >> command;
//  int pre = prefix(command);
//
//  if (command.compare(1, 3, "lef") == 0 || command.compare(0, 3, "lef") == 0) {
//    //left
//  } else if (command.compare(0, 2, "ri") == 0 || command.compare(1, 2, "ri") == 0) {
//    //right
//  } else if (command.compare(0, 2, "do") == 0 || command.compare(1, 2, "do") == 0) {
//    //down
//  } else if (command.compare(0, 2, "cl") == 0 || command.compare(1, 2, "cl") == 0) {
//    //cw
//  } else if (command.compare(0,2, "co") == 0 || command.compare(1,2, "co") == 0) {
//    //ccw
//  } else if (command.compare(0,2 ,"dr") == 0 || command.compare(1,2 ,"dr") == 0) {
//    //drop
//  } else if (command.compare(0,6,"levelu") == 0 || command.compare(1,6,"levelu") == 0) {
//    //levelu
//  } else if (command.compare(0,6,"leveld") == 0 || command.compare(1,6,"leveld") == 0) {
//    //leveld
//  } else if (command[0] == 'n') {
//    //norandom <file>
//  } else if (command.compare(0,2,"se") == 0) {
//    //sequence <file>
//  } else if (command.compare(0,2,"re") == 0) {
//    //restart
//  } else if (command.compare(0,2,"re") == 0) {
//    //hint
//  } else if (command == "I" || command == "J" || command == "L" ||
//  command == "S" || command == "Z" || command == "O" || command == "T") {
//    // I, J, L, S, Z, O, T
//  } else {
//      // invalid command
//  }
//}
