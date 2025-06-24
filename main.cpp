#include "src/Application.h"

int main(const int argc, char *argv[]) {
  // read filename from args
  std::string filename = argc > 1 ? argv[1] : "";

  // launch application
  Application application(filename);
  application.launch();

  // return
  return 0;
}


