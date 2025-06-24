#include <fstream>
#include <ncurses.h>
#include "Console.h"

Console::Console() : Editor(buffer) {
  // initialize
  initscr();
  cbreak();
  noecho();
  init_colors();
  keypad(stdscr, TRUE);

  // render output
  render();
}

Console::~Console() {
  endwin();
}

void Console::remove_char() {
  const int index = buffer.get_cursor_index();
  const char ch = buffer.erase();
  if (ch == '\0') return;
  line_count.update(ch, false, index);
}

void Console::insert_char(const char ch) {
  const int index = buffer.get_cursor_index();
  buffer.insert(ch);
  line_count.update(ch, true, index);
}

void Console::up_key_input_action() {
  const int index = buffer.get_cursor_index();
  const int row = line_count.index_to_row(index);
  if (row == 0) return;

  const int prev_row_count = line_count.get(row - 1);
  const int col = line_count.index_row_to_col(index, row);

  int target = index - col - prev_row_count - 1;
  target += prev_row_count < col ? prev_row_count : col;
  buffer.set_cursor_index(target);
}

void Console::down_key_input_action() {
  const int index = buffer.get_cursor_index();
  const int row = line_count.index_to_row(index);
  if (row == line_count.max_used_row) return;

  const int next_row_count = line_count.get(row + 1);
  const int col = line_count.index_row_to_col(index, row);

  int target = index + (line_count.get(row) - col) + 1;
  target += next_row_count < col ? next_row_count : col;
  buffer.set_cursor_index(target);
}

void Console::left_key_input_action() {
  buffer.set_cursor_index(buffer.get_cursor_index() - 1);
}

void Console::right_key_input_action() {
  buffer.set_cursor_index(buffer.get_cursor_index() + 1);
}

void Console::backspace_key_input_action() {
  remove_char();
}

void Console::home_key_input_action() {
  const int index = buffer.get_cursor_index();
  const int row = line_count.index_to_row(index);
  const int col = line_count.index_row_to_col(index, row);
  if (col == 0) return;
  memory.set_cursor_index(index - col);
}

void Console::end_key_input_action() {
  const int index = buffer.get_cursor_index();
  const int row = line_count.index_to_row(index);
  const int col = line_count.index_row_to_col(index, row);
  const int cur_row_count = line_count.get(row);
  if (col == cur_row_count) return;
  memory.set_cursor_index(index - col + cur_row_count);
}

void Console::init_colors() {
  start_color();
  use_default_colors();
  init_pair(1, COLOR_CYAN, -1);
}

void Console::init_newline(int &row, int &col) {
  // re int row and col
  row++;
  col = 0;

  // render row number
  attron(COLOR_PAIR(1));
  mvaddch(row, col++, '[');
  for (const char ch: std::to_string(row + 1))
    mvaddch(row, col++, ch);
  mvaddch(row, col++, ']');
  mvaddch(row, col++, ':');
  mvaddch(row, col++, ' ');
  attroff(COLOR_PAIR(1));
}

void Console::render_text() const {
  // init text display
  int row = -1, col = 0;
  init_newline(row, col);

  // init cursor display
  int cursor_row = 0, cursor_col = 0;
  const int cursor_index = memory.get_cursor_index();

  // get text
  std::string const content = memory.to_string();
  int const content_length = static_cast<int>(content.size());

  // display text
  for (int i = 0; i < content_length; i++) {
    // check cursor index
    if (i == cursor_index) {
      cursor_row = row;
      cursor_col = col;
    }

    // check newline
    if (content[i] == '\n') {
      init_newline(row, col);
      continue;
    }

    // print character
    mvaddch(row, col++, content[i]);
  }

  // check if cursor at end
  if (cursor_index == content_length) {
    cursor_row = row;
    cursor_col = col;
  }

  // display cursor
  move(cursor_row, cursor_col);
}

void Console::write_to_file(const std::string &filename) {
  std::ofstream file(filename);
  if (file.is_open()) {
    file << buffer.to_string() + '\n';
    file.close();
  }
}

void Console::read_from_file(const std::string &filename) {
  std::ifstream file(filename);
  if (file) {
    // populate buffer
    char ch;
    while (file.get(ch)) {
      insert_char(ch);
    }
    file.close();

    // display output
    render();
  }
}

void Console::render() {
  clear();
  render_text();
  refresh();
}

void Console::handle_input(const int ch) {
  switch (ch) {
    case KEY_UP:
      up_key_input_action();
      break;

    case KEY_DOWN:
      down_key_input_action();
      break;

    case KEY_LEFT:
      left_key_input_action();
      break;

    case KEY_RIGHT:
      right_key_input_action();
      break;

    case KEY_BACKSPACE:
      backspace_key_input_action();
      break;

    case KEY_HOME:
      home_key_input_action();
      break;

    case KEY_END:
      end_key_input_action();
      break;

    default:
      insert_char(static_cast<char>(ch));
  }
}
