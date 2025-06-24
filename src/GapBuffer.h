#ifndef GAPBUFFER_H
#define GAPBUFFER_H

#include "Memory.h"

class GapBuffer final : public Memory {
  char *data = nullptr;
  int size, gap_start, gap_end;

  void move_gap_left();
  void move_gap_right();
  void expand(int delta);

public:
  explicit GapBuffer(int size);
  ~GapBuffer() override;

  char erase() override;
  void insert(char ch) override;
  int get_cursor_index() override;
  void set_cursor_index(int index) override;
  std::string to_string() override;
};

#endif //GAPBUFFER_H
