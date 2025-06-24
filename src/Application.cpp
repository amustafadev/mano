#include <ncurses.h>
#include "Application.h"

Application::Application(const std::string &filename) : filename(filename) {
  is_running = true;
  editor.read_from_file(filename);
}

void Application::launch() {
  while (is_running)
    update();
}


void Application::handle_save() {
  if (filename.empty()) return;  // TODO: prompt filename
  editor.write_to_file(filename);
}


void Application::update() {
  // wait for input
  const int ch = getch();

  // application level inputs
  if (ch == KEY_RESIZE) return;
  if (ch == APP_EXIT_KEY) is_running = false;
  else if (ch == APP_SAVE_KEY) handle_save();

  // editor level inputs
  else editor.handle_input(ch);

  // render
  editor.render();
}