#ifndef CONSOLE_H
#define CONSOLE_H

#include "Editor.h"
#include "GapBuffer.h"
#include "LineArray.h"

class Console final : public Editor {
  GapBuffer buffer = GapBuffer(16);
  LineArray line_count = LineArray(16);

  void remove_char();
  void insert_char(char ch);

  void up_key_input_action();
  void down_key_input_action();
  void left_key_input_action();
  void right_key_input_action();
  void backspace_key_input_action();
  void home_key_input_action();
  void end_key_input_action();

  static void init_colors();
  static void init_newline(int &row, int &col);

  void render_text() const;

public:
  Console();
  ~Console() override;

  void render() override;
  void handle_input(int ch) override;

  void write_to_file(const std::string &filename) override;
  void read_from_file(const std::string &filename) override;
};

#endif //CONSOLE_H
