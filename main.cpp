#include <iostream>
#include "src/Application.h"

int main(const int argc, char *argv[]) {
  // read filename from args
  if (argc < 2) {
    std::cerr << "ERROR: Filename required!\n"
              << "Example: mano <filename>";
    return 1;
  }
  const std::string filename = argv[1];

  // launch application
  Application application(filename);
  application.launch();

  // return
  return 0;
}
