#ifndef MEMORY_H
#define MEMORY_H

#include <string>

class Memory {
public:
  virtual ~Memory() = default;

  virtual char erase() = 0;
  virtual void insert(char ch) = 0;
  virtual int get_cursor_index() = 0;
  virtual void set_cursor_index(int index) = 0;
  virtual std::string to_string() = 0;
};

#endif //MEMORY_H
