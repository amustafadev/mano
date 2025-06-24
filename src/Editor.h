#ifndef EDITOR_H
#define EDITOR_H

#include "Memory.h"

class Editor {
protected:
  Memory &memory;

public:
  explicit Editor(Memory &memory): memory(memory) {};
  virtual ~Editor() = default;

  virtual void render() = 0;
  virtual void handle_input(int ch) = 0;

  virtual void write_to_file(const std::string &filename) = 0;
  virtual void read_from_file(const std::string &filename) = 0;
};

#endif //EDITOR_H
