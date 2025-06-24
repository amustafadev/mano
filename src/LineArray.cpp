// #include <cstring>
// #include "LineArray.h"
//
// LineArray::LineArray(const int size) {
//   this->size = size;
//   data = new int[size];
//   data[0] = 0;
// }
//
// LineArray::~LineArray() {
//   delete[] data;
//   data = nullptr;
// }
//
// void LineArray::expand(const int delta) {
//   auto const new_data = new int[size + delta];
//   memcpy(new_data, data, size * sizeof(int));
//   delete[] data;
//   size += delta;
//   data = new_data;
// }
//
// void LineArray::drop_row(const int row) {
//   if (row < max_used_row)
//     memcpy(data + row, data + row + 1, (max_used_row - row) * sizeof(int));
//   max_used_row--;
// }
//
// void LineArray::insert_row(const int row) {
//   if (++max_used_row >= size) expand(size);
//   if (row < max_used_row)
//     memcpy(data + row + 1, data + row, (max_used_row - row) * sizeof(int));
//   data[row] = data[row - 1] - current_col;
//   data[row - 1] = current_col;
// }
//
// void LineArray::merge_rows(const int row_keep, const int row_drop) {
//   data[row_keep] += data[row_drop];
//   drop_row(row_drop);
// }
//
// void LineArray::update_line_count(const bool is_insert) {
//   if (is_insert) {
//     insert_row(++current_row);
//     current_col = 0;
//   }
//   else {
//     current_col = data[current_row - 1];
//     merge_rows(current_row - 1, current_row);
//     current_row--;
//   }
// }
//
// void LineArray::update_current_width(const bool is_insert) {
//   if (is_insert) {
//     current_col++;
//     data[current_row]++;
//   }
//   else {
//     current_col--;
//     data[current_row]--;
//   }
//   if (data[current_row] < 0 && current_row > 0) {
//     drop_row(current_row--);
//     current_col = data[current_row];
//   }
// }
//
// int LineArray::get_row() const {
//   return current_row;
// }
//
// int LineArray::get_col() const {
//   return current_col;
// }
//
// int LineArray::get_count(const int index) const {
//   return data[index];
// }
//
// void LineArray::update(const char ch, const bool is_insert) {
//   if (ch == '\n') update_line_count(is_insert);
//   else update_current_width(is_insert);
// }
//
// void LineArray::set_current_row_from_index(const int index) {
//   int row = 0, total = 0;
//   for (row = 0; row <= max_used_row; row++) {
//     total += data[row];
//     if (row < max_used_row) total += 1;
//     if (index < total) break;
//   }
//   current_row = row;
//   if (current_row == 0) current_col = index;
//   else if (current_row == max_used_row) current_col = index - total + data[current_row];
//   else current_col = index - total + data[current_row] + 1;
// }

#include <cstring>
#include "LineArray.h"

LineArray::LineArray(const int size) {
  this->size = size;
  data = new int[size];
  data[0] = 0;
}

LineArray::~LineArray() {
  delete[] data;
  data = nullptr;
}

int LineArray::get(const int index) const {
  return data[index];
}

void LineArray::expand(const int delta) {
  auto const new_data = new int[size + delta];
  memcpy(new_data, data, size * sizeof(int));
  delete[] data;
  size += delta;
  data = new_data;
}

int LineArray::index_to_row(const int index) const {
  int row = 0, total = 0;
  for (row = 0; row < max_used_row; row++) {
    total += data[row] + 1;
    if (index < total) break;
  }
  return row;
}

int LineArray::index_row_to_col(const int index, const int row) const {
  if (row == 0) return index;
  int total = 0;
  for (int i = 0; i < row; i++) total += data[i] + 1;
  return index - total;
}

void LineArray::drop_row(const int row) {
  if (row < max_used_row)
    memcpy(data + row, data + row + 1, (max_used_row - row) * sizeof(int));
  max_used_row--;
}

void LineArray::insert_row(const int row, int const index) {
  if (++max_used_row >= size) expand(size);
  if (row + 1 < max_used_row)
    memcpy(data + row + 2, data + row + 1, (max_used_row - row) * sizeof(int));

  const int col = index_row_to_col(index, row);
  data[row + 1] = data[row] - col;
  data[row] = col;
}

void LineArray::merge_rows(const int row_keep, const int row_drop) {
  data[row_keep] += data[row_drop];
  drop_row(row_drop);
}

void LineArray::update_line_count(const bool is_insert, const int row, const int index) {
  if (is_insert) insert_row(row, index);
  else merge_rows(row - 1, row);
}

void LineArray::update_current_width(const bool is_insert, const int row) {
  if (is_insert) data[row]++;
  else data[row]--;
  if (data[row] < 0 && row > 0) drop_row(row);
}

void LineArray::update(const char ch, const bool is_insert, const int index) {
  const int current_row = index_to_row(index);
  if (ch == '\n') update_line_count(is_insert, current_row, index);
  else update_current_width(is_insert, current_row);
}
