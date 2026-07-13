#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t length;
} Mutable_String;

Mutable_String ms(char *data) { return (Mutable_String){data, strlen(data)}; }

int has_up(size_t row, size_t n_rows) { return row > 0; }
int has_down(size_t row, size_t n_rows) { return row < n_rows - 1; }
int has_left(size_t col, size_t len_col) { return col > 0; }
int has_right(size_t col, size_t len_col) { return col < len_col - 1; }

size_t find_first_of_mutable(Mutable_String *sv, char c) {
  for (size_t i = 0; i < sv->length; i++) {
    if (sv->data[i] == c) {
      return i;
    }
  }

  return sv->length;
}

void replace_char(Mutable_String *string, size_t position, char new_char) {
  if (position >= string->length) {
    fprintf(stderr,
            "Error: position %zu is out of bounds for string of length %zu\n",
            position, string->length);
    return;
  }
  ((char *)string->data)[position] = new_char;
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

  Mutable_String input = ms(buffer);
  size_t len = input.length;
  size_t col_len = find_first_of_mutable(&input, '\n');
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
        replace_char(&input, i * (col_len + 1) + j, '.');
        if (i > 0) {
          i--;
        }
        j = -1;
        total++;
      }
    }
  }

  free(buffer);

  printf("Total: %d\n", total);
}

int main() {
  // char *input_name = "input_test.txt"; // 43
  char *input_name = "input.txt"; // 8587

  solve_day4_part1(input_name);
}
