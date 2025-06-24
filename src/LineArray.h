#ifndef LINEARRAY_H
#define LINEARRAY_H

class LineArray {
  int size;
  int *data = nullptr;

  void expand(int delta);
  void drop_row(int row);
  void insert_row(int row, int index);
  void merge_rows(int row_keep, int row_drop);

  void update_line_count(bool is_insert, int row, int index);
  void update_current_width(bool is_insert, int row);

public:
  explicit LineArray(int size);
  ~LineArray();

  int max_used_row = 0;

  [[nodiscard]] int get(int index) const;
  [[nodiscard]] int index_to_row(int index) const;
  [[nodiscard]] int index_row_to_col(int index, int row) const;

  void update(char ch, bool is_insert, int index);
};

#endif //LINEARRAY_H
