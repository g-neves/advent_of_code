#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  const char *data;
  size_t length;
} String_View;

String_View sv(const char *data) { return (String_View){data, strlen(data)}; }

int has_up(size_t row, size_t n_rows) { return row > 0; }
int has_down(size_t row, size_t n_rows) { return row < n_rows - 1; }
int has_left(size_t col, size_t len_col) { return col > 0; }
int has_right(size_t col, size_t len_col) { return col < len_col - 1; }

// int check_up(void) { return 0; }
// int check_down(void) { return 0; }
// int check_left(void) { return 0; }
// int check_right(void) { return 0; }
// int check_up_left(void) { return 0; }
// int check_up_right(void) { return 0; }
// int check_down_left(void) { return 0; }
// int check_down_right(void) { return 0; }

size_t find_first_of(String_View *sv, char c) {
  for (size_t i = 0; i < sv->length; i++) {
    if (sv->data[i] == c) {
      return i;
    }
  }

  return sv->length;
}

void replace_char(String_View *sv, size_t position, char new_char) {
  ((char *)sv->data)[position] = new_char;
}

void solve_day4_part1(char *input_name) {

  int total = 0;

  FILE *file = fopen(input_name, "r");
  if (file == NULL) {
    printf("Error opening file: %s\n", input_name);
    return;
  }

  fseek(file, 0L, SEEK_END);   // Move to the end of the file
  long numbytes = ftell(file); // Get the size
  fseek(file, 0L, SEEK_SET);   // Reset to the beginning

  char *buffer = malloc(numbytes);
  fread(buffer, sizeof(char), numbytes, file);

  String_View input = sv(buffer);
  size_t len = input.length;
  size_t col_len = find_first_of(&input, '\n');
  size_t n_rows = len / (col_len + 1);

  fclose(file);

  for (size_t i = 0; i < n_rows; i++) {
    for (size_t j = 0; j < col_len; j++) {
      size_t count = 0;
      if (input.data[i * (col_len + 1) + j] != '@') {
        continue;
      }
      if (has_up(i, n_rows)) {
        if (input.data[(i - 1) * (col_len + 1) + j] == '@') {
          count++;
        }
      }
      if (has_down(i, n_rows)) {
        if (input.data[(i + 1) * (col_len + 1) + j] == '@') {
          count++;
        }
      }
      if (has_left(j, col_len)) {
        if (input.data[i * (col_len + 1) + j - 1] == '@') {
          count++;
        }
      }
      if (has_right(j, col_len)) {
        if (input.data[i * (col_len + 1) + j + 1] == '@') {
          count++;
        }
      }
      if (has_up(i, n_rows) && has_left(j, col_len)) {
        if (input.data[(i - 1) * (col_len + 1) + j - 1] == '@') {
          count++;
        }
      }
      if (has_up(i, n_rows) && has_right(j, col_len)) {
        if (input.data[(i - 1) * (col_len + 1) + j + 1] == '@') {
          count++;
        }
      }
      if (has_down(i, n_rows) && has_left(j, col_len)) {
        if (input.data[(i + 1) * (col_len + 1) + j - 1] == '@') {
          count++;
        }
      }
      if (has_down(i, n_rows) && has_right(j, col_len)) {
        if (input.data[(i + 1) * (col_len + 1) + j + 1] == '@') {
          count++;
        }
      }

      if (count < 4) {
        total++;
      }
    }
  }

  free(buffer);

  printf("Total: %d\n", total);
}

int main() {
  // char *input_name = "input_test.txt"; // 13
  char *input_name = "input.txt"; // 1376

  solve_day4_part1(input_name);
}
