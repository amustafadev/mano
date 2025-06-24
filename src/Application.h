#ifndef APPLICATION_H
#define APPLICATION_H

#include "Console.h"

class Application {
  const int APP_SAVE_KEY = 15;
  const int APP_EXIT_KEY = 24;

  Console editor;

  std::string filename;
  bool is_running = false;

  void update();
  void handle_save();

public:
  explicit Application(const std::string &filename);
  ~Application() = default;

  void launch();
};



#endif //APPLICATION_H
