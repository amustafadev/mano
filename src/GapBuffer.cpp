#include <cstring>
#include "GapBuffer.h"

GapBuffer::GapBuffer(const int size) {
  this->size = size;
  data = new char[size];

  gap_start = 0;
  gap_end = size;
}

GapBuffer::~GapBuffer() {
  delete[] data;
  data = nullptr;
}

void GapBuffer::move_gap_left() {
  if (gap_start > 0)
    data[--gap_end] = data[--gap_start];
}

void GapBuffer::move_gap_right() {
  if (gap_end < size)
    data[gap_start++] = data[gap_end++];
}

void GapBuffer::expand(const int delta) {
  // create new array
  auto const new_data = new char[size + delta];

  // copy data to new array
  memcpy(new_data, data, gap_start);
  memcpy(new_data + gap_start + delta, data + gap_end, size - gap_end);

  // update data pointer
  delete[] data;
  data = new_data;

  // update params
  size += delta;
  gap_end += delta;
}

void GapBuffer::insert(const char ch) {
  if (gap_start == gap_end)
    expand(size);
  data[gap_start++] = ch;
}

char GapBuffer::erase() {
  if (gap_start <= 0) return '\0';
  return data[--gap_start];
}

std::string GapBuffer::to_string() {
  std::string result;
  result.append(data, data + gap_start);
  result.append(data + gap_end, data + size);
  return result;
}

int GapBuffer::get_cursor_index() {
  return gap_start;
}

void GapBuffer::set_cursor_index(const int index) {
  const int delta = index - gap_start;
  const int gap_width = gap_end - gap_start;

  if (index < 0 || gap_end + delta > size) return;

  if (delta == 0) return;
  if (delta > 0) memmove(data + gap_start, data + gap_end, delta);
  else memmove(data + gap_end + delta, data + index, -delta);

  gap_start = index;
  gap_end = gap_start + gap_width;
}